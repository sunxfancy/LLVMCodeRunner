all: main.ll main.O1.ll
	../build/bin/opt main.ll -sroa --debug-pass=Structure -S -o main.O1-sroa.ll
	../build/bin/opt main.ll -print-alias-sets -sroa -early-cse --debug-pass=Structure -S -o main.O1-sroa-cse.ll
	../build/bin/opt main.ll -disable-basicaa -print-alias-sets -sroa --debug-pass=Structure -S -o main.O1-sroa-noaa.ll

adce: main.ll
	../build/bin/opt main.ll -adce --debug-pass=Structure -disable-output

licm:
	clang -O0 -std=c99 loop.c -S -emit-llvm -o loop.ll
	../build/bin/opt loop.ll -print-alias-sets --debug-pass=Structure -disable-output
	../build/bin/opt loop.ll -stats -licm --debug-pass=Structure -S -o loop.licm.ll
	../build/bin/opt loop.ll -stats -disable-basicaa -licm --debug-pass=Structure -S -o loop.licm-noaa.ll

gvn: main.ll
	../build/bin/opt main.ll -print-alias-sets --debug-pass=Structure -disable-output
	../build/bin/opt main.ll -stats -gvn --debug-pass=Structure -S -o gvn.ll
	../build/bin/opt main.ll -stats -disable-basicaa -gvn --debug-pass=Structure -S -o gvn.noaa.ll

test:
	../build/bin/llvm-as < /dev/null | ../build/bin/opt -O1 -disable-output -debug-pass=Arguments

main.ll:
	clang -O0 -std=c99 main.c -S -emit-llvm -o main.ll

main.O1.ll:
	clang -O3 -std=c99 main.c -S -emit-llvm -o main.O1.ll