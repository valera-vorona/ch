#ifndef __YY_TEMPLATE_DRIVER__
#define __YY_TEMPLATE_DRIVER__

#include "Scanner.h"
#include "parser.tab.h"
#include "../struct/Node.h"
#include "../options/Driver.h"

#include <memory>
#include <string>
#include <iostream>

namespace yy_template {

    class Driver {
    public:
        Driver(yy_options::Driver *options);

        ~Driver() = default;

        /** 
        * parse - parse from a c++ input stream
        * \param[in] in - std::istream&, input stream
        * \param[in] out - std::ostream *, output stream, stdout by default
        */
        void parse(std::istream &in, std::ostream *out = nullptr);

        void find(const std::string &key);

        void set_variable(const std::string &name, const std::string &value);

        std::string get_variable(const std::string &name) const;

        std::ostream& print(std::ostream &stream);

    private:
        std::unique_ptr<Scanner> scanner;
        std::unique_ptr<Parser> parser;
   
        std::shared_ptr<yy_struct::Node> structure;

        yy_options::Driver *options;
    };

}

#endif /* __YY_TEMPLATE_DRIVER__ */

