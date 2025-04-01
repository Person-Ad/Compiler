%skeleton "lalr1.cc"
%require "3.0.4"
%define api.value.type variant
%define parse.trace
%define parse.error verbose

%code requires {
#include <string>
}

%param { yyFlexLexer* lexer }

%{
#include <iostream>
#include "lexer.hpp"
%}

// Token declarations
%token IF ELSE WHILE FOR SWITCH CASE DEFAULT BREAK CONTINUE RETURN
%token KW_VAR KW_CONST KW_FUNC KW_INT KW_FLOAT KW_BOOL KW_STRING
%token <std::string> IDENTIFIER STRING
%token <int> INTEGER
%token <double> FLOAT
%token <bool> BOOLEAN
%token PLUS MINUS STAR SLASH PERCENT EQ NEQ LT GT LE GE AND OR NOT
%token ASSIGN SEMICOLON LPAREN RPAREN LBRACE RBRACE

// Grammar rules
%%

program
    : statement_list
    ;

statement_list
    : statement
    | statement_list statement
    ;

statement
    : assignment_statement
    | expression_statement
    ;

assignment_statement
    : IDENTIFIER ASSIGN expression SEMICOLON
      { std::cout << "Assigned " << $1 << " = [value]\n"; }
    ;

expression_statement
    : expression SEMICOLON
      { std::cout << "Expression evaluated\n"; }
    ;

expression
    : expression PLUS expression
      { std::cout << "Add\n"; }
    | expression MINUS expression
      { std::cout << "Subtract\n"; }
    | expression STAR expression
      { std::cout << "Multiply\n"; }
    | expression SLASH expression
      { std::cout << "Divide\n"; }
    | INTEGER
      { std::cout << "Integer: " << $1 << "\n"; }
    | IDENTIFIER
      { std::cout << "Variable: " << $1 << "\n"; }
    ;

%%

#include "lexer.hpp"
int main() {
    yyFlexLexer lexer;
    yy::parser parser(&lexer);
    return parser.parse();
}