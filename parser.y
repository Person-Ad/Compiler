%{
    #include "node.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #include <stdbool.h>
    #include "parser.tab.h"
	int yylex(void);

	// Expression Nodes
	nodeType *opr(int oper, int nops, ...);
	nodeType *id(char* i);
	nodeType *conInt(int value);
	nodeType *conFloat(double value);
	nodeType *conBool(int value);
	nodeType *conString(char* value);


    // nodeType *cond(int oper, int nops, ...);

	void freeNode(nodeType *p);
	void yyerror(char *s);

    // Graph functions
    int ex (nodeType *p);

    nodeType* topNode = NULL;
%}

%union {
	int intValue;
	float floatValue;
	int boolValue;
	char* stringValue;
    nodeType* nodeValue;
}
// Token declarations
%token IF ELSE WHILE FOR SWITCH CASE DEFAULT BREAK CONTINUE RETURN TERNARY COLON SL S BLOCK
%token <stringValue> KW_VAR KW_CONST KW_FUNC KW_INT KW_FLOAT KW_BOOL KW_STRING
%token <stringValue> IDENTIFIER STRING
%token <intValue> INTEGER
%token <floatValue> FLOAT
%token <boolValue> BOOLEAN
%token PLUS MINUS STAR SLASH PERCENT EQ NEQ LT GT LE GE AND OR NOT
%token ASSIGN SEMICOLON LPAREN RPAREN LBRACE RBRACE

%left PLUS MINUS
%left STAR SLASH PERCENT
%left EQ NEQ LT GT LE GE
%left AND OR
%right NOT


%type <nodeValue> expression statement_list statement program
%type <nodeValue> declaration_statement assignment_statement block_statement


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

<<EOF>>    { return 0; }

// Grammar rules
%%
program
    : statement_list                                           { printf("Parsed program\n");topNode=$1; exit(0); }
    ;

statement_list
    : statement                                                 { $$ = $1; printf("Parsed statement\n");}
    | statement_list statement                                  { $$ = opr(SL, 2, $1, $2); printf("Parsed statement concat\n");}
    ;

statement
    : declaration_statement                                     { $$ = $1; }
    | assignment_statement                                      { $$ = $1; }
    // | conditional_statement                                  
    // | iterative_statement
    // | function_statement
    | block_statement                                           { $$ = $1; }
    ;

// Note: no declaration of constants with no values
declaration_statement
    : KW_VAR IDENTIFIER SEMICOLON                               { $$ = id($2); printf("Declared variable: %s\n", $2); }
    | KW_BOOL IDENTIFIER SEMICOLON                              { $$ = id($2); printf("Declared boolean: %s\n", $2); }
    | KW_INT IDENTIFIER SEMICOLON                               { $$ = id($2); printf("Declared integer: %s\n", $2); }
    | KW_FLOAT IDENTIFIER SEMICOLON                             { $$ = id($2); printf("Declared float: %s\n", $2); }
    | KW_STRING IDENTIFIER SEMICOLON                            { $$ = id($2); printf("Declared string: %s\n", $2); }
    ;
  
assignment_statement
    : IDENTIFIER ASSIGN expression SEMICOLON                    { $$ = opr(ASSIGN, 2, id($1), $3); printf("Assigned %s\n", $1); }
    | KW_CONST IDENTIFIER ASSIGN expression SEMICOLON           { $$ = opr(ASSIGN, 2, id($2), $4); printf("Assigned constant %s\n", $2); }
    | KW_VAR IDENTIFIER ASSIGN expression SEMICOLON             { $$ = opr(ASSIGN, 2, id($2), $4); printf("Assigned variable %s\n", $2); }
    | KW_BOOL IDENTIFIER ASSIGN expression SEMICOLON            { $$ = opr(ASSIGN, 2, id($2), $4); printf("Assigned boolean %s\n", $2); }
    | KW_FLOAT IDENTIFIER ASSIGN expression SEMICOLON           { $$ = opr(ASSIGN, 2, id($2), $4); printf("Assigned float %s\n", $2); }
    | KW_INT IDENTIFIER ASSIGN expression SEMICOLON             { $$ = opr(ASSIGN, 2, id($2), $4); printf("Assigned integer %s\n", $2); }
    | KW_STRING IDENTIFIER ASSIGN expression SEMICOLON          { $$ = opr(ASSIGN, 2, id($2), $4); printf("Assigned string %s\n", $2); }
    ;

expression
    : INTEGER 													{ $$ = conInt($1); printf("Integer: %d\n", $1); }
    | FLOAT 													{ $$ = conFloat($1); printf("Float: %f\n", $1); }
    | IDENTIFIER 												{ $$ = id($1); printf("Identifier: %s\n", $1); }
    | STRING 													{ $$ = conString($1); printf("String: %s\n", $1); }
    | BOOLEAN 													{ $$ = conBool($1); printf("Boolean: %d\n", $1); }	
    | expression PLUS expression 								{ $$ = opr(PLUS, 2, $1, $3); printf("Add Integer\n"); }
    | expression MINUS expression 								{ $$ = opr(MINUS, 2, $1, $3); printf("Subtract Integer\n"); }
    | expression STAR expression 								{ $$ = opr(STAR, 2, $1, $3); printf("Multiply Integer\n"); }
    | expression SLASH expression 								{ $$ = opr(SLASH, 2, $1, $3); printf("Divide Integer\n"); }
    | expression PERCENT expression 							{ $$ = opr(PERCENT, 2, $1, $3); printf("Modulo Integer\n"); }
    | expression EQ expression 									{ $$ = opr(EQ, 2, $1, $3); printf("Equal Integer\n"); }
    | expression NEQ expression 								{ $$ = opr(NEQ, 2, $1, $3); printf("Not Equal Integer\n"); }
    | expression LT expression 									{ $$ = opr(LT, 2, $1, $3); printf("Less Than Integer\n"); }
    | expression GT expression 									{ $$ = opr(GT, 2, $1, $3); printf("Greater Than Integer\n"); }
    | expression LE expression 									{ $$ = opr(LE, 2, $1, $3); printf("Less Than or Equal Integer\n"); }
    | expression GE expression 									{ $$ = opr(GE, 2, $1, $3); printf("Greater Than or Equal Integer\n"); }
    | expression AND expression 								{ $$ = opr(AND, 2, $1, $3); printf("Logical And Boolean\n"); }
    | expression OR expression 									{ $$ = opr(OR, 2, $1, $3); printf("Logical Or Boolean\n"); }
    | NOT expression 											{ $$ = opr(NOT, 1, $2); printf("Logical Not Boolean\n"); }
    | LPAREN expression RPAREN                              	{ $$ = $2; printf("Parentheses\n"); }
    ;

block_statement
    : LBRACE statement_list RBRACE                              { $$ = opr(BLOCK, 1, $2); printf("Parsed block statement\n"); }
    | LBRACE RBRACE                                             { $$ = opr(BLOCK, 1, NULL); printf("Empty block statement\n"); }
    ;




%%

nodeType *conInt(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIntCon;
    p->conI.value = value;

    return p;
}

nodeType *conFloat(double value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeFloatCon;
    p->conF.value = value;

    return p;
}

nodeType *conBool(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeBoolCon;
    p->conB.value = value;

    return p;
}

nodeType *conString(char* value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeStringCon;
    p->conS.value = strdup(value);

    return p;
}

nodeType *id(char* name) {
    nodeType *p;
    printf("name: %s\n", name);

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.name = strdup(name);

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = (nodeType*)malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

// nodeType *cond(...) {
//     va_list ap;
//     nodeType *p;
//     int i;

//     /* allocate node, extending op array */
//     if ((p = (nodeType*)malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
//         yyerror("out of memory");

//     /* copy information */
//     p->type = typeIfCond;
//     va_start(ap, nops);
//     for (i = 0; i < nops; i++)
//         p->condIf.op[i] = va_arg(ap, nodeType*);
//     va_end(ap);
//     return p;
// }

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}


int main() {
    yyparse();
    printf("A:");
    ex(topNode);
    printf("B:");
    return 0;
}