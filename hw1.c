#include <stdio.h>

static int char2int(char c, int *i)
{
    // calc ascii diff
    int diff = c - '0';
    if (diff < 0 || diff > 9) {
        return -1;
    }
    *i = diff;
    return 0;
}

static int is_eol(int a)
{
    return (a == EOF || a == '\r' || a == '\n');
}

int main(void)
{
    printf("math expr: ");
    while (1) {
        char c = getchar();
        if (is_eol(c)) {
            break;
        }
        int d;
        if (char2int(c, &d)) {
            puts("not num");
        } else {
            printf("num: %d\n", d);
        }
    }
    return 0;
}