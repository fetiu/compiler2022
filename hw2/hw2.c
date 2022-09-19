#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define str(s) #s
#define todigit(c) (c - '0') // ascii diff

enum error {
    NOFACTOR,
    NORPAREN,
    BADTOKEN,
};

static int num;
static enum {
    NUL,
    NUMBER,
    PLUS,
    STAR,
    LPAREN,
    RPAREN,
    END
} token;

static int expression(void);
static int term(void);
static int factor(void);

static void error(enum error e)
{
    switch (e) {
    case NOFACTOR:
        printf("\nno number nor expr in factor\n");
        break;
    case NORPAREN:
        printf("\nno closing parenthesis found\n");
        break;
    case BADTOKEN:
        printf("\ninvalid tokens in expression\n");
        break;
    default:
        break;
    }
    exit(1);
}

static void get_token()
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
        token = NUMBER;
        return;
    } else if (ch == '+') {
        ch = getchar();
        token = PLUS;
    } else if (ch == '*') {
        ch = getchar();
        token = STAR;
    } else if (ch == '(') {
        ch = getchar();
        token = LPAREN;
    } else if (ch == ')') {
        ch = getchar();
        token = RPAREN;
    } else if (ch == EOF || ch == '\n') {
        token = END;
        return;
    } else {
        error(BADTOKEN);
    }
}

int main(void)
{
    get_token();
    int result = expression();
    puts("acc");
    if (token != END) {
        error(BADTOKEN);
    } else {
        printf("=%d\n", result);
    }
    return 0;
}

static int expression(void)
{
    int result = term();
    puts("r2");
    while (token == PLUS) {
        puts("s6");
        get_token();
        result = result + term();
        puts("r1");
    }
    return result;
}

static int term(void)
{
    int result = factor();
    puts("r4");
    while (token == STAR) {
        puts("s7");
        get_token();
        result = result * factor();
        puts("r3");
    }
    return result;
}

static int is_factor(void)
{
    return (token == NUMBER || token == LPAREN);
}

static int factor(void)
{
    int result;
    if (token == NUMBER) {
        result = num;
        puts("s5");
        get_token();
        is_factor() ? error(BADTOKEN) : puts("r6");
    } else if (token == LPAREN) {
        puts("s4");
        get_token();
        result = expression();
        if (token == RPAREN) {
            puts("s11");
            get_token();
            is_factor() ? error(BADTOKEN) : puts("r5");
        } else {
            error(NORPAREN);
        }
    } else {
        error(NOFACTOR);
    }
    return result;

}

