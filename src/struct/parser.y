%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 

%define api.namespace {yy_struct}
%define api.parser.class {Parser}

%code requires {
  namespace yy_struct {
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

%parse-param { yy_struct::Scanner &scanner }
%parse-param { yy_struct::Driver &driver }

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
%token <std::string> WORD 
%token <std::string> STRING 
%token               DEFAULT 
%token               PATH 
%token               TEMPLATE

%type <std::string> string

%locations

%%

all: exprs END
    ;

exprs: %empty
    | expr
    | exprs expr
    ;

expr: WORD {
        driver.push_new_child($1);
    } mb_default '{' exprs '}' {
        driver.pop_child();
    }
    | PATH '=' string ';' {
        driver.get_current()->path = $3;
    }
    | TEMPLATE '=' string string ';' {
        driver.get_current()->templates.push_back({$3, $4});
    }
    ;

string: STRING
    | WORD
    ;

mb_default: %empty
    | DEFAULT {
        driver.set_default();
    }
    ;

%%

void 
yy_struct::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Struct parser error: " << err_message << " at " << l << "\n";
}

