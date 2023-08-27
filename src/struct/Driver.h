#ifndef __YY_STRUCT_DRIVER__
#define __YY_STRUCT_DRIVER__

#include <string>
#include <cstddef>
#include <istream>

#include "Scanner.h"
#include "parser.tab.h"

// needed for yy_struct::Node class
#include <unordered_map>
#include <stack>
#include <string>
#include <memory>

namespace yy_struct {

class Node {
public:
    std::string path;

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> children;

    friend class Driver;
};

class Driver {
public:
   Driver();

   virtual ~Driver();
   
   /** 
    * parse - parse from a file
    * @param filename - valid string with input file
    */
   void parse( const char *filename );
   /** 
    * parse - parse from a c++ input stream
    * @param is - std::istream&, valid input stream
    */
   void parse( std::istream &iss );

   void push_new_child(const std::string &name);

   void pop_child();

    std::shared_ptr<Node> get_current() {
        return stack.top();
    }

   std::stack<std::shared_ptr<Node>> stack;

   std::ostream& print(std::ostream &stream);
private:

   void parse_helper( std::istream &stream );

   std::size_t  chars      = 0;
   std::size_t  words      = 0;
   std::size_t  lines      = 0;
   std::size_t  uppercase  = 0;
   std::size_t  lowercase  = 0;
   Parser  *parser  = nullptr;
   Scanner *scanner = nullptr;
   
   /** define some pretty colors **/
   const std::string red   = "\033[1;31m";
   const std::string blue  = "\033[1;36m";
   const std::string norm  = "\033[0m";
};

}

#endif /* __YY_STRUCT_DRIVER__ */

