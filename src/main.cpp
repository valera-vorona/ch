#include <iostream>
#include <sstream>
#include <fstream>
#include "options/Driver.h"
#include "struct/Driver.h"

int main(int argc, char *argv[]) {
    std::stringstream options;

    for (int i=1; i < argc; ++i) {
        options << argv[i];
        if (argc - i > 1) {
            options << '\n';
        }
    }

    std::ifstream fstruct("../assets/struct.txt");
    yy_struct::Driver struct_driver;
    struct_driver.parse(fstruct);

    yy_options::Driver options_driver(struct_driver.get_current());
    options_driver.parse(options);
    
    return EXIT_SUCCESS;
}

