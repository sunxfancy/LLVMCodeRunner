all:
	clang -O0 -std=c99 main.c -S -emit-llvm -o main.ll
	clang -O3 -std=c99 main.c -S -emit-llvm -o main.O1.ll
	../build/bin/opt main.ll -sroa --debug-pass=Structure -S -o main.O1-sroa.ll
	../build/bin/opt main.ll -print-alias-sets -sroa -early-cse --debug-pass=Structure -S -o main.O1-sroa-cse.ll
	../build/bin/opt main.ll -disable-basicaa -print-alias-sets -sroa -early-cse --debug-pass=Structure -S -o main.O1-sroa-cse.ll

test:
	../build/bin/llvm-as < /dev/null | ../build/bin/opt -O1 -disable-output -debug-pass=Arguments
