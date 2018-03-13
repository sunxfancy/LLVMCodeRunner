include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../Runtime)
SET_PROPERTY( SOURCE loop.c PROPERTY COMPILE_FLAGS "-O0 -DNDEBUG")
add_executable(loop loop.c loop_test.cpp)
SET_PROPERTY( SOURCE main.c PROPERTY COMPILE_FLAGS "-O0 -DNDEBUG")
add_executable(gvn main.c main_test.cpp)

llvm_map_components_to_libnames(LLVM_LIBS
    asmparser support core irreader executionengine interpreter runtimedyld
    mc mcjit bitwriter x86codegen target native)

target_link_libraries(loop crrt ${CONAN_LIBS_POCO} ${LLVM_LIBS})
set_target_properties(loop PROPERTIES COMPILE_FLAGS "-D__GLIBCXX_USE_CXX11_ABI=0")

target_link_libraries(gvn crrt ${CONAN_LIBS_POCO} ${LLVM_LIBS})
set_target_properties(gvn PROPERTIES COMPILE_FLAGS "-D__GLIBCXX_USE_CXX11_ABI=0")