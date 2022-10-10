main() {
    // declaration
    int a = 1;
    float b = 1.2;
    char c = 'c';
    char d[] = "hello";
    static char *e = "world!";
    struct s {int (*f)();} g;
    struct s *h = g;
    int i = 0;

    // initializer
    long j[] = {1,2,3,4,5,6,7};
    long k[100] = {0,};

    // assignemt expressions
    a = 2;
    b = 2342385235.3243;
    c = 'z';
    e = d;

    /* conditional expressions */
    a = b || c; // logical OR expression
    a = b && c; // logical AND expression
    a = a | c;  // OR expression
    a = a & c;  // AND expression

    /* relational expression */
    a = b == c;
    a = b != c;
    a = b <= c;
    a = b >= c;
    a = b < c;
    a = b > c;

    // additive expression
    a = b + c;
    a = b - c;

    // multipicative expression
    a = b * c;
    a = b / c;
    a = a % c;

    // cast expression
    a = (unsigned)(b / c + (char)(b - 3) * 5.2) % c;

    // unary expression
    ++a;
    --a;
    &a;
    *e;
    !e;
    -a;
    ~a;
    +a;
    sizeof +a;
    sizeof "hello world";
    sizeof (signed long);

    // postfix expression
    a++;
    a--;
    h->f();
    g.f = 0;
    h->f(a = b, b = c);
    d[a + b * c];

    // primary expression
    (a + g.f() + c);
    "string literals";
    'c', 'b', 'd', 'h';
    1.23, 6.23423, 123123.3;
    1,2,3,4,5,6,7,8,9;
    any_identifier;

    // jump statement
    break;
    continue;
    return;
    return 0;
    return h->f();

    // iteration statement
    for (i = 0; i < a; i++) h->f();
    for (i = 0; i < a; i++) {
        h->f();
        g.f();
    }
    do h->f(); while(a);
    do {
        h->f();
        a = b + c;
    } while(a);
    while (a) {
        h->f();
    }

    // selection statement
    switch (a)
    switch (a) {}
    if (a > c) g.f(); else h->f();
    if (a > b) {
        h->f();
    } else if (b > a) {
        g.f();
    }
    if (a > b)
        h->f();
    if (c > a)
        g.f();
    else
        d[a] = c;
    if (a) d[a] = b;

    // expression statement
    ;

    // labled statement
    case 'c': h->f();
    case 'c': {
        g.f();
        h->f();
    }
    default: g.f();
    default: {
        g.f();
        h->f();
    }
}