#include "Model.h"

using namespace std;
using namespace fsm;

FSM::FSM (StringCR name, StringVectorUP args, StringVectorUP outargs) {
    this->Name = name;
    this->Args = move(args);
    this->OutArgs = move(outargs);
}

FSM::FSM (StringCR name, StringVectorUP args, StringVectorUP outargs, 
    StatementUPVectorUP statementlist) {
    this->Name = name;
    this->Args = move(args);
    this->OutArgs = move(outargs);
    for (auto p : *statementlist) {
        push_back(move(p));
    }
}

void FSM::push_back(StatementUP statement) {
    if (statement->getType() == StatementType::StateTy) {
        StateUP sup(dynamic_cast<State*>(statement.release()));
        this->StateList->push_back(move(sup));
    }
    if (statement->getType() == StatementType::TransitionTy) {
        TransitionUP tup(dynamic_cast<Transition*>(statement.release()));
        this->TransitionList->push_back(move(tup));
    }
}


State::State(StringCR name, StringVectorUP statelist) {
    this->Name = name;
    this->StateList = move(statelist);
}



Transition::Transition(StringCR beginstate, StringCR endstate) {
    this->BeginState = beginstate;
    this->EndState = endstate;
}

Transition::Transition(StringCR beginstate, StringCR endstate, StringCR condition) {
    this->BeginState = beginstate;
    this->EndState = endstate;
    this->Condition = condition;
}

Transition::Transition(StringCR beginstate, StringCR endstate, StringCR condition, StringVectorUP output) {
    this->BeginState = beginstate;
    this->EndState = endstate;
    this->Condition = condition;
    this->Output = move(output);
}