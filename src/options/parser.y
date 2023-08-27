%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 

%define api.namespace {yy_options}
%define api.parser.class {Parser}

%code requires {
  namespace yy_options {
    class Driver;
    class Scanner;
  }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { yy_options::Scanner &scanner }
%parse-param { yy_options::Driver &driver }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "Driver.h"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token               UNKNOWN
%token               END    0     "end of file"
%token               CMD_BEGIN
%token               CMD_END
%token               PRINT
%token <std::string> WORD
%token               NEWLINE
%token <char>        CHAR

%locations

%%

all: END
    | inputs END
    ;

inputs: input
    | inputs input
    ;

input: chars
    | CMD_BEGIN commands CMD_END
    | CMD_BEGIN CMD_END
    ;

chars: CHAR { std::cout << $1; }
    | chars CHAR { std::cout << $2; }
    ;

commands: command
    | commands command
    ;

command: PRINT { std::cout << "PRINT" << std::endl; }
    ;

/*list_option : END | list END;

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( $1 ); }
  | NEWLINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;
*/
%%


void 
yy_options::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}

