cmake_minimum_required (VERSION 3.1)

project(example)

set(CMAKE_CXX_STANDARD 11)

# 源码以 UTF-8 编码保存，使用 MSVC 编译器需要加编译参数提供支持
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    message(STATUS "optional: /UTF-8")   
endif(MSVC)

macro(api_exe target)
    add_executable(${PROJECT_NAME}-${target}
            ${target}.cpp
            )
    target_link_libraries(${PROJECT_NAME}-${target} qzjw-cpp-sdk)
endmacro()

api_exe(Login)