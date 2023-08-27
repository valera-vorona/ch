#include <string>
#include <iostream>
#include "Driver.h"

struct Options {
    enum {
        CREATE
    } cmd;

    enum {
        CLASS
    } what;

    void run();

private:
    void create();
};

void Options::run() {
    switch (cmd) {
        case CREATE:
            create();
            break;
    }
}

void Options::create() {
    switch (what) {
        case CLASS:
            break;
    }
}

int main(int argc, char *argv[]) {
    using namespace std;

    Options o;

    for (int i=1; i< argc; ++i) {
        cout << argv[i] << endl;
    }

    if (argc > 2) {
        if ("create" == argv[1]) {
            o.cmd = o.CREATE;
            if (argc > 3) {
                if ("class" == argv[2]) {
                    o.what = o.CLASS;
                }
            }
        }
    }

    o.run();

    yy::Driver driver;
    driver.parse("../assets/template.class.h");    
    //driver.parse("main.cpp");    

    std::cout << "Bye" << std::endl;

    return 0;
}

