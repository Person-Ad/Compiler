#include "semantic.h"
#include "parser.tab.h"

struct SymbolTable **all_tables = NULL;
int table_count = 0;
FILE *errors_file;

struct SymbolTable *global_symbol_table = NULL;
struct SymbolTable *current_symbol_table = NULL;

struct SymbolTable *initialize_global_symbol_table(struct SymbolTable *global_symbol_table, struct SymbolTable *current_symbol_table)
{
    global_symbol_table = (struct SymbolTable *)malloc(sizeof(struct SymbolTable));
    global_symbol_table->symbols = NULL;
    global_symbol_table->symbol_count = 0;
    global_symbol_table->parent = NULL;
    global_symbol_table->symbol_table_no = 0;



    return global_symbol_table;
}
void print_all_tracked_symbol_tables()
{
    FILE *file = fopen("tracked_tables.txt", "w");
    if (!file) {
        printf("Error: Could not open file for writing tracked tables.\n");
        return;
    }
    fprintf(file, "# All Tracked Symbol Tables\n\n");

    for (int i = 0; i < table_count; ++i) {
        fprintf(file,
                "## Symbol Table #%d (Address: `%p`, Parent Address: `%p`)\n\n",
                i + 1,
                (void *)all_tables[i],
                (void *)all_tables[i]->parent);

        fprintf(file,
                "| Name | Type | Kind | Param Count | Sub Block Table | Defined | Used |\n");
        fprintf(file,
                "|------|------|------|-------------|-----------------|---------|------|\n");

        struct SymbolTable *table = all_tables[i];
        for (int j = 0; j < table->symbol_count; j++) {
            Symbol *sym = table->symbols[j];

            if (sym->kind && 
                (strcmp(sym->kind, "variable") == 0 || 
                 strcmp(sym->kind, "constant") == 0 || 
                 strcmp(sym->kind, "function") == 0) && 
                sym->type && strcmp(sym->type, "undefined") != 0) {
                if (sym->is_used == 0) {
                    fprintf(errors_file, "Warning: Unused %s '%s'.\n", sym->kind, sym->name);
                }
            }

            int param_count = 0;
            void *sub_table = NULL;
            if (sym->kind && strcmp(sym->kind, "function") == 0) {
                param_count = sym->param_count;
                sub_table = (void *)sym->sub_block_table;
            }

            const char *defined;
            if (sym->kind &&
                (strcmp(sym->kind, "function") == 0 ||
                 strcmp(sym->kind, "variable") == 0 ||
                 strcmp(sym->kind, "constant") == 0) ||
                 strcmp(sym->kind, "parameter") == 0) {
                defined = (sym->is_defined == 1) ? "Yes"
                                                : (sym->is_defined ? "GB" : "No");
            } else {
                defined = "N/A";
            }

            const char *used = (sym->is_used == 1) ? "Yes" : "No";

            fprintf(file,
                "| %s | %s | %s | %d | %p | %s | %s |\n",
                sym->name,
                sym->type,
                sym->kind ? sym->kind : "",
                param_count,
                sub_table,
                defined,
                used);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}
void create_symbol_table(struct SymbolTable **current_symbol_table)
{
    struct SymbolTable *new_table = (struct SymbolTable *)malloc(sizeof(struct SymbolTable));
    new_table->symbols = NULL;
    new_table->symbol_count = 0;
    new_table->symbol_table_no = table_count;
    new_table->parent = *current_symbol_table;
    *current_symbol_table = new_table;

    track_scope(new_table);
}

Symbol *insert_symbol(struct SymbolTable *table, char *name, char *type, char *kind)
{
    if (!table)
        return (Symbol *)NULL;

    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = strdup(type);
    new_symbol->kind = strdup(kind);
    new_symbol->parent = current_symbol_table;

    table->symbols = (Symbol **)realloc(table->symbols, sizeof(Symbol *) * (table->symbol_count + 1));
    table->symbols[table->symbol_count] = new_symbol;
    table->symbol_count++;

    print_symbol_table(current_symbol_table);

    return new_symbol;
}

Symbol *lookup_symbol(struct SymbolTable *table, char *name)
{
    struct SymbolTable *current_table = table;

    while (current_table)
    {
        for (int i = 0; i < current_table->symbol_count; i++)
        {
            if (strcmp(current_table->symbols[i]->name, name) == 0)
            {
                return current_table->symbols[i];
            }
        }
        current_table = current_table->parent;
    }

    return NULL;
}

Symbol *lookup_symbol_same_scope(struct SymbolTable *table, char *name)
{
    struct SymbolTable *current_table = table;

    for (int i = 0; i < current_table->symbol_count; i++)
    {
        if (strcmp(current_table->symbols[i]->name, name) == 0)
        {
            return current_table->symbols[i];
        }
    }

    return NULL;
}

int variable_redeclaration_val(struct SymbolTable *table, char *name)
{
    Symbol *sym = lookup_symbol_same_scope(table, name);
    if (sym == NULL)
        return 1;
    return 0;
}

void print_symbol_table(struct SymbolTable *table)
{
    if (!table)
    {
        printf("No symbol table to display.\n");
        return;
    }

    printf("=== Symbol Table Validation Start === [COUNT=%d]\n", table->symbol_count);
    printf("Current Symbol Table:\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-10s | %-10s | %-12s | %-15s | %-10s |\n", "Name", "Type", "Kind", "Param Count", "Sub Block Table", "Defined");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < table->symbol_count; i++)
    {
        Symbol *sym = table->symbols[i];
        printf("| %-15s | %-10s | %-10s | %-12d | %-15p | %-10s |\n",
               sym->name,
               sym->type,
               sym->kind,
               sym->kind && strcmp(sym->kind, "function") == 0 ? sym->param_count : 0,
               sym->kind && strcmp(sym->kind, "function") == 0 ? (void *)sym->sub_block_table : NULL,
               sym->kind && (strcmp(sym->kind, "function") == 0 || strcmp(sym->kind, "variable") == 0 || strcmp(sym->kind, "constant") == 0) ? (sym->is_defined == 1 ? "Yes" : (sym->is_defined ? "GB" : "No")) : "N/A");
    }

    printf("---------------------------------------------------------------------------------------------\n");
    printf("=== Symbol Table Validation End ===\n");
}

char *nodeEnum_to_string(int type)
{
    switch (type)
    {
    case typeIntCon:
        return strdup("int");
    case typeFloatCon:
        return strdup("float");
    case typeBoolCon:
        return strdup("bool");
    case typeStringCon:
        return strdup("string");
    case typeId:
        return strdup("identifier");
    case typeConst:
        return strdup("constant");
    case typeOpr:
        return strdup("operator");
    default:
        return strdup("unresolved type");
    }
}

int string_to_nodeEnum(const char *str)
{
    if (strcmp(str, "int") == 0)
        return typeIntCon;
    if (strcmp(str, "float") == 0)
        return typeFloatCon;
    if (strcmp(str, "bool") == 0)
        return typeBoolCon;
    if (strcmp(str, "string") == 0)
        return typeStringCon;
    if (strcmp(str, "identifier") == 0)
        return typeId;
    if (strcmp(str, "constant") == 0)
        return typeConst;
    if (strcmp(str, "operator") == 0)
        return typeOpr;
    return -1; // unknown type
}

void track_scope(struct SymbolTable *t)
{
    all_tables = (struct SymbolTable **)realloc(all_tables, sizeof(struct SymbolTable *) * (table_count + 1));
    all_tables[table_count++] = t;
}

void cleanup_all_symbol_tables()
{
    for (int i = 0; i < table_count; ++i)
    {
        struct SymbolTable *st = all_tables[i];
        for (int j = 0; j < st->symbol_count; ++j)
        {
            free(st->symbols[j]->name);
            free(st->symbols[j]->type);
            free(st->symbols[j]->kind);

            free(st->symbols[j]);
        }
        free(st->symbols);
        free(st);
    }
    free(all_tables);
}

void enter_scope(nodeType *node)
{
    if (node->type == typeOpr)
        if (node->opr.oper == BLOCK)
            create_symbol_table(&current_symbol_table);
}

int leave_scope(nodeType *node)
{
    if (node->type == typeOpr)
        if (node->opr.oper == BLOCK)
        {
            if (current_symbol_table->parent == NULL)
                return 0;
            current_symbol_table = current_symbol_table->parent;
            return 1;
        }
    return -1; // non-block node
}

int handle_func_args(nodeType *node, Symbol *nearest_identifier, nodeType *func_id)
{
    if (node->opr.oper == FUNC_ARG)
    {
        if (nearest_identifier != NULL)
        {
            struct SymbolTable *nearest_table = nearest_identifier->sub_block_table;
            if (strcmp(nearest_table->symbols[0]->type, node->opr.op[0]->id.type) != 0 || strcmp(nearest_table->symbols[0]->kind, "parameter") != 0)
            {
                printf("Error: Function %s parameter type mismatch or incorrect parameter kind.\n", func_id->id.name);
                fprintf(errors_file, "Error: Function %s parameter type mismatch or incorrect parameter kind.\n", func_id->id.name);

                return 0;
            }

            node->opr.op[0]->id.sname = nearest_table->symbols[0]->sname;

        }
        else{
            Symbol* sym = insert_symbol(current_symbol_table, node->opr.op[0]->id.name, node->opr.op[0]->id.type, strdup("parameter"));
            if(node->opr.nops == 2){
                if(strcmp(node->opr.op[0]->id.type, nodeEnum_to_string(node->opr.op[1]->type)) == 0){
                    sym->is_defined = 1;
                }
            }

            char* tmp = (char*)malloc(100);
            sprintf(tmp, "%s@s%d", node->opr.op[0]->id.name, sym->parent->symbol_table_no);
            sym->sname = tmp;
            node->opr.op[0]->id.sname = tmp;
        }
    }
    else if (node->opr.oper == FUNC_ARG_LIST)
    {
        int sum = 0;
        for (int i = 0; i < node->opr.nops; i++)
        {
            nodeType *func_arg = node->opr.op[i];
            int handler = handle_func_args(func_arg, nearest_identifier, func_id);
            if (handler == 0)
                return 0;
            sum += handler;
        }

        return sum;
    }

    return 1;
}

int handle_func_call_args(nodeType *func_arg, Symbol *nearest_function, nodeType *func_id)
{
    if (func_arg->opr.oper == ARG_VALUES)
    {
        int sum = 0;

        for (int i = 0; i < func_arg->opr.nops; i++)
        {
            sum += handle_func_call_args(func_arg->opr.op[i], nearest_function, func_id);
        }
        return sum;
    }
    else if (func_arg->opr.oper == ARG_VALUE)
    {
        
        int arg_type = handle_expression(func_arg->opr.op[0]);
        if (arg_type == -1)
        {
            printf("Error: Invalid argument type for function %s.\n", func_id->id.name);
            fprintf(errors_file, "Error: Invalid argument type for function %s.\n", func_id->id.name);
            return 0;
        }

        printf("test");
        Symbol *param = nearest_function->sub_block_table->symbols[0];
        char *param_type = param->type;
        char *arg_type_str = nodeEnum_to_string(arg_type);

        if (arg_type == 4 || arg_type == 5)
        {
            Symbol *nearest_symbol = lookup_symbol(current_symbol_table, func_arg->opr.op[0]->id.name);
            if (nearest_symbol == NULL)
            {

                printf("Error: Variable %s used before initialization\n", func_arg->opr.op[0]->id.name);
                fprintf(errors_file, "Error: Variable %s used before initialization\n", func_arg->opr.op[0]->id.name);
                return 0;
            }
            if (nearest_symbol->is_defined != 1)
            {

                printf("Error: Variable %s used before being defined.\n", func_arg->opr.op[0]->id.name);
                fprintf(errors_file, "Error: Variable %s used before being defined.\n", func_arg->opr.op[0]->id.name);
                return 0;
            }

            arg_type_str = func_arg->id.type;
        }
        if (strcmp(param_type, arg_type_str) != 0)
        {
            // Elevations
            if (strcmp(param_type, "float") == 0 && strcmp(arg_type_str, "int") == 0)
            {

                printf("Warning: Argument %d of function %s: Implicit conversion from int to float\n", 0, func_id->id.name);
                fprintf(errors_file, "Warning: Argument %d of function %s: Implicit conversion from int to float\n", 0, func_id->id.name);
            }
            else if (strcmp(param_type, "int") == 0 && strcmp(arg_type_str, "bool") == 0)
            {

                printf("Warning: Argument %d of function %s: Implicit conversion from bool to int\n", 0, func_id->id.name);
                fprintf(errors_file, "Warning: Argument %d of function %s: Implicit conversion from bool to int\n", 0, func_id->id.name);
            }
            else if (strcmp(param_type, "bool") == 0 && strcmp(arg_type_str, "int") == 0)
            {

                printf("Warning: Argument %d of function %s: Implicit conversion from int to bool\n", 0, func_id->id.name);
                fprintf(errors_file, "Warning: Argument %d of function %s: Implicit conversion from int to bool\n", 0, func_id->id.name);
            }
            else if (strcmp(param_type, "bool") == 0 && strcmp(arg_type_str, "float") == 0)
            {

                printf("Warning: Argument %d of function %s: Implicit conversion from float to bool\n", 0, func_id->id.name);
                fprintf(errors_file, "Warning: Argument %d of function %s: Implicit conversion from float to bool\n", 0, func_id->id.name);
            }
            else if (strcmp(param_type, "float") == 0 && strcmp(arg_type_str, "bool") == 0)
            {

                printf("Warning: Argument %d of function %s: Implicit conversion from bool to float\n", 0, func_id->id.name);
                fprintf(errors_file, "Warning: Argument %d of function %s: Implicit conversion from bool to float\n", 0, func_id->id.name);
            }
            else
            {

                printf("Error: Argument %d of function %s has type mismatch. Expected %s but got %s.\n",
                       0, func_id->id.name, param_type, arg_type_str);
                fprintf(errors_file, "Error: Argument %d of function %s has type mismatch. Expected %s but got %s.\n",
                        0, func_id->id.name, param_type, arg_type_str);
                return 0;
            }
        }
        return 1;
    }

    return 1;
}

int handle_switch_args(nodeType *switch_cases, Symbol *referenced_var)
{
    FILE *file = fopen("errors_and_warnings.txt", "a");
    if (switch_cases->opr.oper == SWITCH_CASES)
    {
        for (int i = 0; i < switch_cases->opr.nops; i++)
        {
            int handler = handle_switch_args(switch_cases->opr.op[i], referenced_var);
            if (handler == 0)
                return 0;
        }
    }
    else if (switch_cases->opr.oper == SWITCH_CASE)
    {
        // check on all common case types then process its body
        while (switch_cases->opr.op[1]->opr.oper == SWITCH_CASE)
        {
            nodeType *case_id = switch_cases->opr.op[0];
            if (case_id->type == typeIntCon || case_id->type == typeStringCon)
            {
                if (strcmp(referenced_var->type, nodeEnum_to_string(case_id->type)) != 0)
                {
                    printf("Error: Case value %s does not match switch variable type %s.\n", case_id->id.name, referenced_var->type);
                    fprintf(file, "Error: Case value %s does not match switch variable type %s.\n", case_id->id.name, referenced_var->type);
                    return 0;
                }
            }
            else if (case_id->type == typeConst)
            {
                Symbol *nearest_identifier = lookup_symbol(current_symbol_table, case_id->constant.name);
                if (nearest_identifier == NULL)
                {
                    printf("Error: Constant %s used in switch case is not declared.\n", case_id->constant.name);
                    fprintf(errors_file, "Error: Constant %s used in switch case is not declared.\n", case_id->constant.name);
                    return 0;
                }
                if (strcmp(nearest_identifier->type, referenced_var->type) != 0)
                {
                    printf("Error: Case value %s does not match switch variable type %s.\n", case_id->constant.name, referenced_var->type);
                    fprintf(errors_file, "Error: Case value %s does not match switch variable type %s.\n", case_id->constant.name, referenced_var->type);
                    return 0;
                }
            }
            else
            {
                printf("Error: Case value %s is not a valid type for switch statement.\n", case_id->id.name);
                fprintf(errors_file, "Error: Case value %s is not a valid type for switch statement.\n", case_id->id.name);
                return 0;
            }

            switch_cases = switch_cases->opr.op[1];
        }
        // case block
        create_symbol_table(&current_symbol_table);

        process_node(switch_cases->opr.op[1]);

        current_symbol_table = current_symbol_table->parent;
    }
    else if (switch_cases->opr.oper == DEFAULT_CASE)
    {
        create_symbol_table(&current_symbol_table);

        process_node(switch_cases->opr.op[0]);

        current_symbol_table = current_symbol_table->parent;
    }

    return 1;
}

int handle_expression(nodeType *node)
{

    if (!node)
        return 0;

    if (node->type == typeIntCon || node->type == typeFloatCon || node->type == typeBoolCon || node->type == typeStringCon)
        return node->type;

    if (node->type == typeId || node->type == typeConst)
    {
        Symbol *nearest_identifier = lookup_symbol(current_symbol_table, node->id.name);
        printf("test - ");

        if (nearest_identifier == NULL)
        {
            printf("Error: Variable %s used before initialization\n", node->id.name);
            fprintf(errors_file, "Error: Variable %s used before initialization\n", node->id.name);
            return -1;
        }
        if (nearest_identifier->is_defined != 1 && strcmp(nearest_identifier->kind, "parameter") != 0)
        {
            printf("Error: Variable %s used before being defined.\n", node->id.name);
            fprintf(errors_file, "Error: Variable %s used before being defined.\n", node->id.name);
            return -1;
        }
        node->id.sname = nearest_identifier->sname;

        if (strcmp(nearest_identifier->type, "int") == 0)
            return typeIntCon;
        else if (strcmp(nearest_identifier->type, "float") == 0)
            return typeFloatCon;
        else if (strcmp(nearest_identifier->type, "bool") == 0)
            return typeBoolCon;
        else if (strcmp(nearest_identifier->type, "string") == 0)
            return typeStringCon;
        else
        {
            printf("Error: Unknown type for variable %s\n", node->id.name);
            fprintf(errors_file, "Error: Unknown type for variable %s\n", node->id.name);
            return -1;
        }
        
        
    }

    int type1 = handle_expression(node->opr.op[0]);
    if (node->opr.nops == 1)
    {
        if (node->opr.oper == NOT)
        {
            if (type1 == typeBoolCon)
                return typeBoolCon;
            if (type1 == typeIntCon || type1 == typeFloatCon)
            {
                printf("Warning: Implicit conversion to bool in logical operation\n");
                fprintf(errors_file, "Warning: Implicit conversion to bool in logical operation\n");
                return typeBoolCon;
            }
            printf("Error: Type mismatch: %s\n", nodeEnum_to_string(type1));
            return -1;
        }
        else if (node->opr.oper == BIT_NOT)
        {
            if (type1 == typeIntCon)
                return typeIntCon;
            printf("Error: Bitwise NOT (~) is only valid for integers. Type mismatch: %s\n", nodeEnum_to_string(type1));
            fprintf(errors_file, "Error: Bitwise NOT (~) is only valid for integers. Type mismatch: %s\n", nodeEnum_to_string(type1));
            return -1;
        }
    }
    int type2 = handle_expression(node->opr.op[1]);

    switch (node->opr.oper)
    {
    case PLUS:
    case MINUS:
    case STAR:
        if (type1 == type2 && type1 != typeStringCon)
            return type1;
        if ((type1 == typeIntCon && type2 == typeFloatCon) || (type1 == typeFloatCon && type2 == typeIntCon))
        {
            printf("Warning: Implicit conversion from int to float\n");
            fprintf(errors_file, "Warning: Implicit conversion from int to float\n");
            return typeFloatCon;
        }
        if (type1 == typeIntCon && type2 == typeBoolCon)
        {
            printf("Warning: Implicit conversion from bool to int\n");
            fprintf(errors_file, "Warning: Implicit conversion from bool to int\n");
            return typeIntCon;
        }
        if (type1 == typeBoolCon && type2 == typeIntCon)
        {
            printf("Warning: Implicit conversion from int to bool\n");
            fprintf(errors_file, "Warning: Implicit conversion from int to bool\n");
            return typeBoolCon;
        }
        if (type1 == typeBoolCon && type2 == typeFloatCon)
        {
            printf("Warning: Implicit conversion from float to bool\n");
            fprintf(errors_file, "Warning: Implicit conversion from float to bool\n");
            return typeBoolCon;
        }
        if (type1 == typeFloatCon && type2 == typeBoolCon)
        {
            printf("Warning: Implicit conversion from bool to float\n");
            fprintf(errors_file, "Warning: Implicit conversion from bool to float\n");
            return typeFloatCon;
        }
        printf("Error: Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        fprintf(errors_file, "Error: Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        return -1;
        break;
    case SLASH:
        if(node->opr.op[1]->conI.value == 0){
            printf("Error: Division by zero\n");
            fprintf(errors_file, "Error: Division by zero\n");
        }
        if ((type1 == typeIntCon && type2 == typeFloatCon) || (type1 == typeFloatCon && type2 == typeIntCon))
        {
            printf("Warning: Implicit conversion from int to float in division\n");
            fprintf(errors_file, "Warning: Implicit conversion from int to float in division\n");
            return typeFloatCon;
        }
        if (type1 == typeIntCon && type2 == typeBoolCon)
        {
            printf("Warning: Implicit conversion from bool to float in division\n");
            fprintf(errors_file, "Warning: Implicit conversion from bool to float in division\n");
            return typeFloatCon;
        }
        if (type1 == typeBoolCon && type2 == typeIntCon)
        {
            printf("Warning: Implicit conversion from int to float in division\n");
            fprintf(errors_file, "Warning: Implicit conversion from int to float in division\n");
            return typeFloatCon;
        }
        if (type1 == typeBoolCon && type2 == typeFloatCon)
        {
            printf("Warning: Implicit conversion from bool to float in division\n");
            fprintf(errors_file, "Warning: Implicit conversion from bool to float in division\n");
            return typeFloatCon;
        }
        if (type1 == typeFloatCon && type2 == typeBoolCon)
        {
            printf("Warning: Implicit conversion from bool to float in division\n");
            fprintf(errors_file, "Warning: Implicit conversion from bool to float in division\n");
            return typeFloatCon;
        }
        if (type1 == type2 && type1 != typeStringCon)
            return typeFloatCon;
        printf("Error: Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        fprintf(errors_file, "Error: Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        return -1;
        break;

    case PERCENT:
        if (type1 == typeIntCon && type2 == typeIntCon)
            return typeIntCon;
        printf("Error: Modulus operator (%%) is only valid for integers. Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        fprintf(errors_file, "Error: Modulus operator (%%) is only valid for integers. Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        return -1;
        break;
    case AND:
    case OR:
    case EQ:
    case NEQ:
    case GT:
    case LT:
    case GE:
    case LE:
        if (type1 == typeBoolCon && type2 == typeBoolCon)
            return typeBoolCon;
        if ((type1 == typeBoolCon && (type2 == typeIntCon || type2 == typeFloatCon)) ||
            (type2 == typeBoolCon && (type1 == typeIntCon || type1 == typeFloatCon)))
        {
            return typeBoolCon;
        }
        if ((type1 == typeIntCon && type2 == typeIntCon) ||
            (type1 == typeFloatCon && type2 == typeFloatCon) ||
            (type1 == typeIntCon && type2 == typeFloatCon) ||
            (type1 == typeFloatCon && type2 == typeIntCon))
        {
            return typeBoolCon;
        }

        printf("Error: Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        fprintf(errors_file, "Error: Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        return -1;
        break;
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_NOT:
    case SHIFT_LEFT:
    case SHIFT_RIGHT:
        if (type1 == typeIntCon && type2 == typeIntCon)
            return typeIntCon;
        printf("Error: Bitwise operations are only valid for integers. Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        fprintf(errors_file, "Error: Bitwise operations are only valid for integers. Type mismatch: %s and %s\n", nodeEnum_to_string(type1), nodeEnum_to_string(type2));
        return -1;
        break;
    default:
        break;
    }

    return -1; // unknown operator
}

// returns 0 -> for ending depth
/*
    In case of assign we do not allow processing children nodes, we process the the node totally till end in a single process_node call
*/
int handle_single_node(nodeType *node)
{
    if(!node) return 0;
    switch (node->type)
    {
    case typeIntCon:
    case typeFloatCon:
    case typeBoolCon:
    case typeStringCon:
        return 0;
        break;
    case typeId:
    {
        int val = variable_redeclaration_val(current_symbol_table, node->id.name);
        if (val == 0)
        {
            printf("Error: Variable %s redefinition\n", node->id.name);
            fprintf(errors_file, "Error: Variable %s redefinition\n", node->id.name);
            return 0;
        }
        Symbol *sym = insert_symbol(current_symbol_table, node->id.name, node->id.type, strdup("variable"));
        sym->is_defined = false;
        char* tmp = (char*)malloc(100);
        sprintf(tmp, "%s@s%d", node->id.name, sym->parent->symbol_table_no);
        sym->sname = tmp;
        node->id.sname = tmp;

        return 0;
        break;
    }
    case typeOpr:
        switch (node->opr.oper)
        {
        case ASSIGN:
        case PLUS_ASSIGN:
        case MINUS_ASSIGN:
        case STAR_ASSIGN:
        case SLASH_ASSIGN:
        {

            nodeType *first_op = node->opr.op[0];  // id / const
            nodeType *second_op = node->opr.op[1]; // expression / constant

            // leftside type
            char *holder_kind = strdup("variable");
            if (first_op->type == typeConst)
                holder_kind = strdup("constant");

            char *holder_name = strcmp(holder_kind, "variable") == 0 ? first_op->id.name : first_op->constant.name;
            char *holder_type = strcmp(holder_kind, "variable") == 0 ? first_op->id.type : strdup("undefined");

            // rightside handler
            switch (second_op->type)
            {
            case typeIntCon:
            case typeBoolCon:
            case typeStringCon:
            case typeFloatCon:
            {
                char *value_type = strdup(
                    second_op->type == typeIntCon     ? "int"
                    : second_op->type == typeFloatCon ? "float"
                    : second_op->type == typeBoolCon  ? "bool"
                                                      : "string");

                if (node->opr.oper == SLASH_ASSIGN && ((second_op->type == typeIntCon && second_op->conI.value == 0) ||
                                                       (second_op->type == typeFloatCon && second_op->conF.value == 0.0)))
                {
                    printf("Error: Division by zero\n");
                    fprintf(errors_file, "Error: Division by zero\n");
                    return 0;
                }

                if (strcmp(holder_type, "undefined") == 0)
                {
                    if (strcmp(holder_kind, "constant") == 0)
                    {
                        int val = variable_redeclaration_val(current_symbol_table, first_op->constant.name);
                        if (val == 0)
                        {
                            printf("Error: Variable %s redefinition\n", first_op->constant.name);
                            fprintf(errors_file, "Error: Variable %s redefinition\n", first_op->constant.name);
                            return 0;
                        }

                        Symbol *sym = insert_symbol(current_symbol_table, holder_name, value_type, holder_kind);
                        sym->is_defined = 1;
                        sym->is_used = 0;

                        char* tmp = (char*)malloc(100);
                        sprintf(tmp, "%s@s%d", holder_name, sym->parent->symbol_table_no);
                        sym->sname = tmp;
                        first_op->constant.sname = tmp;
                    }
                    else
                    {
                        // reassignment
                        Symbol *nearest_identifier = lookup_symbol(current_symbol_table, holder_name);
                        if (nearest_identifier == NULL)
                        {
                            printf("Error: Variable %s used before initialization\n", holder_name);
                            fprintf(errors_file, "Error: Variable %s used before initialization\n", holder_name);
                            return 0;
                        }

                        if (strcmp(nearest_identifier->kind, "constant") == 0)
                        {
                            printf("Error: Constant %s cannot be reassigned\n", holder_name);
                            fprintf(errors_file, "Error: Constant %s cannot be reassigned\n", holder_name);
                        }

                        if (strcmp(nearest_identifier->type, value_type) != 0)
                        {
                            // Elevations
                            if (strcmp(nearest_identifier->type, "float") == 0 && strcmp(value_type, "int") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "int") == 0 && strcmp(value_type, "bool") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "bool") == 0 && strcmp(value_type, "int") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "bool") == 0 && strcmp(value_type, "float") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "float") == 0 && strcmp(value_type, "bool") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                            }
                            else
                            {
                                printf("Error: Type mismatch: %s and %s\n", nearest_identifier->type, value_type);
                                fprintf(errors_file, "Error: Type mismatch: %s and %s\n", nearest_identifier->type, value_type);
                                return 0;
                            }
                        }

                        nearest_identifier->is_defined = 1;
                        first_op->id.sname = nearest_identifier->sname;
                    }
                }
                else
                {

                    int val = variable_redeclaration_val(current_symbol_table, first_op->id.name);

                    if (val == 0)
                    {
                        printf("Error: Variable %s redefinition\n", first_op->id.name);
                        fprintf(errors_file, "Error: Variable %s redefinition\n", first_op->id.name);
                        return 0;
                    }
                    if (strcmp(holder_type, value_type) != 0)
                    {
                        // Elevations
                        if (strcmp(holder_type, "float") == 0 && strcmp(value_type, "int") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                        }
                        else if (strcmp(holder_type, "int") == 0 && strcmp(value_type, "bool") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                        }
                        else if (strcmp(holder_type, "bool") == 0 && strcmp(value_type, "int") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                        }
                        else if (strcmp(holder_type, "bool") == 0 && strcmp(value_type, "float") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                        }
                        else if (strcmp(holder_type, "float") == 0 && strcmp(value_type, "bool") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                        }
                        else
                        {
                            printf("Error: Type mismatch: %s and %s\n", holder_type, value_type);
                            fprintf(errors_file, "Error: Type mismatch: %s and %s\n", holder_type, value_type);
                            return 0;
                        }
                    }
                    Symbol *sym = insert_symbol(current_symbol_table, holder_name, holder_type, holder_kind);
                    sym->is_defined = 1;
                    sym->is_used = 0; // initially

                    char* tmp = (char*)malloc(100);
                    sprintf(tmp, "%s@s%d", holder_name, sym->parent->symbol_table_no);
                    sym->sname = tmp;
                    first_op->id.sname = tmp;
                }
                break;
            }
            default:
            {

                // other expression
                int expression_type = second_op->opr.oper == FUNC_CALL ? -2 : handle_expression(second_op);
                char *value_type = second_op->opr.oper == FUNC_CALL ? strdup("function_call") : strdup(nodeEnum_to_string(expression_type));
                if (second_op->opr.oper == FUNC_CALL)
                {
                    
                    Symbol *nearest_identifier = lookup_symbol(current_symbol_table, second_op->opr.op[0]->opr.op[0]->id.name);
                    if (nearest_identifier == NULL)
                    {
                        printf("Error: Function %s used before initialization\n", holder_name);
                        fprintf(errors_file, "Error: Function %s used before initialization\n", holder_name);
                        return 0;
                    }

                    if (nearest_identifier->is_defined != 1)
                    {
                        printf("Error: Function %s used before being defined.\n", second_op->opr.op[0]->opr.op[0]->id.name);
                        fprintf(errors_file, "Error: Function %s used before being defined.\n", second_op->opr.op[0]->opr.op[0]->id.name);
                        return 0;
                    }

                    if (nearest_identifier->type && strcmp(nearest_identifier->type, "void") == 0)
                    {
                        printf("Error: Function %s returns void, cannot be assigned.\n", holder_name);
                        fprintf(errors_file, "Error: Function %s returns void, cannot be assigned.\n", holder_name);
                        return 0;
                    }
                    nearest_identifier->is_used = 1;
                    handle_single_node(second_op);

                    value_type = nearest_identifier->type;

                    second_op->opr.op[0]->opr.op[0]->id.sname = nearest_identifier->sname;
                }
                if (expression_type == -1)
                {
                    printf("Error: Type mismatch: %s and %s\n", holder_type, value_type);
                    fprintf(errors_file, "Error: Type mismatch: %s and %s\n", holder_type, value_type);
                    return 0;
                }
                if (strcmp(holder_type, "undefined") == 0)
                {
                    if (strcmp(holder_kind, "constant") == 0)
                    {
                        int val = variable_redeclaration_val(current_symbol_table, first_op->constant.name);
                        if (val == 0)
                        {
                            printf("Error: Variable %s redefinition\n", first_op->constant.name);
                            fprintf(errors_file, "Error: Variable %s redefinition\n", first_op->constant.name);
                            return 0;
                        }

                        Symbol *sym = insert_symbol(current_symbol_table, holder_name, value_type, holder_kind);
                        sym->is_defined = 1;
                        sym->is_used = 0;

                        char* tmp = (char*)malloc(100);
                        sprintf(tmp, "%s@s%d", holder_name, sym->parent->symbol_table_no);
                        sym->sname = tmp;
                        first_op->constant.sname = tmp;
                    }
                    else
                    {
                        // reassignment
                        Symbol *nearest_identifier = lookup_symbol(current_symbol_table, holder_name);
                        
                        if (nearest_identifier == NULL)
                        {
                            printf("Error: Variable %s used before initialization\n", holder_name);
                            fprintf(errors_file, "Error: Variable %s used before initialization\n", holder_name);
                            return 0;
                        }

                        if (strcmp(nearest_identifier->kind, "constant") != 0)
                        {
                            printf("Error: Constant %s cannot be reassigned\n", holder_name);
                            fprintf(errors_file, "Error: Constant %s cannot be reassigned\n", holder_name);
                        }

                        if (strcmp(nearest_identifier->type, value_type) != 0)
                        {
                            // Elevations
                            if (strcmp(nearest_identifier->type, "float") == 0 && strcmp(value_type, "int") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "int") == 0 && strcmp(value_type, "bool") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "bool") == 0 && strcmp(value_type, "int") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "bool") == 0 && strcmp(value_type, "float") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                            }
                            else if (strcmp(nearest_identifier->type, "float") == 0 && strcmp(value_type, "bool") == 0)
                            {
                                printf("Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                                fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                            }
                            else
                            {
                                printf("Error: Type mismatch: %s and %s\n", nearest_identifier->type, value_type);
                                fprintf(errors_file, "Error: Type mismatch: %s and %s\n", nearest_identifier->type, value_type);
                                return 0;
                            }
                        }

                        nearest_identifier->is_defined = 1;
                        first_op->id.sname = nearest_identifier->sname;
                    }
                }
                else
                {
                    int val = variable_redeclaration_val(current_symbol_table, first_op->id.name);
                    if (val == 0)
                    {
                        printf("Error: Variable %s redefinition\n", first_op->id.name);
                        fprintf(errors_file, "Error: Variable %s redefinition\n", first_op->id.name);
                        return 0;
                    }

                    if (strcmp(holder_type, value_type) != 0)
                    {
                        // Elevations
                        if (strcmp(holder_type, "float") == 0 && strcmp(value_type, "int") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to float\n", holder_name);
                        }
                        else if (strcmp(holder_type, "int") == 0 && strcmp(value_type, "bool") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to int\n", holder_name);
                        }
                        else if (strcmp(holder_type, "bool") == 0 && strcmp(value_type, "int") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from int to bool\n", holder_name);
                        }
                        else if (strcmp(holder_type, "bool") == 0 && strcmp(value_type, "float") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from float to bool\n", holder_name);
                        }
                        else if (strcmp(holder_type, "float") == 0 && strcmp(value_type, "bool") == 0)
                        {
                            printf("Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                            fprintf(errors_file, "Warning: Variable (%s): Implicit conversion from bool to float\n", holder_name);
                        }
                        else
                        {
                            printf("Error: Type mismatch: %s and %s\n", holder_type, value_type);
                            fprintf(errors_file, "Error: Type mismatch: %s and %s\n", holder_type, value_type);
                            return 0;
                        }
                    }

                    Symbol *sym = insert_symbol(current_symbol_table, holder_name, holder_type, holder_kind);
                    sym->is_defined = 1;

                    char* tmp = (char*)malloc(100);
                    sprintf(tmp, "%s@s%d", holder_name, sym->parent->symbol_table_no);
                    sym->sname = tmp;
                    first_op->id.sname = tmp;
                }
                break;
            }
            }
            return 0;
            break;
        }
        case INCREMENT_PREFIX:
        case DECREMENT_PREFIX:
        case INCREMENT_POSTFIX:
        case DECREMENT_POSTFIX:
        {
            nodeType *operand = node->opr.op[0];
            if (operand->type != typeId)
            {
                printf("Error: Increment/Decrement operations are only valid for variables.\n");
                fprintf(errors_file, "Error: Increment/Decrement operations are only valid for variables.\n");
                return 0;
            }

            Symbol *nearest_identifier = lookup_symbol(current_symbol_table, operand->id.name);
            if (nearest_identifier == NULL)
            {
                printf("Error: Variable %s used before initialization.\n", operand->id.name);
                fprintf(errors_file, "Error: Variable %s used before initialization.\n", operand->id.name);
                return 0;
            }
            nearest_identifier->is_used = 1;

            if (strcmp(nearest_identifier->type, "int") != 0 && strcmp(nearest_identifier->type, "float") != 0)
            {
                printf("Error: Increment/Decrement operations are only valid for int or float types. Variable %s has type %s.\n",
                       operand->id.name, nearest_identifier->type);
                fprintf(errors_file, "Error: Increment/Decrement operations are only valid for int or float types. Variable %s has type %s.\n",
                        operand->id.name, nearest_identifier->type);
                return 0;
            }
            return 0;
            break;
        }
        case FUNC:
        {
            nodeType *func_id = node->opr.op[0]->opr.op[0];
            const int isPrototype = node->opr.nops == 3;
            nodeType *func_args = node->opr.op[1];
            Symbol *function_sym = NULL;
            const int paramCount = func_args->opr.nops;
            // insertion of function symbol
            Symbol *nearest_identifier = lookup_symbol_same_scope(current_symbol_table, func_id->id.name);
            if (nearest_identifier != NULL)
            {
                if (strcmp(nearest_identifier->kind, "function") != 0)
                {
                    printf("Error: Can't use %s as function name as it's already used.\n", func_id->id.name);
                    fprintf(errors_file, "Error: Can't use %s as function name as it's already used.\n", func_id->id.name);
                    return 0;
                }
                if (nearest_identifier->is_defined == 1)
                {
                    printf("Error: Function %s redefinition or function prototyping after the actual implementation.\n", func_id->id.name);
                    fprintf(errors_file, "Error: Function %s redefinition or function prototyping after the actual implementation.\n", func_id->id.name);
                    return 0;
                }
                if (nearest_identifier->param_count != paramCount)
                {
                    printf("Error: Function %s has %d parameters, but was declared with %d parameters.\n", func_id->id.name, nearest_identifier->param_count, paramCount);
                    fprintf(errors_file, "Error: Function %s has %d parameters, but was declared with %d parameters.\n", func_id->id.name, nearest_identifier->param_count, paramCount);
                    return 0;
                }
                if (nearest_identifier->type != NULL && strcmp(nearest_identifier->type, func_id->id.type) != 0)
                {
                    printf("Error: Function %s has type %s, but was declared with type %s.\n", func_id->id.name, nearest_identifier->type, func_id->id.type);
                    fprintf(errors_file, "Error: Function %s has type %s, but was declared with type %s.\n", func_id->id.name, nearest_identifier->type, func_id->id.type);
                    return 0;
                }
            
                func_id->id.sname = nearest_identifier->sname;
            }
            else
            {
                function_sym = insert_symbol(current_symbol_table, func_id->id.name, func_id->id.type, "function");
                function_sym->param_count = paramCount;
                function_sym->is_defined = isPrototype;
                function_sym->is_used = 0;
                char* tmp = (char*)malloc(100);
                printf("test %d\n", function_sym->parent == NULL);
                sprintf(tmp, "%s@s%d", func_id->id.name, function_sym->parent->symbol_table_no);
                function_sym->sname = tmp;
                func_id->id.sname = tmp;

                create_symbol_table(&current_symbol_table);
                function_sym->sub_block_table = current_symbol_table;
            }

            int handler = handle_func_args(func_args, nearest_identifier, func_id);
            if (handler == 0 && paramCount != 0)
                return 0;
            
            if (function_sym != NULL)
                function_sym->param_count = handler;

            if (node->opr.nops == 3)
            {

                if (node->opr.op[2]->opr.op[0]->opr.nops > 0)
                {

                    if (nearest_identifier != NULL)
                        current_symbol_table = nearest_identifier->sub_block_table;

                    nodeType *func_body_block_sl = node->opr.op[2]->opr.op[0]->opr.op[0];
                    process_node(func_body_block_sl);

                    if (nearest_identifier != NULL)
                        current_symbol_table = current_symbol_table->parent;
                }
            }

            if (nearest_identifier != NULL)
                nearest_identifier->is_defined = 1;
            else
                current_symbol_table = current_symbol_table->parent;

            // print_symbol_table(current_symbol_table);
            return 0;
            break;
        }
        case FUNC_CALL:
        {

            nodeType *func_id = node->opr.op[0]->opr.op[0];
            Symbol *nearest_function = lookup_symbol(current_symbol_table, func_id->id.name);
            if (nearest_function == NULL || strcmp(nearest_function->kind, "function") != 0)
            {
                printf("Error: Function %s not declared or not a valid function.\n", func_id->id.name);
                fprintf(errors_file, "Error: Function %s not declared or not a valid function.\n", func_id->id.name);
                return 0;
            }
            
            if (nearest_function->is_defined == 0)
            {
                printf("Error: Function %s is declared but not defined.\n", func_id->id.name);
                fprintf(errors_file, "Error: Function %s is declared but not defined.\n", func_id->id.name);
                return 0;
            }
            nodeType *func_arg = node->opr.op[1];
            if (func_arg->opr.nops == 0)
            {
                if (nearest_function->param_count != 0)
                {
                    printf("Error: Function %s expects %d arguments, but none were provided.\n", func_id->id.name, nearest_function->param_count);
                    fprintf(errors_file, "Error: Function %s expects %d arguments, but none were provided.\n", func_id->id.name, nearest_function->param_count);
                    return 0;
                }
                return 0;
            }
            if(nearest_function->param_count == 0 && func_arg->opr.nops != 0){
                printf("Error: Function %s expects %d arguments, but more were provided.\n", func_id->id.name, nearest_function->param_count);
                fprintf(errors_file, "Error: Function %s expects %d arguments, but more were provided.\n", func_id->id.name, nearest_function->param_count);
                return 0;
            }
            nearest_function->is_used = 1;

            
            // int handler = handle_func_call_args(func_arg, nearest_function, func_id);
            // if (handler == 0)
            //     return 0;

            // if (nearest_function->param_count != handler)
            // {
            //     printf("Error: Function %s expects %d arguments, but %d were provided.\n", func_id->id.name, nearest_function->param_count, handler);
            //     fprintf(errors_file, "Error: Function %s expects %d arguments, but %d were provided.\n", func_id->id.name, nearest_function->param_count, handler);
            //     return 0;
            // }

            return 0;
            break;
        }
        case FOR:
        {

            nodeType *for_cond = node->opr.op[0];
            nodeType *for_init = for_cond->opr.op[0];
            nodeType *for_term = for_cond->opr.op[1];
            nodeType *for_step = for_cond->opr.op[2];

            create_symbol_table(&current_symbol_table);

            // handle init
            Symbol *sym = insert_symbol(current_symbol_table, for_init->opr.op[0]->opr.op[0]->id.name, for_init->opr.op[0]->opr.op[0]->id.type, "parameter");
            sym->is_defined = 1;
            char* tmp = (char*)malloc(100);
            sprintf(tmp, "%s@s%d", for_init->opr.op[0]->opr.op[0]->id.name, sym->parent->symbol_table_no);
            sym->sname = tmp;
            for_init->opr.op[0]->opr.op[0]->id.sname = tmp;
            // handle term
            int term_type = handle_expression(for_term->opr.op[0]);
            if (term_type != typeBoolCon && term_type != typeIntCon && term_type != typeFloatCon)
            {
                printf("Error: For loop termination condition must be of type bool, int or float.\n");
                fprintf(errors_file, "Error: For loop termination condition must be of type bool, int or float.\n");
                return 0;
            }

            // handle step
            handle_single_node(for_step);

            if (node->opr.nops == 2)
            {

                // handle body
                nodeType *for_body = node->opr.op[1]->opr.op[0];
                if (for_body->opr.oper == BLOCK)
                    for_body = for_body->opr.op[0];
                process_node(for_body);
            }

            current_symbol_table = current_symbol_table->parent;

            return 0;
            break;
        }
        case SWITCH:
        {
            nodeType *switch_var = node->opr.op[0];
            nodeType *switch_body = node->opr.op[1];

            // validate on switch_var
            Symbol *referenced_var = lookup_symbol(current_symbol_table, switch_var->opr.op[0]->id.name);
            if (referenced_var == NULL)
            {
                printf("Error: Variable %s used in switch statement is not declared.\n", switch_var->opr.op[0]->id.name);
                fprintf(errors_file, "Error: Variable %s used in switch statement is not declared.\n", switch_var->opr.op[0]->id.name);
                return 0;
            }

            if (strcmp(referenced_var->type, "int") != 0 && strcmp(referenced_var->type, "string") != 0)
            {
                printf("Error: Switch statement variable %s must be of type int or string, but got %s.\n", switch_var->opr.op[0]->id.name, referenced_var->type);
                fprintf(errors_file, "Error: Switch statement variable %s must be of type int or string, but got %s.\n", switch_var->opr.op[0]->id.name, referenced_var->type);
                return 0;
            }

            char *switch_var_type = strdup(referenced_var->type);

            // switch_body
            nodeType *switch_cases = switch_body->opr.op[0];
            nodeType *default_case = switch_body->opr.op[1];
            int handler = handle_switch_args(switch_cases, referenced_var);
            if (node->opr.nops == 3)
            {
                // default case
                int def_handler = handle_switch_args(default_case, referenced_var);
            }

            print_symbol_table(current_symbol_table);
            return 0;
            break;
        }
        case COND:
        {
            nodeType *cond = node->opr.op[0];
            int expression_type_val = handle_expression(cond);

            if (expression_type_val == -1)
            {
                printf("Error: Invalid expression type.\n");
                fprintf(errors_file, "Error: Invalid expression type.\n");
                return 0;
            }
            // here we terminate not globally on IF but on the cond
            return 0;
            break;
        }
        case RETURN:
            if(node->opr.nops > 0){
                if(node->opr.op[0]->opr.oper == FUNC_CALL){
                    Symbol *nearest_identifier = lookup_symbol(current_symbol_table, node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                    if (nearest_identifier == NULL)
                    {
                        printf("Error: Function %s called before initialization\n", node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                        fprintf(errors_file, "Error: Function %s called before initialization\n", node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                        return 0;
                    }

                    if (nearest_identifier->is_defined != 1)
                    {
                        printf("Error: Function %s called before being defined.\n", node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                        fprintf(errors_file, "Error: Function %s called before being defined.\n", node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                        return 0;
                    }

                    if (nearest_identifier->type && strcmp(nearest_identifier->type, "void") == 0)
                    {
                        printf("Error: Function %s returns void, cannot be assigned.\n", node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                        fprintf(errors_file, "Error: Function %s returns void, cannot be assigned.\n", node->opr.op[0]->opr.op[0]->opr.op[0]->id.name);
                        return 0;
                    }
                    nearest_identifier->is_used = 1;
                    handle_single_node(node->opr.op[0]);


                    node->opr.op[0]->opr.op[0]->opr.op[0]->id.sname = nearest_identifier->sname;
                }else{
                    int expression_type_val = handle_expression(node->opr.op[0]);
    
                    if (expression_type_val == -1)
                    {
                        printf("Error: Invalid expression type.\n");
                        fprintf(errors_file, "Error: Invalid expression type.\n");
                        return 0;
                    }
                }
            }
            return 0;
            break;
        case AND:
        case OR:
        case EQ:
        case NEQ:
        case GT:
        case LT:
        case GE:
        case LE:
        case BIT_AND:
        case BIT_OR:
        case BIT_XOR:
        case BIT_NOT:
        case SHIFT_LEFT:
        case SHIFT_RIGHT:
        case PLUS:
        case MINUS:
        case STAR:
        case SLASH:
        {
            if(node->opr.oper == SLASH && node->opr.op[1]->conI.value == 0){
                printf("Error: Division by zero\n");
                fprintf(errors_file, "Error: Division by zero\n");
            }
            int expression_type_val = handle_expression(node);
            if (expression_type_val == -1)
            {
                printf("Error: Invalid expression type.\n");
                fprintf(errors_file, "Error: Invalid expression type.\n");
                return 0;
            }
            return 0;
            break;
        }
        default:
            break;
        }
    default:
        break;
    }

    return 1;
}

void process_node(nodeType *node)
{
    if (!node)
        return;
    // for blocks
    if (node->type == typeOpr)
        if (node->opr.oper == BLOCK)
            create_symbol_table(&current_symbol_table);

    // printf("type = %d, oper = %d\n", (int)node->type, node->opr.oper == RETURN);
    printf("type = %d, oper = %d (%d)\n", (int)node->type, node->opr.oper == RETURN, node->opr.oper);
    int cont = handle_single_node(node);
    if (cont != 0)
    {
        for (int i = 0; i < node->opr.nops; i++)
        {
            // special case: non-block if/else/while/repeat-until body
            if (node->opr.oper == IF || node->opr.oper == IFELSE || node->opr.oper == ITER_BODY)
                if (node->opr.op[i]->opr.oper != COND && node->opr.op[i]->opr.oper != BLOCK)
                    create_symbol_table(&current_symbol_table);

            process_node(node->opr.op[i]);

            if (node->opr.oper == IF || node->opr.oper == IFELSE || node->opr.oper == ITER_BODY)
                if (node->opr.op[i]->opr.oper != COND && node->opr.op[i]->opr.oper != BLOCK)
                    current_symbol_table = current_symbol_table->parent;
        }
    }
    // for blocks
    if (node->type == typeOpr)
        if (node->opr.oper == BLOCK)
            current_symbol_table = current_symbol_table->parent;
}

void semantic_check(nodeType *topNode)
{
    // Initialization
    global_symbol_table = initialize_global_symbol_table(global_symbol_table, current_symbol_table);
    current_symbol_table = global_symbol_table;

    errors_file = fopen("errors_and_warnings.txt", "w");
    if (errors_file == NULL)
    {
        perror("Error opening file");
        return;
    }
    fprintf(errors_file, "");
    errors_file = fopen("errors_and_warnings.txt", "a");
    
    track_scope(current_symbol_table);
    process_node(topNode);

    printf("tracked tables");
    print_all_tracked_symbol_tables();

    fclose(errors_file);

    // cleaning
    cleanup_all_symbol_tables();
}