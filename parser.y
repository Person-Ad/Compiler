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
%token WHILE REPEATUNTIL SWITCH CASE DEFAULT BREAK CONTINUE RETURN TERNARY COLON SL S BLOCK
%token COND ITER_BODY FOR FOR_COND FOR_INIT FOR_STEP FOR_TERM
%token COMMA FUNC FUNC_ARG_LIST FUNC_BODY FUNC_ARG
%token IF ELSE IFELSE
%token SWITCH_BODY SWITCH_CASES SWITCH_CASE  DEFAULT_CASE SWITCH_VAR
%token INCREMENT_PREFIX INCREMENT_POSTFIX DECREMENT_POSTFIX DECREMENT_PREFIX
%token <stringValue> KW_VAR KW_CONST KW_FUNC KW_INT KW_FLOAT KW_BOOL KW_STRING
%token <stringValue> IDENTIFIER STRING
%token <intValue> INTEGER
%token <floatValue> FLOAT
%token <boolValue> BOOLEAN
%token PLUS MINUS STAR SLASH PERCENT EQ NEQ LT GT LE GE AND OR NOT
%token ASSIGN SEMICOLON LPAREN RPAREN LBRACE RBRACE PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN BIT_AND BIT_OR BIT_XOR BIT_NOT SHIFT_LEFT SHIFT_RIGHT INCREMENT DECREMENT

%right ASSIGN
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left EQ NEQ
%left LT GT LE GE
%left SHIFT_LEFT SHIFT_RIGHT
%left PLUS MINUS
%left STAR SLASH PERCENT
%right NOT BIT_NOT
%left INCREMENT DECREMENT

%type <nodeValue> expression statement_list statement program iter_body condition for_condition for_init for_terminate for_step
%type <nodeValue> declaration_statement assignment_statement block_statement iterative_statement conditional_statement
%type <nodeValue> function_arguments function_statement function_body function_argument
%type <nodeValue> if_body else_body 
%type <nodeValue> switch_body switch_variable switch_cases single_case default_case case_value




%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


// Grammar rules
%%
program
    : statement_list                                           { topNode=$1;}
    ;

statement_list
    : statement                                                 { $$ = $1; }
    | statement_list statement                                  { $$ = opr(SL, 2, $1, $2); }
    ;

statement
    : declaration_statement SEMICOLON                           { $$ = $1; }
    | assignment_statement SEMICOLON                            { $$ = $1; }
    | conditional_statement                                     { $$ = $1; }
    | iterative_statement                                       { $$ = $1; }
    | function_statement                                        { $$ = $1; }
    | block_statement                                           { $$ = $1; }
    | BREAK SEMICOLON                                           { $$ = opr(BREAK, 0); }
    | CONTINUE SEMICOLON                                        { $$ = opr(CONTINUE, 0); }
    ;

// Note: no declaration of constants with no values
declaration_statement
    : KW_VAR IDENTIFIER                               { $$ = id($2);  }
    | KW_BOOL IDENTIFIER                              { $$ = id($2);  }
    | KW_INT IDENTIFIER                               { $$ = id($2);  }
    | KW_FLOAT IDENTIFIER                             { $$ = id($2);  }
    | KW_STRING IDENTIFIER                            { $$ = id($2);  }
    ;

assignment_statement
    : IDENTIFIER ASSIGN expression                                { $$ = opr(ASSIGN, 2, id($1), $3); }
    | IDENTIFIER PLUS_ASSIGN expression                           { $$ = opr(PLUS_ASSIGN, 2, id($1), $3); }
    | IDENTIFIER MINUS_ASSIGN expression                          { $$ = opr(MINUS_ASSIGN, 2, id($1), $3); }
    | IDENTIFIER STAR_ASSIGN expression                           { $$ = opr(STAR_ASSIGN, 2, id($1), $3); }
    | IDENTIFIER SLASH_ASSIGN expression                          { $$ = opr(SLASH_ASSIGN, 2, id($1), $3); }
    | INCREMENT expression                                        { $$ = opr(INCREMENT_PREFIX, 1, $2); }
    | DECREMENT expression                                        { $$ = opr(DECREMENT_PREFIX, 1, $2); }
    | expression INCREMENT                                        { $$ = opr(INCREMENT_POSTFIX, 1, $1); }
    | expression DECREMENT                                        { $$ = opr(DECREMENT_POSTFIX, 1, $1); }
    | KW_CONST IDENTIFIER ASSIGN expression                       { $$ = opr(ASSIGN, 2, id($2), $4); }
    | KW_CONST IDENTIFIER PLUS_ASSIGN expression                  { $$ = opr(PLUS_ASSIGN, 2, id($2), $4); }
    | KW_CONST IDENTIFIER MINUS_ASSIGN expression                 { $$ = opr(MINUS_ASSIGN, 2, id($2), $4); }
    | KW_CONST IDENTIFIER STAR_ASSIGN expression                  { $$ = opr(STAR_ASSIGN, 2, id($2), $4); }
    | KW_CONST IDENTIFIER SLASH_ASSIGN expression                 { $$ = opr(SLASH_ASSIGN, 2, id($2), $4); }
    | KW_VAR IDENTIFIER ASSIGN expression                         { $$ = opr(ASSIGN, 2, id($2), $4); }
    | KW_VAR IDENTIFIER PLUS_ASSIGN expression                    { $$ = opr(PLUS_ASSIGN, 2, id($2), $4); }
    | KW_VAR IDENTIFIER MINUS_ASSIGN expression                   { $$ = opr(MINUS_ASSIGN, 2, id($2), $4); }
    | KW_VAR IDENTIFIER STAR_ASSIGN expression                    { $$ = opr(STAR_ASSIGN, 2, id($2), $4); }
    | KW_VAR IDENTIFIER SLASH_ASSIGN expression                   { $$ = opr(SLASH_ASSIGN, 2, id($2), $4); }
    | KW_BOOL IDENTIFIER ASSIGN expression                        { $$ = opr(ASSIGN, 2, id($2), $4); }
    | KW_BOOL IDENTIFIER PLUS_ASSIGN expression                   { $$ = opr(PLUS_ASSIGN, 2, id($2), $4); }
    | KW_BOOL IDENTIFIER MINUS_ASSIGN expression                  { $$ = opr(MINUS_ASSIGN, 2, id($2), $4); }
    | KW_BOOL IDENTIFIER STAR_ASSIGN expression                   { $$ = opr(STAR_ASSIGN, 2, id($2), $4); }
    | KW_BOOL IDENTIFIER SLASH_ASSIGN expression                  { $$ = opr(SLASH_ASSIGN, 2, id($2), $4); }
    | KW_FLOAT IDENTIFIER ASSIGN expression                       { $$ = opr(ASSIGN, 2, id($2), $4); }
    | KW_FLOAT IDENTIFIER PLUS_ASSIGN expression                  { $$ = opr(PLUS_ASSIGN, 2, id($2), $4); }
    | KW_FLOAT IDENTIFIER MINUS_ASSIGN expression                 { $$ = opr(MINUS_ASSIGN, 2, id($2), $4); }
    | KW_FLOAT IDENTIFIER STAR_ASSIGN expression                  { $$ = opr(STAR_ASSIGN, 2, id($2), $4); }
    | KW_FLOAT IDENTIFIER SLASH_ASSIGN expression                 { $$ = opr(SLASH_ASSIGN, 2, id($2), $4); }
    | KW_INT IDENTIFIER ASSIGN expression                         { $$ = opr(ASSIGN, 2, id($2), $4); }
    | KW_INT IDENTIFIER PLUS_ASSIGN expression                    { $$ = opr(PLUS_ASSIGN, 2, id($2), $4); }
    | KW_INT IDENTIFIER MINUS_ASSIGN expression                   { $$ = opr(MINUS_ASSIGN, 2, id($2), $4); }
    | KW_INT IDENTIFIER STAR_ASSIGN expression                    { $$ = opr(STAR_ASSIGN, 2, id($2), $4); }
    | KW_INT IDENTIFIER SLASH_ASSIGN expression                   { $$ = opr(SLASH_ASSIGN, 2, id($2), $4); }
    | KW_STRING IDENTIFIER ASSIGN expression                      { $$ = opr(ASSIGN, 2, id($2), $4); }
    | KW_STRING IDENTIFIER PLUS_ASSIGN expression                 { $$ = opr(PLUS_ASSIGN, 2, id($2), $4); }
    | KW_STRING IDENTIFIER MINUS_ASSIGN expression                { $$ = opr(MINUS_ASSIGN, 2, id($2), $4); }
    | KW_STRING IDENTIFIER STAR_ASSIGN expression                 { $$ = opr(STAR_ASSIGN, 2, id($2), $4); }
    | KW_STRING IDENTIFIER SLASH_ASSIGN expression                { $$ = opr(SLASH_ASSIGN, 2, id($2), $4); }
    ;

expression
    : INTEGER 													{ $$ = conInt($1);  }
    | FLOAT 													{ $$ = conFloat($1);  }
    | IDENTIFIER 												{ $$ = id($1);  }
    | STRING 													{ $$ = conString($1);  }
    | BOOLEAN 													{ $$ = conBool($1);  }	
    | expression PLUS expression 								{ $$ = opr(PLUS, 2, $1, $3);  }
    | expression MINUS expression 								{ $$ = opr(MINUS, 2, $1, $3);  }
    | expression STAR expression 								{ $$ = opr(STAR, 2, $1, $3);  }
    | expression SLASH expression 								{ $$ = opr(SLASH, 2, $1, $3);  }
    | expression PERCENT expression 							{ $$ = opr(PERCENT, 2, $1, $3);  }
    | expression EQ expression 									{ $$ = opr(EQ, 2, $1, $3);  }
    | expression NEQ expression 								{ $$ = opr(NEQ, 2, $1, $3);  }
    | expression LT expression 									{ $$ = opr(LT, 2, $1, $3);  }
    | expression GT expression 									{ $$ = opr(GT, 2, $1, $3);  }
    | expression LE expression 									{ $$ = opr(LE, 2, $1, $3);  }
    | expression GE expression 									{ $$ = opr(GE, 2, $1, $3);  }
    | expression AND expression 								{ $$ = opr(AND, 2, $1, $3);  }
    | expression OR expression 									{ $$ = opr(OR, 2, $1, $3);  }
    | expression BIT_AND expression                             { $$ = opr(BIT_AND, 2, $1, $3); }
    | expression BIT_OR expression                              { $$ = opr(BIT_OR, 2, $1, $3); }
    | expression BIT_XOR expression                             { $$ = opr(BIT_XOR, 2, $1, $3); }
    | BIT_NOT expression                                        { $$ = opr(BIT_NOT, 1, $2); }
    | expression SHIFT_LEFT INTEGER                             { $$ = opr(SHIFT_LEFT, 2, $1, conInt($3)); }
    | expression SHIFT_RIGHT INTEGER                            { $$ = opr(SHIFT_RIGHT, 2, $1, conInt($3)); }
    | NOT expression 											{ $$ = opr(NOT, 1, $2);  }
    | LPAREN expression RPAREN                              	{ $$ = $2; }
    ;

block_statement
    : LBRACE statement_list RBRACE                              { $$ = opr(BLOCK, 1, $2);  }
    | LBRACE RBRACE                                             { $$ = opr(BLOCK, 1, NULL);  }
    ;

iterative_statement
    : WHILE LPAREN condition RPAREN iter_body                  { $$ = opr(WHILE, 2, $3, $5);  }
    | WHILE LPAREN condition RPAREN SEMICOLON                  { $$ = opr(WHILE, 2, $3, NULL);  }
    | REPEATUNTIL LPAREN condition RPAREN iter_body            { $$ = opr(REPEATUNTIL, 2, $3, $5);  }
    | REPEATUNTIL LPAREN condition RPAREN SEMICOLON            { $$ = opr(REPEATUNTIL, 2, $3, NULL);  }
    | FOR LPAREN for_condition RPAREN iter_body                { $$ = opr(FOR, 2, $3, $5);  }
    | FOR LPAREN for_condition RPAREN SEMICOLON                { $$ = opr(FOR, 2, $3, NULL);  }
    ;

condition
    : expression                                               { $$ = opr(COND, 1, $1); }
    ;

for_condition
    : for_init SEMICOLON for_terminate SEMICOLON for_step                { $$ = opr(FOR_COND, 3, $1, $3, $5); } 
    ;

for_init
    : assignment_statement                                      { $$ = opr(FOR_INIT, 1, $1); }
    ;

for_terminate
    : expression                                                { $$ = opr(FOR_TERM, 1, $1); }
    ;

for_step
    : assignment_statement                                     { $$ = opr(FOR_STEP, 1, $1); }
    ;

iter_body
    : statement                                                { $$ = opr(ITER_BODY, 1, $1); }
    ;

function_statement
    : KW_INT IDENTIFIER LPAREN function_arguments RPAREN function_body { $$ = opr(FUNC, 2, $4, $6); }
    ;
function_arguments
    : function_arguments COMMA function_argument                    { $$ = opr(FUNC_ARG_LIST, 2, $1, $3); }
    | function_argument                                             { $$ = $1; }   
    ;

function_argument
    : declaration_statement %prec LOWER_THAN_ELSE                   { $$ = opr(FUNC_ARG, 1, $1); }
    | declaration_statement ASSIGN case_value                       { $$ = opr(FUNC_ARG, 2, $1, $3); }
    ;

function_body
    : block_statement                                               { $$ = opr(FUNC_BODY, 1, $1);  }
    ;

conditional_statement   
    : IF LPAREN condition RPAREN if_body %prec LOWER_THAN_ELSE      {$$ = opr(IF, 2, $3, $5);}
    | IF LPAREN condition RPAREN if_body ELSE else_body             {$$ = opr(IFELSE, 3, $3, $5, $7);}
    | SWITCH LPAREN switch_variable RPAREN switch_body                   {$$ = opr(SWITCH, 2, $3, $5);}
    ;

if_body
    : statement                                                     {$$ = $1}
    ;
    
else_body
    : statement                                                     {$$ = $1}
    ;

switch_variable
    : IDENTIFIER                                                   {$$ = opr(SWITCH_VAR, 1, id($1));}
    ;

switch_body
    : LBRACE switch_cases default_case RBRACE                       {$$ = opr(SWITCH_BODY, 2, $2, $3);}
    | LBRACE switch_cases RBRACE                                    {$$ = opr(SWITCH_BODY, 1, $2); ex($$);}
    ;

switch_cases
    : switch_cases single_case                                      {$$ = opr(SWITCH_CASES, 2, $1, $2);}
    | single_case                                                   {$$ = $1;}
    ;

single_case
    : CASE case_value COLON statement_list                             {$$ = opr(SWITCH_CASE, 2, $2, $4);}
    ;

case_value
    : INTEGER 													{ $$ = conInt($1);  }
    | FLOAT 													{ $$ = conFloat($1);  }
    | STRING 													{ $$ = conString($1);  }
    | BOOLEAN 													{ $$ = conBool($1);  }
    ;

default_case
    : DEFAULT COLON statement_list                                  {$$ = opr(DEFAULT_CASE, 1, $3);}
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
    
}


int main() {
    
    yyparse();
    ex(topNode);
    
    return 0;
}
