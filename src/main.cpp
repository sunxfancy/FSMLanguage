#include <iostream>
#include "Module.h"

int main(int argc, const char** argv) {
    fsm::Module mod;
    mod.src = fopen(argv[1], "r");
    mod.Parse();
    fclose(mod.src);
    for (auto p : *(mod.root)) {
        p->print();
    }
    return 0;
}