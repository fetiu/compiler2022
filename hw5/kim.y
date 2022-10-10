%token IDENTIFIER TYPE_IDENTIFIER INTEGER_CONSTANT FLOAT_CONSTANT CHARACTER_CONSTANT STRING_LITERAL
    PLUS MINUS PLUSPLUS MINUSMINUS STAR SLASH PERCENT LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET ARROW
    EQUAL LESS GREATER EXCLAM LEQ GEQ NEQ AMPAMP BARBAR AMP BAR NOT DOT DOTDOTDOT COLON SEMICOLON COMMA ASSIGN
    AUTO_SYM STATIC_SYM REGISTER_SYM EXTERN_SYM CONST_SYM TYPEDEF_SYM STRUCT_SYM UNION_SYM ENUM_SYM SIZEOF_SYM
    DO_SYM WHILE_SYM FOR_SYM IF_SYM ELSE_SYM SWITCH_SYM CASE_SYM DEFAULT_SYM RETURN_SYM CONTINUE_SYM BREAK_SYM

%start program

%{
#include <stdio.h>

int yylex(void);
int yyerror(const char *s);
int yywrap(void) {return 1;}
%}

%%
program
    : translation_unit
    ;
translation_unit
    : external_declaration
    | translation_unit external_declaration
    ;
external_declaration
    : function_definition
    | declaration
    ;
function_definition
    : declaration_specifiers declarator compound_statement
    | declarator compound_statement
    ;
declaration
    : declaration_specifiers init_declarator_list SEMICOLON
    | declaration_specifiers SEMICOLON /* for unnamed struct/enum */
    ;
declaration_specifiers
    : type_specifier | storage_class_specifer | type_qualifier
    | type_specifier declaration_specifiers
    | storage_class_specifer declaration_specifiers
    | type_qualifier declaration_specifiers
    ;
storage_class_specifer
    : AUTO_SYM | STATIC_SYM | TYPEDEF_SYM | REGISTER_SYM | EXTERN_SYM
    ;
type_qualifier
    : CONST_SYM /* | VOLITILE_SYM */
    ;
init_declarator_list
    : init_declarator
    | init_declarator_list COMMA init_declarator
    ;
init_declarator
    : declarator
    | declarator ASSIGN initializer
    ;
type_specifier
    : struct_specifier | enum_specifier | TYPE_IDENTIFIER
    ;
struct_specifier
    : struct_or_union IDENTIFIER LBRACE struct_declaration_list RBRACE
    | struct_or_union LBRACE struct_declaration_list RBRACE
    | struct_or_union IDENTIFIER
    ;
struct_or_union
    : STRUCT_SYM | UNION_SYM
    ;
struct_declaration_list
    : struct_declaration
    | struct_declaration_list struct_declaration
    ;
struct_declaration
    : specifier_qualifier_list struct_declarator_list SEMICOLON
    ;
specifier_qualifier_list
    : type_specifier | type_qualifier
    | type_specifier specifier_qualifier_list
    | type_qualifier specifier_qualifier_list
    ;
struct_declarator_list
    : struct_declarator
    | struct_declarator_list COMMA struct_declarator
    ;
struct_declarator
    : declarator
    | COLON constant_expression
    | declarator COLON constant_expression
    ;
enum_specifier
    : ENUM_SYM IDENTIFIER LBRACE enumerator_list RBRACE
    | ENUM_SYM LBRACE enumerator_list RBRACE
    | ENUM_SYM IDENTIFIER
    ;
enumerator_list
    : enumerator
    | enumerator_list COMMA enumerator
    | enumerator_list COMMA
    ;
enumerator
    : IDENTIFIER
    | IDENTIFIER ASSIGN constant_expression
    ;
declarator
    : pointer direct_declarator
    | direct_declarator
pointer
    : STAR
    | STAR pointer
    | STAR type_qualifier
    | STAR type_qualifier pointer
    ;
direct_declarator
    : IDENTIFIER
    | LPAREN declarator RPAREN
    | direct_declarator LBRACKET constant_expression_opt RBRACKET
    | direct_declarator LPAREN parameter_type_list_opt RPAREN
    ;
constant_expression_opt
    : /* empty */
    | constant_expression
    ;
parameter_type_list_opt
    : /* empty */
    | parameter_type_list
    ;
parameter_type_list
    : parameter_list
    | parameter_list COMMA DOTDOTDOT
    ;
parameter_list
    : parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;
parameter_declaration
    : declaration_specifiers declarator
    | type_name
    ;
type_name
    : declaration_specifiers
    | declaration_specifiers abstract_declarator
    ;
abstract_declarator
    : pointer
    | direct_abstract_declarator
    | pointer direct_abstract_declarator
    ;
direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN
    | LBRACKET constant_expression_opt RBRACKET
    | LPAREN parameter_type_list_opt RPAREN
    | direct_abstract_declarator LBRACKET constant_expression_opt RBRACKET
    | direct_abstract_declarator LPAREN parameter_type_list_opt RPAREN
    ;
initializer
    : assignment_expression
    | LBRACE initializer_list RBRACE
    | LBRACE initializer_list COMMA RBRACE
    ;
initializer_list
    : initializer
    | initializer_list COMMA initializer
    ;
statement
    : labled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;
labled_statement
    : CASE_SYM constant_expression COLON statement
    | DEFAULT_SYM COLON statement
    /* | IDENTIFIER COLON statement */
    ;
compound_statement
    : LBRACE declaration_list statement_list RBRACE
    ;
declaration_list
    : /* empty */
    | declaration_list declaration
    ;
statement_list
    : /* empty */
    | statement_list statement
    ;
expression_statement
    : SEMICOLON
    | expression SEMICOLON
    ;
selection_statement
    : IF_SYM LPAREN expression RPAREN statement
    | IF_SYM LPAREN expression RPAREN statement ELSE_SYM statement
    | SWITCH_SYM LPAREN expression RPAREN statement
    ;
iteration_statement
    : WHILE_SYM LPAREN expression RPAREN statement
    | DO_SYM statement WHILE_SYM LPAREN expression RPAREN
    | FOR_SYM LPAREN expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RPAREN statement
    ;
expression_opt
    : /* empty */
    | expression
jump_statement
    : RETURN_SYM expression_opt SEMICOLON
    | CONTINUE_SYM SEMICOLON
    | BREAK_SYM SEMICOLON
    /* | GOTO_SYM IDENTIFIER */
    ;
primary_expression
    : IDENTIFIER
    | INTEGER_CONSTANT
    | FLOAT_CONSTANT
    | CHARACTER_CONSTANT
    | STRING_LITERAL
    | LPAREN expression RPAREN
    ;
postfix_expression
    : primary_expression
    | postfix_expression LBRACKET expression RBRACKET
    | postfix_expression LPAREN arg_expression_list_opt RPAREN
    | postfix_expression DOT IDENTIFIER
    | postfix_expression ARROW IDENTIFIER
    | postfix_expression PLUSPLUS
    | postfix_expression MINUSMINUS
    ;
arg_expression_list_opt
    : /* empty */
    | arg_expression_list
    ;
arg_expression_list
    : assignment_expression
    | arg_expression_list COMMA assignment_expression
    ;
unary_expression
    : postfix_expression
    | PLUSPLUS unary_expression
    | MINUSMINUS unary_expression
    | AMP cast_expression
    | STAR cast_expression
    | EXCLAM cast_expression
    | MINUS cast_expression
    | NOT cast_expression
    | PLUS cast_expression
    | SIZEOF_SYM unary_expression
    | SIZEOF_SYM LPAREN type_name RPAREN
    ;
cast_expression
    : unary_expression
    | LPAREN type_name RPAREN cast_expression
    ;
multiplicative_expression
    : cast_expression
    | multiplicative_expression STAR cast_expression
    | multiplicative_expression SLASH cast_expression
    | multiplicative_expression PERCENT cast_expression
    ;
additive_expression
    : multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;
shift_expression
    : additive_expression
    /* | shift_expression LSHIFT additive_expression */
    /* | shift_expression RSHIFT additive_expression */
    ;
relational_expression
    : shift_expression
    | relational_expression LESS shift_expression
    | relational_expression GREATER shift_expression
    | relational_expression LEQ shift_expression
    | relational_expression GEQ shift_expression
    ;
equality_expression
    : relational_expression
    | equality_expression EQUAL relational_expression
    | equality_expression NEQ relational_expression
    ;
AND_expression
    : equality_expression
    | AND_expression AMP equality_expression
    ;
OR_expression
    : AND_expression
    | OR_expression BAR AND_expression
    ;
logical_AND_expression
    : OR_expression
    | logical_AND_expression AMPAMP OR_expression
    ;
logical_OR_expression
    : logical_AND_expression
    | logical_OR_expression BARBAR logical_AND_expression
    ;
conditional_expression
    : logical_OR_expression
    /* | logical_OR_expression QUERY expression COLON conditional_expression */
    ;
assignment_expression
    : conditional_expression
    | unary_expression ASSIGN assignment_expression
    ;
expression
    : assignment_expression
    | expression COMMA assignment_expression
    ;
constant_expression
    : conditional_expression
    ;
%%

int main()
{
    yyparse() || puts("success");
}

extern int yyget_lineno(void);
extern char *yyget_text(void);
int yyerror(const char *s)
{
    printf("line %d: %s near %s\n", yyget_lineno(), s, yyget_text());
    return 0;
}
