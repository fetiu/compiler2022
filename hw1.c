#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_SIZE 256
#define is_number(n) (n >= 0 || n <= 9)
#define is_lambda(r) (r == NULL)
#define is_eol(c) (c == EOF || c == '\r' || c == '\n' || c == '\0')

static int calc_expr(const char *expr);

static int char2int(char c)
{
    // calc ascii diff
    int diff = c - '0';
    return diff;
}

static char *split(const char *src, char delim, char **rest, char *buf)
{
    char *dst = buf;
    *dst = '\0';
    if (rest) {
        *rest = NULL;
    }
    int parens = 0;
    while (1) {
        char c = *src;
        // split except for parenthesis
        if (c == delim && parens == 0) {
            *dst = '\0';
            break;
        }
        if (is_eol(c)) {
            *dst = '\0';
            if (strlen(buf) > 0) {
                return buf;
            }
            return NULL;
        } else if (c == '(') {
            parens++;
        } else if (c == ')') {
            parens--;
        }
        // ignore spaces
        if (c != ' ') {
            *dst = c;
            dst++;
        }
        src++;
    }
    if (rest) {
        *rest = (char *)src + 1; // a char next to delim
    }
    return buf;
}

static int calc_factor(const char *factor)
{
    const char *errmsg = NULL;

    // ignore leading spaces
    while (*factor == ' ') {
        factor++;
    }

    if (*factor == '(') {
        char buf[MAX_BUF_SIZE];
        // extract expression inside parentheses
        char *expr = split(factor + 1, ')', NULL, buf);
        if (is_lambda(expr)) {
            errmsg = "empty expression";
            goto error;
        }
        return calc_expr(expr);
    }

    int num = char2int(*factor);
    if (!is_number(num)) {
        errmsg = "factor not a number";
        goto error;
    }
    return num;
error:
    printf("[%s] %s: %s\n", __func__, errmsg, factor);
    exit(-3);
}

static int calc_term(const char *term)
{
    char buf[MAX_BUF_SIZE];
    char *term_rest;
    char *factor = split(term, '*', &term_rest, buf);
    if (is_lambda(factor)) {
        printf("[%s] empty factor in %s\n", __func__, term);
        exit(-2);
    }
    
    if (is_lambda(term_rest)) {
        return calc_factor(factor);
    }
    return calc_factor(factor) * calc_term(term_rest);
}

static int calc_expr(const char *expr)
{
    char buf[MAX_BUF_SIZE];
    char *expr_rest;
    char *term = split(expr, '+', &expr_rest, buf);
    if (is_lambda(term)) {
        printf("[%s] empty term in %s\n", __func__, expr);
        exit(-1);
    }

    if (is_lambda(expr_rest)) {
        return calc_term(term);
    }
    return calc_term(term) + calc_expr(expr_rest);
}

int main(void)
{
    printf("math expr: ");
    char buf[MAX_BUF_SIZE];
    char *expr = gets(buf); // same with getchar until line feed
    if (!expr) {
        return -1;
    }
    int res = calc_expr(expr);
    printf("%s = %d\n", expr, res);
    return 0;
}