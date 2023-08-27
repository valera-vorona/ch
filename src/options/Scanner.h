#ifndef __YY_OPTIONS_SCANNER__
#define __YY_OPTIONS_SCANNER__

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer OptionsFlexLexer
#include <FlexLexer.h>
#endif

#include "generated/parser.tab.h"
//#include "location.hh"

namespace yy_options {

class Scanner : public yyFlexLexer{
public:
   
   Scanner(std::istream *in) : yyFlexLexer(in)
   {
      loc = new Parser::location_type();
   };
  
   //get rid of override virtual function warning
//   using FlexLexer::yylex;

   virtual
   int yylex( Parser::semantic_type * const lval, 
              Parser::location_type *location );
   // YY_DECL defined in mc_lexer.l
   // Method body created by flex in mc_lexer.yy.cc


private:
   /* yyval ptr */
   Parser::semantic_type *yylval = nullptr;
   /* location ptr */
   Parser::location_type *loc    = nullptr;
};

}

#endif /* __YY_OPTIONS_SCANNER__ */

