#include "Model.h"

using namespace std;
using namespace fsm;

FSM::FSM (StringCR name, StringVectorUP args, StringVectorUP outargs) {
    this->Name = name;
    this->Args = move(args);
    this->OutArgs = move(outargs);
}

FSM::FSM (StringCR name, StringVectorUP args, StringVectorUP outargs, 
    StateVectorUP statelist, TransitionVectorUP transitionlist) {
    this->Name = name;
    this->Args = move(args);
    this->OutArgs = move(outargs);
    this->StateList = move(statelist);
    this->TransitionList = move(transitionlist);
}

void FSM::push_back(StatementUP statement) {
    if (statement->getType() == StatementType::StateTy) {
        this->StateList->push_back(statement.release());
    }
    if (statement->getType() == StatementType::TransitionTy) {
        this->TransitionList->push_back(statement.release());
    }
}


State::State(StringCR name, StringVectorUP statelist) {
    this->Name = name;
    this->StateList = move(statelist);
}

Transition::Transition(StringCR beginstate, StringCR endstate, StringCR condition, StringVectorUP output) {
    this->BeginState = beginstate;
    this->EndState = endstate;
    this->Condition = condition;
    this->Output = move(output);
}