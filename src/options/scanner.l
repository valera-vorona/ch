%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "Scanner.h"
#undef  YY_DECL
#define YY_DECL int yy_options::Scanner::yylex(yy_options::Parser::semantic_type * const lval, yy_options::Parser::location_type *location)

/* using "token" to make the returns for the tokens shorter to type */
using token = yy_options::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="yy_options::Scanner"
%option prefix="Options"
%option noyywrap
%option c++

CMD_BEGIN <<<
CMD_END   >>>
SPACE (\ |\t)

%s parsing

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

<INITIAL>{CMD_BEGIN}    std::cout << "LEX BEGIN" << std:: endl; BEGIN(parsing); return token::CMD_BEGIN; /* begin parsing */

<INITIAL>\n             {
                            loc->lines(); // update line number
                            yylval->emplace<char>('\n');
                            return token::CHAR; /* pass through all the characters */
                        }

<INITIAL>.              {
                            //std::cout << *yytext;
                            yylval->emplace<char>(*yytext);
                            return token::CHAR; /* pass through all the characters */
                        }

<parsing>{CMD_END}      std::cout << "LEX END" << std::endl; BEGIN(INITIAL); return token::CMD_END; /* finish parsing */
<parsing>\n             loc->lines(); // update line number
<parsing>{SPACE}+       { }
<parsing>=              return token::PRINT;
<parsing>.              return token::UNKNOWN;

%%

