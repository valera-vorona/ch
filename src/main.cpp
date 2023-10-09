#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include "options/Driver.h"
#include "struct/Driver.h"
#include "template/Driver.h"

std::string get_env(const char *name) {
    auto s = std::getenv(name);
    return s ? s : std::string();
}

int main(int argc, char *argv[]) {
    int rv = EXIT_SUCCESS;

    try {
        std::stringstream options;

        // joining command line args into one line separating with '\n'
        for (int i=1; i < argc; ++i) {
            options << argv[i];
            if (argc - i > 1) {
                options << '\n';
            }
        }

        // setting up ch_home (the data files home dir)
        std::string ch_home;

        // first finding ".ch" from the current directory and up to the root (excl. root itself) 
        auto pwd = std::filesystem::current_path();
        while (pwd.has_relative_path()) {
            if (std::filesystem::exists(pwd / ".ch")) {
                ch_home = (pwd / ".ch").string();
                break;
            }
            pwd = pwd.parent_path();
        }

        if (ch_home.empty()) {
            // Check CH_HOME and HOME envs
            ch_home = get_env("CH_HOME");
            if (ch_home.empty()) {
                ch_home = get_env("HOME") + "/.ch";
            }
        }

        ch_home += '/';

        // opening the structure file
        std::string fname = ch_home + "struct.txt";
        std::ifstream fstruct(fname);
        if (!fstruct.is_open()) {
            throw std::logic_error("Can't find structure file: \"" + fname + '"');
        }

        // loading the structure
        yy_struct::Driver struct_driver(ch_home + "templates/");
        struct_driver.parse(fstruct);

        // loading the options
        yy_options::Driver options_driver(struct_driver.get_current());
        options_driver.parse(options);

        std::string ofname = options_driver.get_variable("-o");
        if (ofname.empty()) ofname = options_driver.get_variable("--out-file-name");
        if (ofname.empty()) ofname = options_driver.get_variable("name");
        if (ofname.empty()) {
            throw std::logic_error("No output file name specified!");
        }

        int good = 0, bad = 0;

        // generating code with yy_template::Driver.parse()
        for (auto f: options_driver.structure->templates) {
            // prepending absolute template file path if required
            std::string templatefname = std::filesystem::path(f.first).is_absolute() ? f.first : ch_home + f.first;
            std::ifstream ftemplate(templatefname);
            if (!ftemplate.is_open()) {
                throw std::logic_error("Can't find template file: \"" + f.first + '"');
            }

            // appending the file ext got from the structure file
            std::string oname = ofname + f.second;

            //check if file with this name already exists
            if (std::filesystem::exists(oname) && options_driver.get_variable("--force").empty()) {
                std::cerr << "File \"" << oname << "\" exists, use option --force=t to overwrite it!" << std::endl;
                ++bad;
            } else {
                // write
                std::ofstream ofs(oname);
                yy_template::Driver template_driver(&options_driver);
                template_driver.parse(ftemplate, &ofs);
                ++good;
            }
        }

        std::cout << good << " files created, " << bad << " files failed" << std::endl;

    } catch (std::logic_error &e) {
        std::cerr << e.what() << std:: endl;
        rv = EXIT_FAILURE;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std:: endl;
        rv = EXIT_FAILURE;
    }

    return rv;
}

