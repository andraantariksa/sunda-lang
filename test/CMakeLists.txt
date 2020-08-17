enable_testing()

set(TEST_SOURCES
        syntax/Lexer.cpp)

add_executable(sunda_test
        main.cpp
        ${TEST_SOURCES})

target_link_libraries(sunda_test
        sunda_compiler
        gtest
        pthread)

target_include_directories(sunda_test
        PUBLIC
        ../src)