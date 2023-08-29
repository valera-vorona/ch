#include "Driver.h"
#include <fstream>

namespace yy_template {

    Driver::Driver(yy_options::Driver *options) : options(options) {

    }

    void Driver::parse(std::istream &in, std::ostream *out) {
        scanner = std::make_unique<Scanner>(&in, out);
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
        options->set_variable(name, value);
    }

    std::string Driver::get_variable(const std::string &name) const {
        return options->get_variable(name);
    }

    std::ostream& Driver::print(std::ostream &stream) {
        return(stream);
    }

}

