#include "Driver.h"

namespace yy_template {

    Driver::Driver(const yy_options::Driver *options) : options(options) {

    }

    void Driver::parse(std::istream &stream) {
        scanner = std::make_unique<Scanner>(&stream);
        parser = std::make_unique<Parser>(*scanner.get(), *this);

        if (parser->parse() != 0) {
            //TODO: make some other error reaction
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

