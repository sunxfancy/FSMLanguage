#pragma once

#include <string>
#include <vector>
#include <memory>
#include "VectorDef.h"

namespace fsm {

class State;
class Transition;
class FSM;
typedef const std::string& StringCR;

VectorAndPtrDefineRename(String, std::string);
VectorAndPtrDefine(FSM);
VectorAndPtrDefine(State);
VectorAndPtrDefine(Transition);

class FSM {
public:
    std::string Name;
    StringVectorUP Args;
    StringVectorUP OutArgs;
    StateVectorUP StateList;
    TransitionVectorUP TransitionList;

    FSM(StringCR name, StringVectorUP args, StringVectorUP outargs, StateVectorUP statelist, TransitionVectorUP transitionlist);
};

class State {
public:
    std::string Name;
    StringVectorUP StateList;

    State(StringCR name, StringVectorUP statelist);
};

class Transition {
    std::string BeginState;
    std::string EndState;
    std::string Condition;
    StringVectorUP Output;

    Transition(StringCR beginstate, StringCR endstate, StringCR condition, StringVectorUP output);
};

}