#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct Hello : public FunctionPass {
    static char ID;
    Hello() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
        errs() << "Hello: ";
        errs().write_escaped(F.getName()) << '\n';
        return false;
    }
}; // end of struct Hello
} // end of anonymous namespace

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

namespace {
struct LoopDector : public LoopPass {
    static char ID;
    LoopDector() : LoopPass(ID) {}

    bool runOnLoop(Loop *L, LPPassManager &LPM) override {
        errs() << "LoopDector: ";
        errs().write_escaped(L->getName()) << '\n';
        return false;
    }
}; // end of struct LoopDector
} // end of anonymous namespace

char LoopDector::ID = 1;
static RegisterPass<LoopDector> Y("loop-detector", "LoopDector Pass",
                                  false /* Only looks at CFG */,
                                  false /* Analysis Pass */);