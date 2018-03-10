#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include <iostream>

using namespace llvm;
using namespace Poco;
using namespace Poco::Net;

namespace {
struct CodeRunnerPass : public ModulePass {
    static char ID;
    CodeRunnerPass() : ModulePass(ID) {}

    bool runOnModule(Module &M) override {
        errs() << "CodeRunnerPass: ";
        std::string str;
        raw_string_ostream ss(str);
        M.print(ss, nullptr);
        sendMsg(ss.str());
        return false;
    }

    void sendMsg(const std::string& module, std::string addr = "http://127.0.0.1:12306") {
        URI uri(addr);
        HTTPClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest request(HTTPRequest::HTTP_POST, "/all");
        request.setContentLength(module.length());
        std::ostream& os = session.sendRequest(request);
        os << module << std::flush;
        HTTPResponse response;
        std::istream& rs = session.receiveResponse(response);
        StreamCopier::copyStream(rs, std::cerr);
    }

}; // end of struct CodeRunnerPass
} // end of anonymous namespace

char CodeRunnerPass::ID = 0;
static RegisterPass<CodeRunnerPass> X("cr", "Code Runner Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

