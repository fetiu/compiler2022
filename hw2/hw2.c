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

static enum {
    NUL,
    NUMBER,
    PLUS,
    STAR,
    LPAREN,
    RPAREN,
    END
} token;
static double num;

static double expression(void);
static double term(void);
static double factor(void);

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
            putchar(ch);
            ch = getchar();
        } while (isdigit(ch));
        if (ch == '.') {
            int exp = 1;
            putchar(ch);
            ch = getchar();
            do {
                exp *= 10;
                num += (double)todigit(ch) / exp;
                putchar(ch);
                ch = getchar();
            } while (isdigit(ch));
        }
        token = NUMBER;
        return;
    } else if (ch == '+') {
        putchar(ch);
        ch = getchar();
        token = PLUS;
    } else if (ch == '*') {
        putchar(ch);
        ch = getchar();
        token = STAR;
    } else if (ch == '(') {
        putchar(ch);
        ch = getchar();
        token = LPAREN;
    } else if (ch == ')') {
        putchar(ch);
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
    double result = expression();
    if (token != END) {
        error(BADTOKEN);
    } else {
        printf("=%f\n", result);
    }
    return 0;
}

static double expression(void)
{
    double result = term();
    while (token == PLUS) {
        get_token();
        result = result + term();
    }
    return result;
}

static double term(void)
{
    double result = factor();
    while (token == STAR) {
        get_token();
        result = result * factor();
    }
    return result;
}

static double factor(void)
{
    double result;
    if (token == NUMBER) {
        result = num;
        get_token();
    } else if (token == LPAREN) {
        get_token();
        result = expression();
        if (token == RPAREN) {
            get_token();
        } else {
            error(NORPAREN);
        }
    } else {
        error(NOFACTOR);
    }
    return result;
}

