#ifndef __YY_OPTIONS_DRIVER__
#define __YY_OPTIONS_DRIVER__

#include "Scanner.h"
#include "parser.tab.h"
#include "../struct/Node.h"

#include <unordered_map>
#include <string>
#include <istream>

namespace yy_options {

    class Driver {
    public:
        Driver(std::shared_ptr<yy_struct::Node> structure);

        virtual ~Driver();

        /** 
        * parse - parse from a c++ input stream
        * \param[in] is - std::istream&, valid input stream
        */
        void parse(std::istream &is);

        void find(const std::string &key);

        void set_variable(const std::string &name, const std::string &value);

        std::ostream& print(std::ostream &stream);

    private:
        void parse_helper( std::istream &stream );

        Parser  *parser  = nullptr;
        Scanner *scanner = nullptr;
   
        std::shared_ptr<yy_struct::Node> structure;

        std::unordered_map<std::string, std::string> variables;
    };

}

#endif /* __YY_OPTIONS_DRIVER__ */

