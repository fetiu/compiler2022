#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

enum error {
    NOFACTOR,
    NORPAREN,
    INVALID,
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
    case INVALID:
        printf("\ninvalid expression\n");
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
    while (ch == ' ' || ch == '\t' ) {
        // puts(__func__);
        ch = getchar();
    }
    if (isdigit(ch)) {
        char numstr[11] = {ch}; // affords INTMAX = 2,147,483,647
        do {
            ch = getchar();
            strncat(numstr, &ch, 1);
        } while (isdigit(ch) && strlen(numstr) < (sizeof(numstr)-1));
        puts(numstr);
        num = atoi(numstr);
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
        error(INVALID);
    }
    putchar(ch);
}

int main(void)
{
    get_token();
    // puts(__func__);
    int result = expression();
    if (token != END) {
        error(INVALID);
    } else {
        printf(" = %d\n", result);
    }
    return 0;
}

static int expression(void)
{
    // puts(__func__);
    int result = term();
    while (token == PLUS) {
        get_token();
        result = result + term();
    }
    return result;
}

static int term(void)
{
    // puts(__func__);
    int result = factor();
    while (token == STAR) {
        get_token();
        result = result * factor();
    }
    return result;
}

static int factor(void)
{
    // puts(__func__);
    int result;
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

