#ifndef __YY_STRUCT_NODE__
#define __YY_STRUCT_NODE__

#include <unordered_map>
#include <string>
#include <memory>

namespace yy_struct {

class Node {
public:
    std::string path;
    bool _default = false;

//private:
    std::unordered_map<std::string, std::shared_ptr<Node>> children;

    friend class Driver;
};

}

#endif /* __YY_STRUCT_NODE__ */

