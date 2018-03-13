all: main.ll main.O1.ll
	../build/bin/opt main.ll -sroa --debug-pass=Structure -S -o main.O1-sroa.ll
	../build/bin/opt main.ll -print-alias-sets -sroa -early-cse --debug-pass=Structure -S -o main.O1-sroa-cse.ll
	../build/bin/opt main.ll -disable-basicaa -print-alias-sets -sroa --debug-pass=Structure -S -o main.O1-sroa-noaa.ll

adce: main.ll
	../build/bin/opt main.ll -adce --debug-pass=Structure -disable-output

licm:
	clang -O0 loop.c -S -emit-llvm -o loop.ll
	../build/bin/opt loop.ll -print-alias-sets --debug-pass=Structure -disable-output
	../build/bin/opt loop.ll -stats -licm --debug-pass=Structure -S -o loop.licm.ll
	../build/bin/opt loop.ll -stats -disable-basicaa -print-alias-sets -licm --debug-pass=Structure -S -o loop.licm-noaa.ll

gvn: main.ll
	../build/bin/opt main.ll -print-alias-sets --debug-pass=Structure -disable-output
	../build/bin/opt main.ll -stats -gvn --debug-pass=Structure -S -o gvn.ll
	../build/bin/opt main.ll -stats -disable-basicaa -gvn --debug-pass=Structure -S -o gvn.noaa.ll

getO1pass:
	../build/bin/llvm-as < /dev/null | ../build/bin/opt -O1 -disable-output -debug-pass=Arguments

test-licm:
	../build/bin/opt loop.ll -load ../build/bin/libRunnerPass.so -cr -licm -cr -disable-output
	../build/bin/opt loop.ll -load ../build/bin/libRunnerPass.so -disable-basicaa -cr -licm -cr -disable-output

test-gvn:
	../build/bin/opt main.ll -load ../build/bin/libRunnerPass.so -cr -gvn -cr -disable-output
	../build/bin/opt main.ll -load ../build/bin/libRunnerPass.so -disable-basicaa -cr -gvn -cr -disable-output


main.ll:
	clang -O0 main.c -S -emit-llvm -o main.ll

main.O1.ll:
	clang -O1 main.c -S -emit-llvm -o main.O1.ll

clear:
	rm *.ll 

.PHONY: all adec licm gvn clear 