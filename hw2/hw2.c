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

typedef struct {
    enum {
        INT,
        FLOAT
    } type;
    union {
        int i;
        double f;
    } val;
} number;

static number num;
static enum {
    NUL,
    NUMBER,
    PLUS,
    STAR,
    LPAREN,
    RPAREN,
    END
} token;

static number expression(void);
static number term(void);
static number factor(void);

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
        num.type = INT;
        num.val.i = 0;
        do {
            num.val.i = num.val.i * 10 + todigit(ch);
            putchar(ch);
            ch = getchar();
        } while (isdigit(ch));
        if (ch == '.') {
            num.type = FLOAT;
            num.val.f = num.val.i;
            double exp = 1;
            putchar(ch);
            ch = getchar();
            while (isdigit(ch)) {
                exp *= 10;
                num.val.f += todigit(ch) / exp;
                putchar(ch);
                ch = getchar();
            }
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
    number result = expression();
    if (token != END) {
        error(BADTOKEN);
    } else if (result.type == FLOAT) {
        printf("=%f\n", result.val.f);
    } else {
        printf("=%i\n", result.val.i);
    }
    return 0;
}

static number expression(void)
{
    number result = term();
    while (token == PLUS) {
        get_token();
        number rest = term();
        if (result.type == INT && rest.type == FLOAT) {
            result.type = FLOAT;
            result.val.f = result.val.i + rest.val.f;
        } else if (result.type == FLOAT && rest.type == INT){
            result.val.f += rest.val.i;
        } else if (result.type == FLOAT && rest.type == FLOAT) {
            result.val.f += rest.val.f;
        } else {
            result.val.i += rest.val.i;
        }
    }
    return result;
}

static number term(void)
{
    number result = factor();
    while (token == STAR) {
        get_token();
        number rest = factor();
        if (result.type == INT && rest.type == FLOAT) {
            result.type = FLOAT;
            result.val.f = result.val.i * rest.val.f;
        } else if (result.type == FLOAT && rest.type == INT){
            result.val.f *= rest.val.i;
        } else if (result.type == FLOAT && rest.type == FLOAT) {
            result.val.f *= rest.val.f;
        } else {
            result.val.i *= rest.val.i;
        }
    }
    return result;
}

static number factor(void)
{
    number result;
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
