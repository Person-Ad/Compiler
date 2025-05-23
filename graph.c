/* source code courtesy of Frank Thomas Braun */

/* calc3d.c: Generation of the graph of the syntax tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "parser.tab.h"

int del = 1; /* distance of graph columns */
int eps = 3; /* distance of graph lines */

/* interface for drawing (can be replaced by "real" graphic using GD or other) */
void graphInit(void);
void graphFinish();
void graphBox(char *s, int *w, int *h);
void graphDrawBox(char *s, int c, int l);
void graphDrawArrow(int c1, int l1, int c2, int l2);

/* recursive drawing of the syntax tree */
void exNode(nodeType *p, int c, int l, int *ce, int *cm);

/*****************************************************************************/

/* main entry point of the manipulation of the syntax tree */
int ex(nodeType *p)
{
    int rte, rtm;

    graphInit();
    exNode(p, 0, 0, &rte, &rtm);
    graphFinish();
    return 0;
}

/*c----cm---ce---->                       drawing of leaf-nodes
 l leaf-info
 */

/*c---------------cm--------------ce----> drawing of non-leaf-nodes
 l            node-info
 *                |
 *    -------------     ...----
 *    |       |               |
 *    v       v               v
 * child1  child2  ...     child-n
 *        che     che             che
 *cs      cs      cs              cs
 *
 */

void exNode(nodeType *p,
            int c, int l,    /* start column and line of node */
            int *ce, int *cm /* resulting end column and mid of node */
)
{
    int w, h;      /* node width and height */
    char *s;       /* node text */
    int cbar;      /* "real" start column of node (centred above subnodes) */
    int k;         /* child number */
    int che, chm;  /* end column and mid of children */
    int cs;        /* start column of children */
    char word[20]; /* extended node text */
    
    
    if (!p){
        printf("p is nullptr");
        return;
    }

    strcpy(word, "???"); /* should never appear */
    s = word;
    switch (p->type)
    {
    case typeIntCon:
        sprintf(word, "c(%d)", p->conI.value);
        break;
    case typeFloatCon:
        sprintf(word, "c(%f)", p->conF.value);
        break;
    case typeBoolCon:
        sprintf(word, "c(%d)", p->conB.value);
        break;
    case typeStringCon:
        sprintf(word, "c(%s)", p->conS.value);
        break;
    case typeId:
        sprintf(word, "id(%s)", p->id.name);
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case BLOCK:
            s = "[block]";
            break;
        case WHILE:
            s = "[while]";
            break;
        case REPEATUNTIL:
            s = "[repeat-until]";
            break;
        case COND:
            s = "[COND]";
            break;
        case ITER_BODY:
            s = "[ITER_BODY]";
            break;
        case FOR:
            s = "[FOR]";
            break;            
        case FOR_COND:
            s = "[FOR_COND]";
            break;
        case FOR_INIT:
            s = "[FOR_INIT]";
            break;
        case FOR_STEP:
            s = "[FOR_STEP]";
            break;
        case FOR_TERM:
            s = "[FOR_TERM]";
            break;
        case FUNC:
            s = "[FUNC]";
            break;
        case FUNC_ARG_LIST:
            s = "[FUNC_ARG_LIST]";
            break;
        case FUNC_ARG:
            s = "[FUNC_ARG]";
            break;
        case FUNC_BODY:
            s = "[FUNC_BODY]";
            break;
        case RETURN:
            s = "[RETURN]";
            break;
        case IF:
            s = "[IF]";
            break;
        case IFELSE:
            s = "[IF-ELSE]";
            break;
        
        case SWITCH:
            s = "[switch]";
            break;
        case SWITCH_BODY:
            s = "[SWITCH_BODY]";
            break;
        case SWITCH_CASES:
            s = "[SWITCH_CASES]";
            break;
        case SWITCH_CASE:
            s = "[SWITCH_CASE]";
            break;
        case SWITCH_VAR:
            s = "[SWITCH_VAR]";
            break;  
        case DEFAULT_CASE:
            s = "[DEFAULT_CASE]";
            break;  
        case INCREMENT_PREFIX:
            s = "[INCREMENT_PREFIX]";
            break;  
        case DECREMENT_PREFIX:
            s = "[DECREMENT_PREFIX]";
            break;  
        case INCREMENT_POSTFIX:
            s = "[INCREMENT_POSTFIX]";
            break;  
        case DECREMENT_POSTFIX:
            s = "[DECREMENT_POSTFIX]";
            break;
        case BREAK:
            s = "[BREAK]";
            break; 
        case FUNC_CALL:
            s = "[FUNC_CALL]";
            break;  
        case FUNC_ID:
            s = "[FUNC_ID]";
            break;  
        case ARG_VALUES:
            s = "[ARG_VALUES]";
            break;  
        case ARG_VALUE:
            s = "[ARG_VALUE]";
            break;  
        case CONTINUE:
            s = "[CONTINUE]";
            break;  
        case SEMICOLON:
            s = "[;]";
            break;
        case ASSIGN:
            s = "[=]";
            break;
        case PLUS_ASSIGN:
            s = "[+=]";
            break;
        case MINUS_ASSIGN:
            s = "[-=]";
            break;
        case STAR_ASSIGN:
            s = "[*=]";
            break;
        case SLASH_ASSIGN:
            s = "[/=]";
            break;
        case PLUS:
            s = "[+]";
            break;
        case MINUS:
            s = "[-]";
            break;
        case STAR:
            s = "[*]";
            break;
        case SLASH:
            s = "[/]";
            break;
        case LT:
            s = "[<]";
            break;
        case GT:
            s = "[>]";
            break;
        case GE:
            s = "[>=]";
            break;
        case LE:
            s = "[<=]";
            break;
        case NEQ:
            s = "[!=]";
            break;
        case EQ:
            s = "[==]";
            break;
        case AND:
            s = "[&&]";
            break;
        case SHIFT_LEFT:
            s = "[<<]";
            break;
        case SHIFT_RIGHT:
            s = "[>>]";
            break;
        case BIT_AND:
            s = "[&]";
            break;
        case BIT_OR:
            s = "[|]";
            break;
        case BIT_XOR:
            s = "[^]";
            break;
        case BIT_NOT:
            s = "[~]";
            break;
        case SL:
            s = "[ST_L]";
            break;
        case S:
            s = "[ST]";
            break;
        }
        break;
    }


    /* construct node text box */
    graphBox(s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    /* node is leaf */
    if (p->type == typeIntCon || p->type == typeFloatCon || p->type == typeBoolCon || p->type == typeStringCon || p->type == typeId || p->opr.nops == 0)
    {
        graphDrawBox(s, cbar, l);
        return;
    }

    /* node has children */
    cs = c;
    for (k = 0; k < p->opr.nops; k++)
    {
        exNode(p->opr.op[k], cs, l + h + eps, &che, &chm);
        cs = che;
    }
    

    /* total node width */
    if (w < che - c)
    {
        cbar += (che - c - w) / 2;
        *ce = che;
        *cm = (c + che) / 2;
    }

    /* draw node */
    graphDrawBox(s, cbar, l);

    /* draw arrows (not optimal: children are drawn a second time) */
    cs = c;
    for (k = 0; k < p->opr.nops; k++)
    {
        exNode(p->opr.op[k], cs, l + h + eps, &che, &chm);
        graphDrawArrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }
}

/* interface for drawing */

#define lmax 200
#define cmax 200

char graph[lmax][cmax]; /* array for ASCII-Graphic */
int graphNumber = 0;

void graphTest(int l, int c)
{
    int ok;
    ok = 1;
    if (l < 0)
        ok = 0;
    if (l >= lmax)
        ok = 0;
    if (c < 0)
        ok = 0;
    if (c >= cmax)
        ok = 0;
    if (ok)
        return;
    printf("\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d",
           l, c, lmax, cmax);
    exit(1);
}

void graphInit(void)
{
    int i, j;
    for (i = 0; i < lmax; i++)
    {
        for (j = 0; j < cmax; j++)
        {
            graph[i][j] = ' ';
        }
    }
}

void graphFinish()
{
    int i, j;
    for (i = 0; i < lmax; i++)
    {
        for (j = cmax - 1; j > 0 && graph[i][j] == ' '; j--)
            ;
        graph[i][cmax - 1] = 0;
        if (j < cmax - 1)
            graph[i][j + 1] = 0;
        if (graph[i][j] == ' ')
            graph[i][j] = 0;
    }
    for (i = lmax - 1; i > 0 && graph[i][0] == 0; i--)
        ;
    printf("\n\nGraph %d:\n", graphNumber++);
    for (j = 0; j <= i; j++)
        printf("\n%s", graph[j]);
    printf("\n");
}

void graphBox(char *s, int *w, int *h)
{
    *w = strlen(s) + del;
    *h = 1;
}

void graphDrawBox(char *s, int c, int l)
{
    int i;
    graphTest(l, c + strlen(s) - 1 + del);
    for (i = 0; i < strlen(s); i++)
    {
        graph[l][c + i + del] = s[i];
    }
}

void graphDrawArrow(int c1, int l1, int c2, int l2)
{
    int m;
    graphTest(l1, c1);
    graphTest(l2, c2);
    m = (l1 + l2) / 2;
    while (l1 != m)
    {
        graph[l1][c1] = '|';
        if (l1 < l2)
            l1++;
        else
            l1--;
    }
    while (c1 != c2)
    {
        graph[l1][c1] = '-';
        if (c1 < c2)
            c1++;
        else
            c1--;
    }
    while (l1 != l2)
    {
        graph[l1][c1] = '|';
        if (l1 < l2)
            l1++;
        else
            l1--;
    }
    graph[l1][c1] = '|';
}
