add_library(RunnerPass MODULE Pass.cpp)
set_target_properties(RunnerPass PROPERTIES COMPILE_FLAGS "-D__GLIBCXX_USE_CXX11_ABI=0 -fno-rtti" )