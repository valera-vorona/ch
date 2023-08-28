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
    /* %option nodefault - don't use nodefault in this scanner to make the scanner pass through unknown tokens */
%option yyclass="yy_options::Scanner"
%option prefix="Template"
%option noyywrap
%option c++

BEGIN  <<<
END    >>>

DIGIT   [0-9]
LETTER  [a-zA-Z_]
SYM     ({DIGIT}|{LETTER})
STRING  {LETTER}{SYM}*
SPACE   [\t \r\n]

%x parcing
%x comment

%%

%{                      /** Code executed at the beginning of yylex **/
                        yylval = lval;
%}

<INITIAL>{BEGIN}        BEGIN(parcing);
<INITIAL>\n             location->lines(); yyout << '\n';

<comment>{END}          BEGIN(INITIAL);
<comment>\n             location->lines();
<comment>.              /* eat */

<parcing>{END}          BEGIN(INITIAL);
<parcing>#              BEGIN(comment);
<parcing>\{             return token::BEGIN_BLOCK;
<parcing>\}             return token::END_BLOCK;

<parcing>{STRING}       yylval->emplace<std::string>(yytext); return token::STRING;
<parcing>{SPACE}        /* pass */
<parcing>.              yylval->emplace<std::string>(yytext); return token::UNKNOWN;

%%

