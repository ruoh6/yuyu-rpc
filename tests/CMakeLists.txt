add_executable(runTests
    test_uniqueid.cc
)
target_include_directories(runTests PRIVATE $(CMAKE_SOURCE_DIR/src))

find_package(GTest REQUIRED)
target_link_libraries(runTests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)
