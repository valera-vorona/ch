#ifndef __YY_STRUCT_DRIVER__
#define __YY_STRUCT_DRIVER__

#include "Node.h"
#include "Scanner.h"
#include "parser.tab.h"

#include <string>
#include <istream>
#include <stack>
#include <memory>

namespace yy_struct {

    class Driver {
    public:
        Driver();

        virtual ~Driver();

    /**
        * parse - parse from a c++ input stream
        * \param[in] is - std::istream&, valid input stream
        */
        void parse(std::istream &is);

        void push_new_child(const std::string &key);

        void pop_child();

        std::shared_ptr<Node> get_current();

        void set_default();

        std::stack<std::shared_ptr<Node>> stack;

        std::ostream& print(std::ostream &stream);

    private:

        void parse_helper( std::istream &stream );

        Parser  *parser  = nullptr;
        Scanner *scanner = nullptr;
    };

}

#endif /* __YY_STRUCT_DRIVER__ */

