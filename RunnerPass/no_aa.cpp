#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct NoAA : public FunctionPass {
    static char ID;
    NoAA() : FunctionPass(ID) {}
    
}; 

char NoAA::ID = 0;

// Declare that we implement the AliasAnalysis interface
INITIALIZE_AG_PASS(NoAA, AliasAnalysis , "no-aa",
    "No AA",
    false,  // Is CFG Only?
    true,   // Is Analysis?
    false); // Is default Analysis Group implementation?
} 

