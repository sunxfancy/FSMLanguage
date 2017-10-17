#pragma once

#include <string>
#include <vector>
#include <memory>

namespace fsm {

class State;
class Transition;

typedef const string& StringCR;
typedef std::vector<std::string> StringVector;
typedef std::unique_ptr<StringVector> StringVectorUP;
typedef std::vector<State> StateVector;
typedef std::unique_ptr<StateVector> StateVectorUP;
typedef std::vector<Transition> TransitionVector;
typedef std::unique_ptr<TransitionVector> TransitionVectorUP;

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