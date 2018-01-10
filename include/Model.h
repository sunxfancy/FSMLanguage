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

enum StatementType {
    StateTy, TransitionTy
};
class Statement {
public:
    Statement() {}
    virtual ~Statement() {}
    virtual StatementType getType() = 0;
};

class State : public Statement {
public:
    State() {}
    virtual ~State() { if (StateList) delete StateList; }
    std::string Name;
    StringVectorP StateList = nullptr;

    State(StringCR name, StringVectorP statelist);
    virtual StatementType getType() { return StateTy; }
};

class Transition : public Statement {
public:
    Transition() {}
    virtual ~Transition() { if (Output) delete Output; }

    std::string BeginState;
    std::string EndState;
    std::string Condition;
    StringVectorP Output = nullptr;

    Transition(StringCR beginstate, StringCR endstate);
    Transition(StringCR beginstate, StringCR endstate, StringCR condition);
    Transition(StringCR beginstate, StringCR endstate, StringCR condition, StringVectorP output);
    virtual StatementType getType() { return TransitionTy; }
};



class FSM {
public:
    FSM() {}
    ~FSM() {
        if (Args) delete Args;
        if (OutArgs) delete OutArgs;
        if (StateList) {
            for (State *ptr : *StateList) { delete ptr; }
            delete StateList;
        }
        if (TransitionList) {
            for (Transition *ptr : *TransitionList) { delete ptr; }
            delete TransitionList;
        }
    }

    std::string Name;
    StringVectorP Args = nullptr;
    StringVectorP OutArgs = nullptr;
    StatePVectorP StateList = nullptr;
    TransitionPVectorP TransitionList = nullptr;
    
    FSM(StringCR name, StringVectorP args, StringVectorP outargs);
    FSM(StringCR name, StringVectorP args, StringVectorP outargs, StatementPVectorP statementlist);
    void push_back(StatementP statement);
};



}