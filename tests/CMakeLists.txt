set(TEST_SOURCES testsListeSimplementChainee.cpp)

add_executable(
        testsListeSimplementChainee
        ${TEST_SOURCES}
)

target_include_directories(testsListeSimplementChainee PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        testsListeSimplementChainee
        gtest_main
        gtest
        pthread
)

include(GoogleTest)

gtest_discover_tests(testsListeSimplementChainee)

