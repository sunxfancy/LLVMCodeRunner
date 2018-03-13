add_library(crrt SHARED main.cpp)

SET_PROPERTY( SOURCE test.cpp PROPERTY COMPILE_FLAGS "-O0 -DNDEBUG")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(crrt_run test.cpp)

llvm_map_components_to_libnames(LLVM_LIBS
    asmparser support core irreader executionengine interpreter runtimedyld
    mc mcjit bitwriter x86codegen target native)

target_link_libraries(crrt_run crrt ${CONAN_LIBS_POCO} ${LLVM_LIBS})
set_target_properties(crrt_run PROPERTIES COMPILE_FLAGS "-D__GLIBCXX_USE_CXX11_ABI=0")