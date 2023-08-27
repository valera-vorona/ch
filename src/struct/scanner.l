%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "Scanner.h"
#undef  YY_DECL
#define YY_DECL int yy_struct::Scanner::yylex(yy_struct::Parser::semantic_type * const lval, yy_struct::Parser::location_type *location)

/* using "token" to make the returns for the tokens shorter to type */
using token = yy_struct::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="yy_struct::Scanner"
%option prefix="Struct"
%option noyywrap
%option c++

DIGIT   [0-9]
LETTER  [a-zA-Z_]
SYM     ({DIGIT}|{LETTER})
WORD    {LETTER}{SYM}*
SPACE   [\t ]
EOL     \r?\n

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

_default                std::cout << "DEFAULT" << std::endl; return token::DEFAULT;
path                    return token::PATH;
{WORD}                  std::cout << "WORD: " << yytext << std::endl; yylval->emplace<std::string>(yytext); return token::WORD;
=                       std::cout << '=' << std::endl; return '='; 
\{                      std::cout << '{' << std::endl; return '{'; 
\}                      std::cout << '}' << std::endl; return '}'; 
.                       /* pass */
\n                      loc->lines(); // update line number

%%

