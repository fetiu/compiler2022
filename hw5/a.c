#include <stdio.h>

const a = 1;

struct s {
int : 64;
};

main() {
    printf("%d\n", a);
    struct s b;
    printf("%u\n", sizeof(b));
}
