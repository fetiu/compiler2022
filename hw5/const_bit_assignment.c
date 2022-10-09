const a = 1;

struct s {
int : 32;
};

extern int printf(const char *fmt, ...);
extern int printf2(const char **fmt, ...);
extern int printf2(const char **const fmt, ...);
extern int printf3(const char *const *fmt, ...);
extern int printf4(const char *const *const fmt, ...);

main() {
    int c;
    c = a, c = a, c = sizeof(struct s);
    printf("%d\n", a);
    struct s b;
    printf("%zu\n", sizeof b);
}
