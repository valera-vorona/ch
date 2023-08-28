#include "Driver.h"

namespace yy_struct {

    Driver::Driver() {
        stack.push(std::make_shared<Node>());
    }

    void Driver::parse(std::istream &stream) {
        scanner = std::make_unique<Scanner>(&stream);
        parser = std::make_unique<Parser>(*scanner.get(), *this);

        if (parser->parse() != 0) {
            //TODO: make some other error reaction
            std::cerr << "Parse failed!!\n";
        }
    }

    void Driver::push_new_child(const std::string &key) {
        auto child = std::make_shared<Node>();
        //TODO: check if such a key already exists
        stack.top()->children[key] = child;
        stack.push(child);
    }

    void Driver::pop_child() {
        if (stack.empty()) {}
        stack.pop();
    }

    std::shared_ptr<Node> Driver::get_current() {
        return stack.top();
    }

    void Driver::set_default() {
        if (stack.size() > 1) {
            auto current = stack.top();
            stack.pop();
            for (auto kv : stack.top()->children) {
                if (kv.second->_default) {
                    //TODO: error, default already exists!
                }
            }
            stack.push(current);

            current->_default = true;
        }
    }

    std::ostream& Driver::print(std::ostream &stream) {
        return(stream);
    }

}

