#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define todigit(c) (c - '0') // ascii diff
#define MAX_STATES 12
#define MAX_GRAMMAR 6
#define ACC 999

enum terminal {
    NUMBER,
    PLUS,
    STAR,
    LPAREN,
    RPAREN,
    END,
    MAX_TERMINALS,
    ILLEGAL_TOKEN = MAX_TERMINALS,
} sym;

struct production {
    enum nonterminal {
        EXPRESSION,
        TERM,
        FACTOR,
        MAX_NONTERMINALS,
    } left;
    unsigned length;
} prod[MAX_GRAMMAR + 1] = {
    [1] = {.length = 3, .left = EXPRESSION},
    [2] = {.length = 1, .left = EXPRESSION},
    [3] = {.length = 3, .left = TERM},
    [4] = {.length = 1, .left = TERM},
    [5] = {.length = 3, .left = FACTOR},
    [6] = {.length = 1, .left = FACTOR},
};

int action[MAX_STATES][MAX_TERMINALS] = {
    [0] = {[NUMBER] = 5,   [LPAREN] = 4},
    [1] = {[PLUS]   = 6,   [END] = ACC},
    [2] = {[PLUS]   = -2,  [STAR] = 7,  [RPAREN] = -2, [END] = -2},
    [3] = {[PLUS]   = -4,  [STAR] = -4, [RPAREN] = -4, [END] = -4},
    [4] = {[NUMBER] = 5,   [LPAREN] = 4},
    [5] = {[PLUS]   = -6,  [STAR] = -6, [RPAREN] = -6, [END] = -6},
    [6] = {[NUMBER] = 5,   [LPAREN] = 4},
    [7] = {[NUMBER] = 5,   [LPAREN] = 4},
    [8] = {[PLUS]   = 6,   [RPAREN] = 11},
    [9] = {[PLUS]   = -1,  [STAR] = 7,  [RPAREN] = -1, [END] = -1},
    [10]= {[PLUS]  = -3,   [STAR] = -3, [RPAREN] = -3, [END] = -3},
    [11]= {[PLUS]  = -5,   [STAR] = -5, [RPAREN] = -5, [END] = -5},
};

int go_to[MAX_STATES][MAX_NONTERMINALS] = {
    [0] = {[EXPRESSION] = 1, [TERM] = 2, [FACTOR] = 3},
    [4] = {[EXPRESSION] = 8, [TERM] = 2, [FACTOR] = 3},
    [6] = {[TERM] = 9, [FACTOR] = 3},
    [7] = {[FACTOR] = 10},
};

static int stack[1000];
static int top = -1;

void yyparse(void);
enum terminal yylex(void);

int main(void)
{
    yyparse();
    return 0;
}

void push(int i)
{
    stack[++top] = i;
}

void shift(int i)
{
    push(i);
    sym = yylex();
}

void reduce(int i)
{
    top -= prod[i].length;
    int old_top = top;
    push(go_to[stack[old_top]][prod[i].left]);
}

void yyerror(void)
{
    printf("syntax error\n");
    exit(1);
}

void yyparse(void)
{
    stack[++top] = 0;
    sym = yylex();
    while (1) {
        int i = action[stack[top]][sym];
        if (i == ACC) {
            printf("success!\n");
            break;
        } else if (i > 0) {
            shift(i);
        } else if (i < 0) {
            reduce(-i);
        } else {
            yyerror();
        }
    }
}

void lex_error(void)
{
    printf("illegal token\n");
    exit(2);
}

int num;
enum terminal yylex(void)
{
    static char ch = ' ';
    // skip whitespaces
    while (ch == ' ' || ch == '\t') {
        ch = getchar();
    }
    if (isdigit(ch)) {
        num = 0;
        do {
            num = num * 10 + todigit(ch);
            ch = getchar();
        } while (isdigit(ch));
        return NUMBER;
    } else if (ch == '+') {
        ch = getchar();
        return PLUS;
    } else if (ch == '*') {
        ch = getchar();
        return STAR;
    } else if (ch == '(') {
        ch = getchar();
        return LPAREN;
    } else if (ch == ')') {
        ch = getchar();
        return RPAREN;
    } else if (ch == EOF || ch == '\n') {
        return END;
    } else {
        lex_error();
    }
    return ILLEGAL_TOKEN;
}
