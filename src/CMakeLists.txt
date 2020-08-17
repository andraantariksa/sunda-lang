# Compiler library
set(SOURCES
        syntax/Token.cpp
        syntax/Lexer.cpp
        syntax/AST.cpp
        syntax/Location.cpp)

add_library(sunda_compiler
        STATIC
        ${SOURCES})

# Sunda executable
add_executable(sunda
        main.cpp)

target_link_libraries(sunda
        sunda_compiler)

target_include_directories(sunda
        PUBLIC
        ../external/lib/structopt/single_include)
