digit   [0-9]
letter  [a-zA-z_]
delim   [ \t]
line    [\n]
ws      {delim}+
%{
#include "y.tab.h"
%}
%%
{ws}        {}
{line}      {yyset_lineno(yyget_lineno()+1);}
auto        {return AUTO_SYM;}
break       {return BREAK_SYM;}
case        {return CASE_SYM;}
continue    {return CONTINUE_SYM;}
default     {return DEFAULT_SYM;}
do          {return DO_SYM;}
else        {return ELSE_SYM;}
enum        {return ENUM_SYM;}
for         {return FOR_SYM;}
if          {return IF_SYM;}
return      {return RETURN_SYM;}
sizeof      {return SIZEOF_SYM;}
static      {return STATIC_SYM;}
struct      {return STRUCT_SYM;}
switch      {return SWITCH_SYM;}
typedef     {return TYPEDEF_SYM;}
union       {return UNION_SYM;}
while       {return WHILE_SYM;}
"\+\+"      {return PLUSPLUS;}
"\-\-"      {return MINUSMINUS;}
"\->"       {return ARROW;}
"<"         {return LESS;}
">"         {return GREATER;}
"<="        {return LEQ;}
">="        {return GEQ;}
"!="        {return NEQ;}
"=="        {return EQUAL;}
"&&"        {return AMPAMP;}
"||"        {return BARBAR;}
"\.\.\."    {return DOTDOTDOT;}
"\("        {return LPAREN;}
"\)"        {return RPAREN;}
"\["        {return LBRACKET;}
"\]"        {return RBRACKET;}
"\{"        {return LBRACE;}
"\}"        {return RBRACE;}
"\:"        {return COLON;}
"\."        {return DOT;}
"\,"        {return COMMA;}
"\!"        {return EXCLAM;}
"\*"        {return STAR;}
"\/"        {return SLASH;}
"\%"        {return PERCENT;}
"\&"        {return AMP;}
"\;"        {return SEMICOLON;}
"\+"        {return PLUS;}
"\-"        {return MINUS;}
"\="        {return ASSIGN;}
{digit}+                    {return INTEGER_CONSTANT;}
{digit}+\.{digit}+          {return FLOAT_CONSTANT;}
{letter}({letter}|{digit})* {return IDENTIFIER;}
\"([^"\n]|\\["\n])*\"       {return STRING_LITERAL;}
\'([^'\n]|\'\')\'           {return CHARACTER_CONSTANT;}
%%
