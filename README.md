LLVMCodeRunner
=================

What's a code runner?

LLVM Code runner contains a special utility pass with a runtime library. Usually, when we develop a new LLVM pass, and we want to know the benefit of it. The best way is to use the LLVM test suite and there are some kinds of tools can help you get the performance results. 

But actually, to test a pass is not easy. And when you generate many kinds of optimitions, there is no way for you to get the best one, except test it one by one. 
It's really time consuming. Even thought you just change one line of your final generated function. You need to rebuild the whole project, link the executable and run the test. If the test project is huge, that's will be too slow.

So usually, it's impossible to run real project as an optimition test suite. 

This code runner is to solve this problem. It's designed to be easily called in an LLVM pass. And the real runner also could be disturbed on the internet. So it's possible to send the test command to lots of different platfroms (if there is no architecture difference). 

With this tool, you can test your code on any kinds of platform without redeploy your new version of code. You can also run test suite on your android tablet or iPhone. 


## Architecture of the project

The project is based on a simple idea - Using a JIT engine to directly run the code. The LLVM project has a nice JIT engine for testing and running LLVM assembly code from remote. 

So the work flow is we first create a test suite and base line version of the project. In the next, we use a function pointer to replace the function we want to test and keep the other the same. 



## Build the project

Firstly, we need to install python3 with pip support. To build this project, we need cmake, C++ compiler which support C++11 and any kinds of build system which cmake support. And make sure your path enviroment varible has the pip command, and the place of third party commands.

Second, install Conan package manager and Code Factory build tool. Then setup the package location for conan.

```sh
pip3 install --user --upgrade conan codefactory
conan remote add sunxfancy https://api.bintray.com/conan/sunxfancy/common 
conan remote add ECDK https://api.bintray.com/conan/elite-lang/ECDK 
```

Third, run build command in the root dir of this project.

```sh
codef build --release
```



## Test the project

We have some test suites in the AliasAnalysis Directory. For generating IR file, you also need clang installed.

To test the correctness of code runner:

```sh
cd AsmGen/
make            # this will create a main.bc file in dir `build/bin`
cd ../build/bin
./crrt_run
```

Those commands will create a server of code runner. Then, please use another shell to test the pass.

```sh
cd build/bin
./opt main.bc -load ./libRunnerPass.so -cr -licm -cr -disable-output
```

If the project build correctly, it will show you the time consume before and after the -licm pass.

```sh
CodeRunnerPass: dgemm_ijk : 1
time base: 88 ms
time real: 88 ms

CodeRunnerPass: dgemm_ijk : 4.19048
time base: 88 ms
time real: 21 ms
```


To test the Alias Analysis pass, please create the IR file first:

```sh
cd AliasAnalysis/
make
```

To test the speed, please use another shell to run the server:
```sh
cd build/bin
./loop
```

And use the old shell to test the speed:
```sh
make test-licm
```

Before test the GVN, please first use Ctrl+C shutdown the server.
```sh
cd build/bin
./gvn
```

And use the old shell to run the test:
```sh
make test-gvn
```