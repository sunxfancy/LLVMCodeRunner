
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "crrt.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <map>
#include <sstream>

using namespace llvm;
using namespace std;
using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

class JITRunner {
public:
    JITRunner() {
        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();
        InitializeNativeTargetAsmParser();
    }
    ~JITRunner() {
        delete EE;
        delete RTDyldMM;
    }
    LLVMContext context;
    ExecutionEngine *EE = NULL;
    RTDyldMemoryManager *RTDyldMM = NULL;
    map<string, test_func> testptr_map;

    void initEE(std::unique_ptr<Module> Owner) {
        string ErrStr;
        if (EE == NULL) {
            RTDyldMM = new SectionMemoryManager();
            EE = EngineBuilder(std::move(Owner))
                     .setEngineKind(EngineKind::JIT)
                     .setErrorStr(&ErrStr)
                     .setVerifyModules(true)
                     .setMCJITMemoryManager(
                         std::unique_ptr<RTDyldMemoryManager>(RTDyldMM))
                     .setOptLevel(CodeGenOpt::Default)
                     .create();
        } else
            EE->addModule(std::move(Owner));
        if (ErrStr.length() != 0)
            cerr << "Create Engine Error" << endl << ErrStr << endl;
        EE->finalizeObject();
    }

    void *LoadFunction(string func_name, StringRef memory) {
        SMDiagnostic error;
        std::unique_ptr<Module> Owner =
            parseAssemblyString(memory, error, context);
        if (Owner == nullptr) {
            cout << "Load Error" << endl;
            error.print("crrt_run", errs());
            return nullptr;
        }

        initEE(std::move(Owner));

        void *func_addr = (void *)(EE->getFunctionAddress(func_name.c_str()));
        if (func_addr == 0) {
            printf("Error: Can not find function %s\n", func_name.c_str());
            return nullptr;
        }
        return func_addr;
    }

    // here we test and get the speed up
    double RunTest(string func_name, void *func_addr) {
        auto p = testptr_map[func_name];
        return p(func_addr);
    }
};

static JITRunner runner;

class RootHandler : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest &request,
                       HTTPServerResponse &response) {
        cout << ("Request from " + request.clientAddress().toString()) << endl;
        response.setStatus(HTTPResponse::HTTP_OK);
        response.setChunkedTransferEncoding(true);
        response.setContentType("text/html");
        std::ostream &ostr = response.send();

        if (request.getURI() == "/function") {
            string name;
            request.stream() >> name;
            stringstream ss;
            ss << request.stream().rdbuf();
            void *f = runner.LoadFunction(name, ss.str());
            ostr << runner.RunTest(name, f) << endl;
        }
    }
};

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
    MyRequestHandlerFactory() {}
    HTTPRequestHandler *createRequestHandler(const HTTPServerRequest &request) {
        return new RootHandler();
    }
};

class CRRTServer : public ServerApplication {
public:
    CRRTServer(int port) : port(port) {}
    ~CRRTServer() {}

protected:
    int main(const vector<string> &) {
        HTTPServerParams *pParams = new HTTPServerParams;
        pParams->setMaxQueued(100);
        pParams->setMaxThreads(4);
        ServerSocket svs(port);
        HTTPServer srv(new MyRequestHandlerFactory(), svs, pParams);
        srv.start();
        waitForTerminationRequest();
        srv.stop();
    }

private:
    UInt16 port;
};

void crrt_reg_test(crrt_Reg arr[]) {
    for (int i = 0; arr[i].name != NULL; ++i) {
        runner.testptr_map[arr[i].name] = arr[i].func;
    }
}

extern void crrt_main();

int main(int argc, char *argv[]) {
    crrt_main();
    CRRTServer app(12306);
    return app.run(argc, argv);
}
