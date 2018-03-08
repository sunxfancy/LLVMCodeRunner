all:
	clang -O0 -std=c99 main.c -S -emit-llvm -o main.ll
	clang -O3 -std=c99 main.c -S -emit-llvm -o main.O3.ll
	../build/bin/opt main.ll -std-compile-opts -S -o main.Ox.ll

