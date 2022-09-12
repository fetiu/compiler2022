#include <stdio.h>

#define MAX_BUF_SIZE 256
#define is_number(n) (n >= 0 || n <= 9)
#define is_lambda(r) (r == NULL)

static int calc_expr(const char *expr);

static int char2int(char c)
{
    // calc ascii diff
    int diff = c - '0';
    return diff;
}

static char *split(const char *src, char delim, char **rest)
{
    static char buf[MAX_BUF_SIZE];

    int pos;

    if (rest) {
        *rest = buf + pos;
    }
    return buf;
}

static int calc_factor(const char *factor)
{
    const char *errmsg;

    // ignore leading spaces
    while (*factor == ' ') {
        factor++;
    }

    if (*factor == '(') {
        // extract expression inside parenthesis
        char *expr = split(factor + 1, ')', NULL);
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
    return 0xDEADBEEF;
}

static int calc_term(const char *term)
{
    char *term_rest;
    char *factor = split(term, '*', &term_rest);
    if (is_lambda(factor)) {
        printf("[%s] empty factor in %s\n", __func__, term);
    }
    
    if (is_lambda(term_rest)) {
        return calc_factor(factor);
    }
    return calc_factor(factor) * calc_term(term_rest);
}

static int calc_expr(const char *expr)
{
    char *expr_rest;
    char *term = split(expr, '+', &expr_rest);
    if (is_lambda(term)) {
        printf("[%s] empty term in %s\n", __func__, expr);
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
    char *expr = gets(buf);
    if (!expr) {
        return -1;
    }
    int res = calc_expr(expr);
    printf("%s = %d\n", expr, res);
    return 0;
}