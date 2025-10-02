#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"

using namespace llvm;

struct PeepholePass : public PassInfoMixin<PeepholePass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    std::vector<Instruction*> toDelete;

    for (auto &BB : F) {
      for (auto &I : BB) {
        if (auto *op = dyn_cast<BinaryOperator>(&I)) {
          if (op->getOpcode() == Instruction::Add) {
            Value *lhs = op->getOperand(0);
            Value *rhs = op->getOperand(1);

            if (auto *const_lhs = dyn_cast<ConstantInt>(lhs)) {
              if (const_lhs->getZExtValue() == 0) {
                op->replaceAllUsesWith(rhs);
                toDelete.push_back(op);
              }
            }

            if (auto *const_rhs = dyn_cast<ConstantInt>(rhs)) {
              if (const_rhs->getZExtValue() == 0) {
                op->replaceAllUsesWith(lhs);
                toDelete.push_back(op);
              }
            }
          }
        }
      }
    }

    for (auto *I : toDelete) {
      I->eraseFromParent();
    }

    return toDelete.empty() ? PreservedAnalyses::all() : PreservedAnalyses::none();
  }
};

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "Peephole", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "peephole") {
            FPM.addPass(PeepholePass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
