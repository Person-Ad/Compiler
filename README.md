## Project Overview

This project involves designing and implementing a simple programming language using the Lex (Flex) and Yacc (Bison) compiler-generating tools.

- Variable and constant declarations
- Mathematical and logical expressions
- Assignment statements
- Control flow statements (if-then-else, while loops, for loops, switch statements)
- Block structures with nested scopes
- Functions

The project is divided into two phases:
- **Phase I**: Implement the lexical analyzer (lexer) and parser.
- **Phase II**: Extend the implementation with a symbol table, quadruple generation, syntax error handling, and basic semantic analysis.

I will focus on the current progress in **Phase I** and the what is still missing and needs to be implemented.

---

## Tools and Technologies Used

- **Flex (Lex)**: Generates the lexical analyzer.
- **Bison (Yacc)**: Generates the parser.
- **C++**: The implementation language for both the lexer and parser.
- **GCC/G++**: Compiler used to build the project.

---

## Progress So Far

### 1. Lexical Analyzer (Lexer)

- **Status**: Fully implemented and tested.
- **Details**:
  - Defined in `lexer.l` and generated using Flex with C++ option.
  - Recognizes the token list defined in the lexer.l file.
- **Testing**:
  - Compiled and tested independently with the following commands:
    ```bash
    flex --outfile=lexer.cpp --header-file=lexer.hpp lexer.l
    g++ main.cpp lexer.cpp -o run_lexer -lfl
    ./run_lexer < test_file.txt
    ```
  - The `main.cpp` file uses `yyFlexLexer` to tokenize input from `test_file.txt`, printing token types and values.
  - Successfully tokenizes sample inputs, confirming correct functionality.

### 2. Parser

- **Status**: Partially implemented; encountering compilation issues.
- **Details**:
  - Defined in `parser.y` and generated using Bison with C++ support.
  - Declares tokens corresponding to the lexer’s output, including keywords, literals, operators, and punctuation.
  - Implements basic grammar rules for:
    - Assignment statements (e.g., `x = 5;`)
    - Simple arithmetic expressions (e.g., `a + b * c`)
- **Issues**:
  - Compilation fails when integrating with the lexer, with the following error:
    ```
    parser.cpp: In member function ‘virtual int yy::parser::parse()’:
    parser.cpp:610:40: error: ‘yylex’ was not declared in this scope; did you mean ‘yylen’?
      610 |             yyla.kind_ = yytranslate_ (yylex (&yyla.value, lexer));
          |                                        ^~~~~
          |                                        yylen
    ```

---

## Remaining Tasks for Phase I

To complete Phase I, the following tasks must be addressed:

### 1. Resolve the `yylex` Declaration Issue

### 2. Complete the parser implementation.

---
