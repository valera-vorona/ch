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
        Driver(const std::string &path_to_templates);

        ~Driver() = default;

    /**
        * parse - parse from a c++ input stream
        * \param[in] is - std::istream&, valid input stream
        */
        void parse(std::istream &is);

        void push_new_child(const std::string &key);

        void pop_child();

        std::shared_ptr<Node> get_current();

        void set_default();


        std::ostream& print(std::ostream &stream);

    private:

        std::stack<std::shared_ptr<Node>> stack;

        std::unique_ptr<Scanner> scanner;
        std::unique_ptr<Parser> parser;

        const std::string path_to_templates;
    };

}

#endif /* __YY_STRUCT_DRIVER__ */

