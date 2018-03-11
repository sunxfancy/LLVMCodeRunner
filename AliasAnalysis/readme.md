This directory is used to do the experiment for the effect of Alias Analysis.

Alias Analysis is a group of passes that can analysis the pointers which point to the same place. So those passes didn't transform the code but find out the inner information for other transformation pass. Actually, this is very important topic in LLVM, and there are quite a lot of pass that relay on alias analysis. 

# The main objective of this experiment

To find out the influence of alias analysis, and compare the different version of alias analysis algorithm. 

## Test Idea

Alias analysis driven transformations：

* -adce pass, which implements Aggressive Dead Code Elimination uses the AliasAnalysis interface to delete calls to functions that do not have side-effects and are not used.
Actually after reading the source code, this pass would not call alias analysis anymore. The debug structure also showing that.

* -licm pass implements various Loop Invariant Code Motion related transformations. It uses the AliasAnalysis interface for several different transformations

* -gvn, -memcpyopt, and -dse passes
These passes use AliasAnalysis information to reason about loads and stores. GVN has the power to elimate the redundant expression. So it's a good point to check the effect of alias analysis.

## Evaluation

The -aa-eval pass simply iterates through all pairs of pointers in a function and asks an alias analysis whether or not the pointers alias. This gives an indication of the precision of the alias analysis. Statistics are printed indicating the percent of no/may/must aliases found (a more precise algorithm will have a lower number of may aliases). 

