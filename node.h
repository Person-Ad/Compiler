typedef enum
{
    typeIntCon,
    typeFloatCon,
    typeBoolCon,
    typeStringCon,
    typeId,
    typeOpr,
    typeIfCond
} nodeEnum;

/* constants */
typedef struct
{
    int value; /* value of constant */
} intNodeType;

typedef struct
{
    double value; /* value of constant */
} floatNodeType;

typedef struct
{
    int value; /* value of constant boolean, e.g., 0 for false, 1 for true */
} boolNodeType;

typedef struct
{
    char *value; /* pointer to the string literal */
} stringNodeType;

/* identifiers */
typedef struct
{
    char* name;
} idNodeType;

/* operators */
typedef struct
{
    int oper;                  /* operator */
    int nops;                  /* number of operands */
    struct nodeTypeTag *op[1]; /* operands, extended at runtime */
} oprNodeType;

/* Conditional Statements Structs */
typedef struct
{
    struct nodeTypeTag *condition; /* condition expression */
    struct nodeTypeTag *ifBranch;  /* statements inside if block */
    struct nodeTypeTag *elseBranch; /* statements inside else block (optional) */
} conditionalIfNodeType;

typedef struct nodeTypeTag
{
    nodeEnum type; /* type of node */

    union
    {
        /* constants */
        intNodeType conI;
        floatNodeType conF;
        boolNodeType conB;
        stringNodeType conS;

        idNodeType id;   /* identifiers */
        oprNodeType opr; /* operators */

        // conditionalIfNodeType condIf;
    };
} nodeType;

extern int sym[26];
