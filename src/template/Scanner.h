#ifndef __YY_TEMPLATE_SCANNER__
#define __YY_TEMPLATE_SCANNER__

#ifndef yyFlexLexerOnce
#undef yyFlexLexer
#define yyFlexLexer OptionsFlexLexer
#include <FlexLexer.h>
#endif

#include "template/parser.tab.h"
#include <memory>

namespace yy_template {

    class Scanner : public yyFlexLexer {
    public:
   
        Scanner(std::istream *in) : yyFlexLexer(in), location(std::make_unique<Parser::location_type>()) {

        }

        /* virtual */  
        int yylex(Parser::semantic_type *const lval, Parser::location_type *location);

        // YY_DECL defined in scanner.l
        // Method body created by flex in lexer.yy.cpp

    private:
        /* yyval ptr */
        Parser::semantic_type *yylval = nullptr;

        /* location ptr */
        std::unique_ptr<Parser::location_type> location;
    };

}

#endif /* __YY_TEMPLATE_SCANNER__ */

