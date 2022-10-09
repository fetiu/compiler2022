const a = 1;

struct s {
    int : 32;
} b; // FIXME: should be compiled without b

extern int printf(const char *fmt, ...);
extern int printf2(const char **fmt, ...);
extern int printf2(const char **const fmt, ...);
extern int printf3(const char *const *fmt, ...);
extern int printf4(const char *const *const fmt, ...);

main() {
    int c;
    struct {struct s d;} e;
    c = a, c = a, c = sizeof(struct s);
    printf("%d\n", a);
    printf("%zu\n", sizeof b);
    c = a + (long)&b + (int)&e.d;
}
