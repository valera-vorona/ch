#ifndef __YY_STRUCT_NODE__
#define __YY_STRUCT_NODE__

#include <unordered_map>
#include <string>
#include <list>
#include <memory>

namespace yy_struct {

class Node {
public:
    std::string path;

    /// list of pairs: first - template file name, ext to add to the produced file
    std::list<std::pair<std::string, std::string>> templates;
    bool _default = false;

//private:
    std::unordered_map<std::string, std::shared_ptr<Node>> children;

    friend class Driver;
};

}

#endif /* __YY_STRUCT_NODE__ */

