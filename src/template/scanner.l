%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "Scanner.h"
#undef  YY_DECL
#define YY_DECL int yy_template::Scanner::yylex(yy_template::Parser::semantic_type *const lval, yy_template::Parser::location_type *location)

/* using "token" to make the returns for the tokens shorter to type */
using token = yy_template::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION location->step(); location->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="yy_options::Scanner"
%option prefix="Options"
%option noyywrap
%option c++

STRING [^=\n]+

%%

%{                      /** Code executed at the beginning of yylex **/
                        yylval = lval;
%}

=                       return '='; 
\n                      location->lines(); // update line number
{STRING}                std::cout << yytext << std::endl; yylval->emplace<std::string>(yytext); return token::STRING;

%%

