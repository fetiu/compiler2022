int f(int, long, unsigned [], char *); // TODO: why need a space between unsigned and []?
int g(int a, long b, unsigned c[], char *d, ...);
int h(typedef const int a, const static long b); // TODO: should use specifier-qualifier
auto int i(void)
{
    f(g(1, 2, 0, 0, 1, 2, 3, 4, 5, 6, 3, 4, 5, 3), 1, 0, 0);
}
extern char *j(register char k)
{
    unsigned c[] = {1, 2, 3};
    f(1, 2, c, "abdef");
    h(i(), 2);
}