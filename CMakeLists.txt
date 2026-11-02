cmake_minimum_required(VERSION 3.20)

project(Seminar9Structures VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SEMINAR9_BUILD_TESTS "Build unit tests" ON)

add_library(structures STATIC src/structures.cpp)
target_include_directories(structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(seminar9 src/main.cpp)
target_link_libraries(seminar9 PRIVATE structures)

function(enable_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

enable_warnings(structures)
enable_warnings(seminar9)

include(CTest)
if(SEMINAR9_BUILD_TESTS)
    add_subdirectory(tests)
    add_test(NAME demo_smoke COMMAND $<TARGET_FILE:seminar9>)
endif()

install(TARGETS seminar9 RUNTIME DESTINATION bin)
