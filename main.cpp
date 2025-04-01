#include <iostream>
#include <FlexLexer.h>

int main() {
    yyFlexLexer lexer_instance;
    std::cout << "--- Lexer Output Start ---\n";
    while (lexer_instance.yylex() != 0) {
        // Loop continues until the lexer returns 0 (end of input)
    }
    std::cout << "--- Lexer Output End ---\n";
    return 0;
}