include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(structure_tests test_structures.cpp)
target_link_libraries(structure_tests PRIVATE structures GTest::gtest_main)

if(MSVC)
    target_compile_options(structure_tests PRIVATE /W4 /WX)
else()
    target_compile_options(structure_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(GoogleTest)
gtest_discover_tests(structure_tests)
