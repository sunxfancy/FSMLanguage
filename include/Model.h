#pragma once

#include <string>
#include <vector>
#include <memory>
#include "VectorDef.h"

namespace fsm {

class State;
class Transition;
class FSM;
class Statement;
typedef const std::string& StringCR;

VectorAndPtrDefineRename(String, std::string);
VectorAndPtrDefine(FSM);
VectorAndPtrDefine(State);
VectorAndPtrDefine(Transition);
VectorAndPtrDefine(Statement);

class FSM {
public:
    std::string Name;
    StringVectorUP Args;
    StringVectorUP OutArgs;
    StateUPVectorUP StateList;
    TransitionUPVectorUP TransitionList;
    
    FSM(StringCR name, StringVectorUP args, StringVectorUP outargs);
    FSM(StringCR name, StringVectorUP args, StringVectorUP outargs, StatementUPVectorUP statementlist);
    void push_back(StatementUP statement);
};

enum StatementType {
    StateTy, TransitionTy
};
class Statement {
public:
    virtual StatementType getType() = 0;
};

class State : public Statement {
public:
    std::string Name;
    StringVectorUP StateList;

    State(StringCR name, StringVectorUP statelist);
    virtual StatementType getType() { return StateTy; }
};

class Transition : public Statement {
public:
    std::string BeginState;
    std::string EndState;
    std::string Condition;
    StringVectorUP Output;

    Transition(StringCR beginstate, StringCR endstate);
    Transition(StringCR beginstate, StringCR endstate, StringCR condition);
    Transition(StringCR beginstate, StringCR endstate, StringCR condition, StringVectorUP output);
    virtual StatementType getType() { return TransitionTy; }
};

}