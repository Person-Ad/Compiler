#include "node.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FIELD_WIDTH 10

int add_code_generation_data(char* op, char* arg1, char* arg2, char* result);

int count_func_call_args(nodeType *func_arg);

void extract_quadruples(nodeType* topNode);

void call_extract_quads(nodeType* topNode);