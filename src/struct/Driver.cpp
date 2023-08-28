#include "Driver.h"

namespace yy_struct {

    Driver::Driver() {
        stack.push(std::make_shared<Node>());
    }

    Driver::~Driver() {
        delete(scanner);
        scanner = nullptr;
        delete(parser);
        parser = nullptr;
    }

    void Driver::parse(std::istream &stream) {
        if(! stream.good() && stream.eof()) {
            return;
        }

        parse_helper(stream);
    }

    void Driver::parse_helper(std::istream &stream) {
        delete(scanner);

        try {
            scanner = new Scanner(&stream);
        } catch( std::bad_alloc &ba ) {
            std::cerr << "Failed to allocate scanner: (" <<
            ba.what() << "), exiting!!\n";
            exit( EXIT_FAILURE );
        }

        delete(parser);

        try {
            parser = new Parser( (*scanner) /* scanner */, 
                                  (*this) /* driver */ );
        }

        catch( std::bad_alloc &ba ) {
            std::cerr << "Failed to allocate parser: (" << 
            ba.what() << "), exiting!!\n";
            exit( EXIT_FAILURE );
        }

        const int accept( 0 );
        if (parser->parse() != accept) {
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

