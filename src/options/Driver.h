#ifndef __YY_OPTIONS_DRIVER__
#define __YY_OPTIONS_DRIVER__

#include "Scanner.h"
#include "parser.tab.h"
#include "../struct/Node.h"

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

namespace yy_options {

    class Driver {
    public:
        Driver(std::shared_ptr<yy_struct::Node> structure);

        ~Driver() = default;

        /** 
        * parse - parse from a c++ input stream
        * \param[in] is - std::istream&, valid input stream
        */
        void parse(std::istream &is);

        void find(const std::string &key);

        void set_variable(const std::string &name, const std::string &value);

        std::string get_variable(const std::string &name) const;

        std::ostream& print(std::ostream &stream);

    private:

        std::unique_ptr<Scanner> scanner;
        std::unique_ptr<Parser> parser;
   
        std::shared_ptr<yy_struct::Node> structure;

        std::unordered_map<std::string, std::string> variables;
    };

}

#endif /* __YY_OPTIONS_DRIVER__ */

