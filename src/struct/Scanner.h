#ifndef __YY_STRUCT_SCANNER__
#define __YY_STRUCT_SCANNER__

#ifndef yyFlexLexerOnce
#undef yyFlexLexer
#define yyFlexLexer StructFlexLexer
#include <FlexLexer.h>
#endif

#include "struct/parser.tab.h"

namespace yy_struct {

    class Scanner : public yyFlexLexer {
    public:
        Scanner(std::istream *in) : yyFlexLexer(in) {
            loc = new Parser::location_type();
        }
  
        /* virtual */
        int yylex(Parser::semantic_type *const lval, Parser::location_type *location);

        // YY_DECL defined in scanner.l
        // Method body created by flex in lexer.yy.cpp

    private:
        /* yyval ptr */
        Parser::semantic_type *yylval = nullptr;

        /* location ptr */
        Parser::location_type *loc    = nullptr;
    };

}

#endif /* __YY_STRUCT_SCANNER__ */

