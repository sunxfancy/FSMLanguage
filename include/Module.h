#pragma once

#include <cstdio>
#include "Model.h"

namespace fsm {


class Module {
public:
    FILE *src;
    char* buffer;
    FSMUPVectorUP root;

    int Parse();
};

}