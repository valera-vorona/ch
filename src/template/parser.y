%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 

%define api.namespace {yy_template}
%define api.parser.class {Parser}

%code requires {
  namespace yy_template {
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

%parse-param { yy_template::Scanner &scanner }
%parse-param { yy_template::Driver &driver }

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

%token                  END    0     "end of file"
%token                  UNKNOWN
%token                  IF
%token                  UNLESS
%token                  ELSE
%token                  UPPER
%token <std::string>    STRING

%locations

%%

all: END
    | exprs END
    ;

exprs: expr
    | exprs expr
    ;

expr: '='  STRING {
        scanner.print(driver.get_variable($2));
    }
    | STRING '=' STRING {
        if (!scanner.blocked()) {
            driver.set_variable($1, $3);
        }
    }
    | IF STRING {
        auto value = driver.get_variable($2);
        if (value.empty() || value == "0") {
            scanner.block();
        }
    }
    | UNLESS STRING {
        auto value = driver.get_variable($2);
        if (!value.empty() && value != "0") {
            scanner.block();
        }
    }
    | ELSE {
        scanner.toggle();
    }
    | '=' UPPER '(' STRING ')' {
        if (!scanner.blocked()) {
            std::string value = driver.get_variable($4);
            std::string upper;

            transform(value.begin(), value.end(), std::back_inserter(upper), [](char c){ return std::toupper(c); });
            scanner.print(upper);
        }
    }
    | '/' {
        scanner.unblock();
    }
    ;

%%

void 
yy_template::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Options parser error: " << err_message << " at " << l << "\n";
}

