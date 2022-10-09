const a = 1;

struct s {
int : 32;
};

main() {
    int c;
    c = a, c = a, c = sizeof(struct s);
    printf("%d\n", a);
    struct s b;
    printf("%u\n", sizeof(b));
}
