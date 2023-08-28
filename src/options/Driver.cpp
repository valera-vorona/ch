#include "Driver.h"

namespace yy_options {

    Driver::Driver(std::shared_ptr<yy_struct::Node> structure) : structure(structure) {

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
   
        parse_helper( stream ); 
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

    void Driver::find(const std::string &key) {
        auto child = structure->children.find(key);
        if (child == structure->children.end()) {
            for (auto kv: structure->children) {
                if (kv.second->_default) {
                    structure = kv.second;
                    break;
                } else{
                    //TODO: error: no matches and no defaults
                }
            }
        } else {
            structure = child->second;
        }
    }

    void Driver::set_variable(const std::string &name, const std::string &value) {
        //TODO: check if this vaiable already exists
        variables[name] = value;
    }

    std::ostream& Driver::print(std::ostream &stream) {
        return(stream);
    }

}

