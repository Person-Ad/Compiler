#include "node.h"

#ifndef SEMANTIC_H_LIBS
#define SEMANTIC_H_LIBS

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#endif // SEMANTIC_H_LIBS

void yyerror(const char *msg);

struct SymbolTable* initialize_global_symbol_table(struct SymbolTable* global_symbol_table, struct SymbolTable* current_symbol_table);

void create_symbol_table(struct SymbolTable** current_symbol_table);

Symbol* insert_symbol(struct SymbolTable* table, char* name, char* type, char* kind);

Symbol* lookup_symbol(struct SymbolTable* table, char* name);

void process_node(nodeType *node);

int handle_expression(nodeType *node);

// int handle_switch_args(nodeType* node, Symbol* referenced_var);

int handle_func_args(nodeType* node, Symbol* nearest_identifier, nodeType *func_id);

struct SymbolTable * handle_func_call_args(struct SymbolTable * temp_table, Symbol* nearest_function, nodeType* func_id);

int handle_switch_args(nodeType* switch_cases, Symbol* referenced_var);

Symbol* lookup_symbol_same_scope(struct SymbolTable* table, char* name);

int variable_redeclaration_val(struct SymbolTable* table, char* name);

void track_scope(struct SymbolTable* t);

void cleanup_all_symbol_tables();

void print_symbol_table(struct SymbolTable *table);

void semantic_check(nodeType* topNode);
