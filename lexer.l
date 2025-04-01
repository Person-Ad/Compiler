%option c++
%option noyywrap
%x COMMENT

%{
#include <iostream>
#include <string>
#include "parser.hpp"

int line_number = 1;

// Helper function to print before returning (optional, keeps actions cleaner)
template<typename T>
T print_and_return(const std::string& type, const char* text, T token) {
    std::cout << type << ": \"" << text << "\"" << std::endl;
    return token;
}

// Overload for unrecognized chars (doesn't return a token enum)
void print_unrecognized(const char* text, int line) {
     std::cout << "ERROR: Unrecognized character '" << text << "' at line " << line << std::endl;
}

%}

/* Pattern Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
IDENT_START [a-zA-Z_]
IDENT_CHAR  [a-zA-Z0-9_]

%%

"if"        { return print_and_return("KEYWORD(IF)", yytext, yy::parser::token::IF); }
"else"      { return print_and_return("KEYWORD(ELSE)", yytext, yy::parser::token::ELSE); }
"while"     { return print_and_return("KEYWORD(WHILE)", yytext, yy::parser::token::WHILE); }
"for"       { return print_and_return("KEYWORD(FOR)", yytext, yy::parser::token::FOR); }
"switch"    { return print_and_return("KEYWORD(SWITCH)", yytext, yy::parser::token::SWITCH); }
"case"      { return print_and_return("KEYWORD(CASE)", yytext, yy::parser::token::CASE); }
"default"   { return print_and_return("KEYWORD(DEFAULT)", yytext, yy::parser::token::DEFAULT); }
"break"     { return print_and_return("KEYWORD(BREAK)", yytext, yy::parser::token::BREAK); }
"continue"  { return print_and_return("KEYWORD(CONTINUE)", yytext, yy::parser::token::CONTINUE); }
"return"    { return print_and_return("KEYWORD(RETURN)", yytext, yy::parser::token::RETURN); }
"var"       { return print_and_return("KEYWORD(VAR)", yytext, yy::parser::token::KW_VAR); }
"const"     { return print_and_return("KEYWORD(CONST)", yytext, yy::parser::token::KW_CONST); }
"func"      { return print_and_return("KEYWORD(FUNC)", yytext, yy::parser::token::KW_FUNC); }
"int"       { return print_and_return("KEYWORD(INT)", yytext, yy::parser::token::KW_INT); }
"float"     { return print_and_return("KEYWORD(FLOAT)", yytext, yy::parser::token::FLOAT); } // Should be changed to KW_FLOAT
"bool"      { return print_and_return("KEYWORD(BOOL)", yytext, yy::parser::token::KW_BOOL); }
"string"    { return print_and_return("KEYWORD(STRING)", yytext, yy::parser::token::STRING); } // Should be changed to KW_STRING

"true"      { return print_and_return("LITERAL(BOOLEAN)", yytext, yy::parser::token::BOOLEAN); }
"false"     { return print_and_return("LITERAL(BOOLEAN)", yytext, yy::parser::token::BOOLEAN); }

{IDENT_START}{IDENT_CHAR}* { return print_and_return("IDENTIFIER", yytext, yy::parser::token::IDENTIFIER); }

-?{DIGIT}+            { return print_and_return("LITERAL(INTEGER)", yytext, yy::parser::token::INTEGER); }

-?{DIGIT}+\.{DIGIT}+    { return print_and_return("LITERAL(FLOAT)", yytext, yy::parser::token::FLOAT); } // Note: Same token as keyword "float"

\"[^\"]*\"            { return print_and_return("LITERAL(STRING)", yytext, yy::parser::token::STRING); } // Note: Same token as keyword "string"

"+"         { return print_and_return("OPERATOR(PLUS)", yytext, yy::parser::token::PLUS); }
"-"         { return print_and_return("OPERATOR(MINUS)", yytext, yy::parser::token::MINUS); }
"*"         { return print_and_return("OPERATOR(STAR)", yytext, yy::parser::token::STAR); }
"/"         { return print_and_return("OPERATOR(SLASH)", yytext, yy::parser::token::SLASH); }
"%"         { return print_and_return("OPERATOR(PERCENT)", yytext, yy::parser::token::PERCENT); }
"=="        { return print_and_return("OPERATOR(EQ)", yytext, yy::parser::token::EQ); }
"!="        { return print_and_return("OPERATOR(NEQ)", yytext, yy::parser::token::NEQ); }
"<"         { return print_and_return("OPERATOR(LT)", yytext, yy::parser::token::LT); }
">"         { return print_and_return("OPERATOR(GT)", yytext, yy::parser::token::GT); }
"<="        { return print_and_return("OPERATOR(LE)", yytext, yy::parser::token::LE); }
">="        { return print_and_return("OPERATOR(GE)", yytext, yy::parser::token::GE); }
"&&"        { return print_and_return("OPERATOR(AND)", yytext, yy::parser::token::AND); }
"||"        { return print_and_return("OPERATOR(OR)", yytext, yy::parser::token::OR); }
"!"         { return print_and_return("OPERATOR(NOT)", yytext, yy::parser::token::NOT); }
"="         { return print_and_return("OPERATOR(ASSIGN)", yytext, yy::parser::token::ASSIGN); }

";"         { return print_and_return("PUNCTUATION(SEMICOLON)", yytext, yy::parser::token::SEMICOLON); }
"("         { return print_and_return("PUNCTUATION(LPAREN)", yytext, yy::parser::token::LPAREN); }
")"         { return print_and_return("PUNCTUATION(RPAREN)", yytext, yy::parser::token::RPAREN); }
"{"         { return print_and_return("PUNCTUATION(LBRACE)", yytext, yy::parser::token::LBRACE); }
"}"         { return print_and_return("PUNCTUATION(RBRACE)", yytext, yy::parser::token::RBRACE); }

"//".* { /* Optional: std::cout << "COMMENT(SINGLE): " << yytext << std::endl; */ }

"/*"        { /* Optional: std::cout << "COMMENT(MULTI_START)" << std::endl; */ BEGIN(COMMENT); }
<COMMENT>\n { line_number++; }
<COMMENT>"*/" { /* Optional: std::cout << "COMMENT(MULTI_END)" << std::endl; */ BEGIN(INITIAL); }
<COMMENT>.  { /* ignore characters in comment */ }

[ \t]+      { /* Ignore whitespace */ }

\n          { line_number++; /* Ignore newline, but count line */ }

.           { print_unrecognized(yytext, line_number); /* Call helper */ }

%%