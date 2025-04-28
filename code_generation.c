#include "code_generation.h"
#include "semantic.h"

char* helper_parent = "none";
char* helper_variable = "none";
static int statement_counter = 0;

FILE *file;

struct code_generation_data
{
    int counter;
    char *op;
    char *arg1;
    char *arg2;
    char *result;
};

struct code_generation_data **code_generation_data_list = NULL;
int code_generation_data_list_size = 0;

int code_generation_data_list_count = 0;

void add_label(char *label, char *postfix)
{
    if (file != NULL)
    {
        fprintf(file,
                " %s%s\n",
                strdup(label), strdup(postfix));
    }
    else
    {
        perror("Error opening file");
    }
}

int add_code_generation_data(char *op, char *arg1, char *arg2, char *result)
{
    // FILE* file = fopen("quadruples.txt", "a");
    if (file != NULL)
    {
        fprintf(file,
                "[ %3d ] ( %15s , %15s , %15s , %15s )\n",
                code_generation_data_list_count++,
                op,
                arg1,
                arg2,
                result);
        // fclose(file);
    }
    else
    {
        perror("Error opening file");
    }

    return code_generation_data_list_count;
}

void print_quadruples()
{
    for (int i = 0; i < code_generation_data_list_size; i++)
    {
        struct code_generation_data *quad = code_generation_data_list[i];
        if (quad != NULL)
        {
            printf("[ %3d ] ( %s , %s , %s , %s )\n",
                   quad->counter,
                   quad->op,
                   quad->arg1,
                   quad->arg2,
                   quad->result);
        }
    }
}

char *handle_quad_expression(nodeType *node)
{
    if (!node)
        return NULL;

    if (node->type == typeConst)
    {
        return strdup(node->constant.sname);
    }

    if (node->type == typeId)
    {
        printf("ttteessttt__%s\n", node->id.sname);

        return strdup(node->id.sname);
    }

    if (node->type == typeIntCon)
    {
        char *result = (char *)malloc(20);
        sprintf(result, "s%d", statement_counter++);
        char value[20];
        sprintf(value, "%d", node->conI.value);
        add_code_generation_data("=", value, strdup("_"), result);
        return result;
    }
    else if (node->type == typeFloatCon)
    {
        char *result = (char *)malloc(20);
        sprintf(result, "s%d", statement_counter++);
        char value[20];
        sprintf(value, "%f", node->conF.value);
        add_code_generation_data("=", value, strdup("_"), result);
        return result;
    }
    else if (node->type == typeBoolCon)
    {
        char *result = (char *)malloc(20);
        sprintf(result, "s%d", statement_counter++);
        const char *value = node->conB.value ? "true" : "false";
        add_code_generation_data("=", (char *)value, strdup("_"), result);
        return result;
    }
    else if (node->type == typeStringCon)
    {
        char *result = (char *)malloc(20);
        sprintf(result, "s%d", statement_counter++);
        add_code_generation_data("=", node->conS.value, strdup("_"), result);
        return result;
    }

    if (node->type == typeOpr)
    {


        char *result = (char *)malloc(20);
        sprintf(result, "s%d", statement_counter++);

        if (node->opr.oper == FUNC_CALL)
        {
            char nops_str[20];
            if(node->opr.op[1]->opr.nops == 0){
                sprintf(nops_str, "%d", 0);
            }else{
                sprintf(nops_str, "%d", count_func_call_args(node->opr.op[1]));
            }
            
            add_code_generation_data(strdup("CALL"), node->opr.op[0]->opr.op[0]->id.name, nops_str, result);
            return result;
        }
        
        char *arg1 = handle_quad_expression(node->opr.op[0]);
        char *arg2 = NULL;

        printf("test__--%d\n", node->opr.oper == PLUS);

        if (node->opr.nops == 2)
            arg2 = handle_quad_expression(node->opr.op[1]);

        switch (node->opr.oper)
        {
        case PLUS:
            add_code_generation_data(strdup("+"), arg1, arg2, result);
            break;
        case MINUS:
            add_code_generation_data(strdup("-"), arg1, arg2, result);
            break;
        case STAR:
            add_code_generation_data(strdup("*"), arg1, arg2, result);
            break;
        case SLASH:
            add_code_generation_data(strdup("/"), arg1, arg2, result);
            break;
        case PERCENT:
            add_code_generation_data(strdup("%"), arg1, arg2, result);
            break;
        case AND:
            add_code_generation_data(strdup("&&"), arg1, arg2, result);
            break;
        case OR:
            add_code_generation_data(strdup("||"), arg1, arg2, result);
            break;
        case EQ:
            add_code_generation_data(strdup("=="), arg1, arg2, result);
            break;
        case NEQ:
            add_code_generation_data(strdup("!="), arg1, arg2, result);
            break;
        case GT:
            add_code_generation_data(strdup(">"), arg1, arg2, result);
            break;
        case LT:

            add_code_generation_data(strdup("<"), arg1, arg2, result);
            break;
        case GE:
            add_code_generation_data(strdup(">="), arg1, arg2, result);
            break;
        case LE:
            add_code_generation_data(strdup("<="), arg1, arg2, result);
            break;
        case NOT:
            add_code_generation_data(strdup("!"), arg1, "_", result);
            break;
        case BIT_AND:
            add_code_generation_data(strdup("&"), arg1, arg2, result);
            break;
        case BIT_OR:
            add_code_generation_data(strdup("|"), arg1, arg2, result);
            break;
        case BIT_XOR:
            add_code_generation_data(strdup("^"), arg1, arg2, result);
            break;
        case BIT_NOT:
            add_code_generation_data(strdup("~"), arg1, "_", result);
            break;
        case SHIFT_LEFT:
            add_code_generation_data(strdup("<<"), arg1, arg2, result);
            break;
        case SHIFT_RIGHT:
            add_code_generation_data(strdup(">>"), arg1, arg2, result);
            break;
        default:
            printf("Error(%d): Unknown operator\n", node->opr.oper);
            return NULL;
        }

        return result;
    }

    return NULL; // unknown node type
}

int count_func_call_args(nodeType *func_arg)
{
    if (func_arg->opr.oper == ARG_VALUES)
    {
        int sum = 0;

        for (int i = 0; i < func_arg->opr.nops; i++)
        {
            sum += count_func_call_args(func_arg->opr.op[i]);
        }
        return sum;
    }
    else if (func_arg->opr.oper == ARG_VALUE)
    {
        return 1;
    }

    return 1;

}

int count_quad_expression(nodeType *node)
{
    if (!node)
        return 0;

    if (node->type == typeConst || node->type == typeId || node->type == typeIntCon ||
        node->type == typeFloatCon || node->type == typeBoolCon || node->type == typeStringCon)
    {
        return 1;
    }

    if (node->type == typeOpr)
    {
        int sum = 0;
        sum += count_quad_expression(node->opr.op[0]);

        if (node->opr.nops == 2)
            sum += count_quad_expression(node->opr.op[1]);

        return sum;
    }

    return 1; // unknown node type
}

void patch_quad_placeholder(const char *filename, int target_line, const char *new_txt) {
    fclose(file);
    file = fopen(filename, "r+");
    if (!file) {
        perror("patch: fopen");
        return;
    }

    char linebuf[512];
    int  lineno = 0;
    while (fgets(linebuf, sizeof linebuf, file)) {
        lineno++;
        if (lineno == target_line) {
            // find the placeholder
            char *q = strstr(linebuf, "????");
            if (!q) {
                fprintf(stderr, "patch: no placeholder on line %d\n", lineno);
                break;
            }
            // compute file‐offset of the first '?'
            long line_start = ftell(file) - strlen(linebuf);
            long placeholder_pos = line_start + (q - linebuf) - 1;

            // build a 4-char replacement, right-aligned
            char buf[5] = {' ',' ',' ',' ','\0'};
            int  n = strlen(new_txt);
            if (n > 4) n = 4;
            memcpy(buf + (4 - n), new_txt, n);

            // seek & overwrite
            if (fseek(file, placeholder_pos, SEEK_SET) != 0) {
                perror("patch: fseek");
            } else if (fwrite(buf, 1, 4, file) != 4) {
                perror("patch: fwrite");
            }
            break;
        }
    }

    fclose(file);
    file = fopen("quadruples.txt", "a");
}

int handle_single_node_quad(nodeType *node)
{
    if(!node) return 0;
    switch (node->type)
    {
    case typeId:
        char result[20];
        sprintf(result, "s%d", statement_counter++);
        add_code_generation_data(strdup("DECL"), strdup("_"), strdup("_"), strdup(node->id.sname));
        return 0;
        break;
    case typeConst:
        char result2[20];
        sprintf(result2, "s%d", statement_counter++);
        add_code_generation_data(strdup("DCON"), strdup(node->constant.sname), strdup("_"), result2);
        return 0;
        break;
    case typeOpr:
    {
        switch (node->opr.oper)
        {
        case FUNC:

            if (node->opr.nops == 2)
                return 0;
            add_label(node->opr.op[0]->opr.op[0]->id.name, ":");
            code_generation_data_list_count++;


            return 1;
            break;
        case FUNC_ID:
            return 0;
            break;
        case FUNC_ARG:
        {
            nodeType *arg = node->opr.op[0];
            add_code_generation_data(strdup("ARG"), strdup("_"), strdup("_"), arg->id.name);

            return 0;
            break;
        }
        case FUNC_CALL:
        {
            handle_quad_expression(node);
            return 0;
            break;
        }
        case CONTINUE:
        {
            if (strcmp(helper_parent, "iter") == 0){
                add_code_generation_data(strdup("CONTINUE"), strdup("_"), strdup("_"), strdup("_"));
            }else{
                printf("Error: CONTINUE statement not inside a loop.\n");
                return 0;
            }
            return 0;
            break;
        }
        case BREAK:
        {
            if (strcmp(helper_parent, "iter") == 0 || strcmp(helper_parent, "switch") == 0) {
                add_code_generation_data(strdup("BREAK"), strdup("_"), strdup("_"), strdup("_"));
            }else{
                printf("Error: BREAK statement not inside a loop.\n");
                return 0;
            }
            return 0;
            break;
        }
        case RETURN:
        {

            if (node->opr.nops == 1)
            {
                char *expression_result = handle_quad_expression(node->opr.op[0]);
                printf("test__--%s\n", expression_result);
                add_code_generation_data(strdup("RETURN"), expression_result, strdup("_"), strdup("_"));
            }
            else
            {
                add_code_generation_data(strdup("RETURN"), strdup("_"), strdup("_"), strdup("_"));
            }


            return 0;
            break;
        }
        case IF:
        case IFELSE:{
            int next_statement = add_code_generation_data(strdup("BEGIN IF"), strdup("_"), strdup("_"), strdup("_"));

            char *expression_result = handle_quad_expression(node->opr.op[0]->opr.op[0]);
            
            int jz_idx = add_code_generation_data(strdup("JZ"), strdup("????"), expression_result, strdup("_"));
            extract_quadruples(node->opr.op[1]);

            char *jz_idx_str = (char *)malloc(20);
            sprintf(jz_idx_str, "%d", code_generation_data_list_count);
            patch_quad_placeholder("quadruples.txt", jz_idx, jz_idx_str);
            
            int jmp_idx = add_code_generation_data(strdup("JMP"), strdup("????"), strdup("_"), strdup("_"));
            if (node->opr.nops == 3) {
                int else_statement = add_code_generation_data(strdup("BEGIN ELSE"), strdup("_"), strdup("_"), strdup("_"));
                char *next = (char *)malloc(20);
                sprintf(next, "%d", else_statement);
                extract_quadruples(node->opr.op[2]);

            }
            char *jmp_idx_str = (char *)malloc(20);
            sprintf(jmp_idx_str, "%d", code_generation_data_list_count);
            patch_quad_placeholder("quadruples.txt", jmp_idx, jmp_idx_str);
            add_code_generation_data(strdup("END IF"), strdup("_"), strdup("_"), strdup("_"));
            return 0;
            break;
        }
        case FOR:{

            /**
             * Flow goes as follow:
             *      BEGIN FOR
             *      FOR INIT
             *      FOR TERM
             *      --JZ -> to end for
             *      FOR BODY
             *      FOR STEP
             *      --JMP -> to term
             *      FOR END
             * 
             */
            helper_parent = "iter";
            add_code_generation_data(strdup("BEGIN FOR"), strdup("_"), strdup("_"), strdup("_"));
            
            nodeType* for_init = node->opr.op[0]->opr.op[0];
            extract_quadruples(for_init);
            int term_idx = code_generation_data_list_count;
            nodeType* for_term = node->opr.op[0]->opr.op[1]->opr.op[0];
            char *expression_result = handle_quad_expression(for_term);
            int jz_idx = add_code_generation_data(strdup("JZ"), strdup("????"), expression_result, strdup("_"));

            nodeType* for_body = node->opr.op[1];
            extract_quadruples(for_body);

            nodeType* for_step = node->opr.op[0]->opr.op[2]->opr.op[0];
            extract_quadruples(for_step);

            int jmp_idx = add_code_generation_data(strdup("JMP"), strdup("????"), strdup("_"), strdup("_"));
            char* jmp_idx_str = (char *)malloc(20);
            sprintf(jmp_idx_str, "%d", term_idx);
            char* jz_idx_str = (char *)malloc(20);
            sprintf(jz_idx_str, "%d", code_generation_data_list_count);

            patch_quad_placeholder("quadruples.txt", jz_idx, jz_idx_str);
            patch_quad_placeholder("quadruples.txt", jmp_idx, jmp_idx_str);

            add_code_generation_data(strdup("END FOR"), strdup("_"), strdup("_"), strdup("_"));
            helper_parent = "";
            return 0;
            break;
        }
        case REPEATUNTIL:
        case WHILE:
        {
            helper_parent = "iter";
            int next_statement;
            if (node->opr.oper == REPEATUNTIL)
            {
                next_statement = add_code_generation_data(strdup("BEGIN REPEAT-UNTIL"), strdup("_"), strdup("_"), strdup("_"));
            }
            else if (node->opr.oper == WHILE)
            {
                next_statement = add_code_generation_data(strdup("BEGIN WHILE"), strdup("_"), strdup("_"), strdup("_"));
            }

            char *expression_result = handle_quad_expression(node->opr.op[0]->opr.op[0]);

            if (node->opr.nops == 2)
            {
                extract_quadruples(node->opr.op[1]);
            }

            char *next = (char *)malloc(20);
            sprintf(next, "%d", next_statement);
            add_code_generation_data(strdup("JZ"), next, expression_result, strdup("_"));
            helper_parent = "";
            return 0;
            break;
        }
        case SWITCH:{
            helper_parent = "switch";
            char *varname = node->opr.op[0]->opr.op[0]->type == typeId ? node->opr.op[0]->opr.op[0]->id.name : node->opr.op[0]->opr.op[0]->constant.name;
            helper_variable = varname;
            int next_statement = add_code_generation_data(strdup("BEGIN SWITCH"), varname, strdup("_"), strdup("_"));

            nodeType* switch_cases = node->opr.op[1];
            handle_single_node_quad(switch_cases->opr.op[0]);

            add_code_generation_data(strdup("END SWITCH"), strdup("_"), strdup("_"), strdup("_"));
            helper_parent = "";
            helper_variable = "";
            return 0;
            break;
        }
        case SWITCH_CASES:{
            for (int i = 0; i < node->opr.nops; i++)
                handle_single_node_quad(node->opr.op[i]);
            return 0;
            break;
        }
        case SWITCH_CASE:{
            add_code_generation_data(strdup("BEGIN CASE"), strdup("_"), strdup("_"), strdup("_"));

            // handling value(s)
            nodeType* case_value = node->opr.op[0];
            nodeType* case_body = node;
            handle_quad_expression(case_value);
            char* prev_result_1 = (char *)malloc(20);
            sprintf(prev_result_1, "s%d", statement_counter - 1);
            while(case_body->opr.op[1]->opr.oper == SWITCH_CASE){
                case_value = case_body->opr.op[1]->opr.op[0];
                handle_quad_expression(case_value);
                char* prev_result_2 = (char *)malloc(20);
                sprintf(prev_result_2, "s%d", statement_counter - 1);
                char* result = (char *)malloc(20);
                sprintf(result, "s%d", statement_counter++);
                add_code_generation_data(strdup("SWITCH-OR"), prev_result_1, prev_result_2, result);
                sprintf(prev_result_1, "s%d", statement_counter - 1);
                case_body = case_body->opr.op[1];
            }
            sprintf(prev_result_1, "s%d", statement_counter);
            int jne_idx = add_code_generation_data(strdup("JNE"), strdup("????"), helper_variable, prev_result_1);

            
            nodeType* case_stmts = case_body->opr.op[1];
            extract_quadruples(case_stmts);
            char* jne_idx_str = (char *)malloc(20);
            sprintf(jne_idx_str, "%d", code_generation_data_list_count);

            patch_quad_placeholder("quadruples.txt", jne_idx, jne_idx_str);
            
            add_code_generation_data(strdup("END CASE"), strdup("_"), strdup("_"), strdup("_"));

            return 0;
            break;
        }
        case ASSIGN:
        {

            char* varname = node->opr.op[0]->type == typeId ? strdup(node->opr.op[0]->id.sname) : strdup(node->opr.op[0]->constant.sname);
            char* kw = node->opr.op[0]->type == typeId ? strdup("DECL") : strdup("DCON");
            if ((node->opr.op[0]->type == typeId && strcmp(node->opr.op[0]->id.type, "undefined") != 0) || node->opr.op[0]->type == typeConst)
                add_code_generation_data(kw, strdup("_"), strdup("_"), varname);
            char *expression_result = handle_quad_expression(node->opr.op[1]);
            if (expression_result == NULL)
            {
                printf("Error: Invalid expression type.\n");
                return 0;
            }

            add_code_generation_data(strdup("="), expression_result, strdup("_"), varname);

            return 0;
            break;
        }
        case PLUS_ASSIGN:
        case MINUS_ASSIGN:
        case STAR_ASSIGN:
        case SLASH_ASSIGN:
        {
            char* oper = NULL;
            switch (node->opr.oper) {
                case PLUS_ASSIGN:
                    oper = strdup("+");
                    break;
                case MINUS_ASSIGN:
                    oper = strdup("-");
                    break;
                case STAR_ASSIGN:
                    oper = strdup("*");
                    break;
                case SLASH_ASSIGN:
                    oper = strdup("/");
                    break;
                default:
                    printf("Error: Unknown assignment operator.\n");
                    return 0;
            }
            char *expression_result = handle_quad_expression(node->opr.op[1]);


            if (expression_result == NULL)
            {
                printf("Error: Invalid expression type.\n");
                return 0;
            }
            char *result = (char *)malloc(20);
            sprintf(result, "s%d", statement_counter++);

            add_code_generation_data(strdup(oper), strdup(node->opr.op[0]->id.sname), expression_result, result);
            add_code_generation_data(strdup("="), result, strdup("_"), strdup(node->opr.op[0]->id.sname));
            return 0;
            break;
        }
        case INCREMENT_POSTFIX:
        case INCREMENT_PREFIX:{
            char *result = (char *)malloc(20);
            sprintf(result, "s%d", statement_counter++);
            add_code_generation_data(strdup("+"), node->opr.op[0]->id.name, strdup("1"), result);
            add_code_generation_data(strdup("="), result, strdup("_"), node->opr.op[0]->id.name);
            return 0;
            break;
        }
        case DECREMENT_POSTFIX:
        case DECREMENT_PREFIX:{
            char *result = (char *)malloc(20);
            sprintf(result, "s%d", statement_counter++);
            add_code_generation_data(strdup("-"), node->opr.op[0]->id.name, strdup("1"), result);
            add_code_generation_data(strdup("="), result, strdup("_"), node->opr.op[0]->id.name);
            return 0;
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }



    return 1;
}

void extract_quadruples(nodeType *topNode)
{

    int cont = handle_single_node_quad(topNode);


    if (cont == 1)
    {
        for (int i = 0; i < topNode->opr.nops; i++)
        {
            extract_quadruples(topNode->opr.op[i]);
        }
    }

    if (topNode->opr.oper == FUNC && cont == 1)
    {
        char end_label[50];
        sprintf(end_label, "END %s", topNode->opr.op[0]->opr.op[0]->id.name);
        add_label(end_label, strdup(";"));
        code_generation_data_list_count++;
    }

    if(topNode->opr.oper == FUNC)
    printf("tttee ssttt A\n");    
}

void call_extract_quads(nodeType *topNode)
{
    file = fopen("quadruples.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    fprintf(file, " ");
    fclose(file);

    file = fopen("quadruples.txt", "a");
    
    extract_quadruples(topNode);

    if (file != NULL)
        fclose(file);
}