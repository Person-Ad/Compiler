%x COMMENT

%{
#include <stdlib.h>
#include "node.h"
#include "parser.tab.h"
#include <stdbool.h>
#include <string.h>
void yyerror(char *);

int line_number = 1;

// Overload for unrecognized chars (doesn't return a token enum)
void print_unrecognized(const char* text, int line) {
    //  std::cout << "ERROR: Unrecognized character '" << text << "' at line " << line << std::endl;
}

%}

/* Pattern Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
IDENT_START [a-zA-Z_]
IDENT_CHAR  [a-zA-Z0-9_]

%%

"if"                        { return IF; }
"else"                      { return ELSE; }
"while"                     { return WHILE; }
"for"                       { return FOR; }
"switch"                    { return SWITCH; }
"case"                      { return CASE; }
"default"                   { return DEFAULT; }
"break"                     { return BREAK; }
"continue"                  { return CONTINUE; }
"return"                    { return RETURN; }
"var"                       { return KW_VAR; }
"const"                     { return KW_CONST; }
"func"                      { return KW_FUNC; }
"int"                       { return KW_INT; }
"float"                     { return KW_FLOAT; }
"bool"                      { return KW_BOOL; }
"string"                    { return KW_STRING; }

"true"                      { yylval.boolValue = 1; return BOOLEAN; }
"false"                     { yylval.boolValue = 0; return BOOLEAN; }

{IDENT_START}{IDENT_CHAR}*  { yylval.stringValue = strdup(yytext); return IDENTIFIER; }

-?{DIGIT}+                  { yylval.intValue = atoi(yytext); return INTEGER; }

-?{DIGIT}+\.{DIGIT}+        { yylval.floatValue = atof(yytext); return FLOAT; }

\"([^\\\"]|\\.)*\"          { yylval.stringValue = strdup(yytext); return STRING; }

"+"                         { return PLUS; }
"-"                         { return MINUS; }
"*"                         { return STAR; }
"/"                         { return SLASH; }
"%"                         { return PERCENT; }
"=="                        { return EQ; }
"!="                        { return NEQ; }
"<"                         { return LT; }
">"                         { return GT; }
"<="                        { return LE; }
">="                        { return GE; }
"&&"                        { return AND; }
"||"                        { return OR; }
"!"                         { return NOT; }
"="                         { return ASSIGN; }
"?"                         { return TERNARY; }

":"                         { return COLON; }
";"                         { return SEMICOLON; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
"{"                         { return LBRACE; }
"}"                         { return RBRACE; }

"//".*                      { /* Optional: std::cout << "COMMENT(SINGLE): " << yytext << std::endl; */ }

"/*"                        { /* Optional: std::cout << "COMMENT(MULTI_START)" << std::endl; */ BEGIN(COMMENT); }
<COMMENT>\n                 { line_number++; }
<COMMENT>"*/"               { /* Optional: std::cout << "COMMENT(MULTI_END)" << std::endl; */ BEGIN(INITIAL); }
<COMMENT>.                  { /* ignore characters in comment */ }

[ \t]+                      { /* Ignore whitespace */ }

\n                          { line_number++; /* Ignore newline, but count line */ }

.                           { print_unrecognized(yytext, line_number); /* Call helper */ }

%%
int yywrap(void) {
    return 1;
}