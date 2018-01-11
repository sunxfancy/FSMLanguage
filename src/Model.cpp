#include "Model.h"
#include <iostream>

using namespace std;
using namespace fsm;

FSM::FSM (StringCR name, StringVectorP args, StringVectorP outargs) {
    this->Name = name;
    this->Args = args;
    this->OutArgs = outargs;
}

FSM::FSM (StringCR name, StringVectorP args, StringVectorP outargs, 
    StatementPVectorP statementlist) {
    this->Name = name;
    this->Args = args;
    this->OutArgs = outargs;
    for (auto p : *statementlist) {
        push_back(p);
    }
}

void FSM::push_back(StatementP statement) {
    if (statement->getType() == StatementType::StateTy) {
        StateP sup(dynamic_cast<StateP>(statement));
        this->StateList.push_back(sup);
    }
    if (statement->getType() == StatementType::TransitionTy) {
        TransitionP tup(dynamic_cast<TransitionP>(statement));
        this->TransitionList.push_back(tup);
    }
}


void FSM::print() {
    cout << Name;
    cout << " ( " << *Args << " ) " << *OutArgs;
    cout << " {" << endl;
    for (auto p : StateList) {
        cout << '\t' << *p << endl;
    }
    cout << endl;
    for (auto p : TransitionList) {
        cout << '\t' << *p << endl;
    }
    cout << "}" << endl;
}


State::State(StringCR name, StringVectorP statelist) {
    this->Name = name;
    this->StateList = statelist;
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

Transition::Transition(StringCR beginstate, StringCR endstate, StringCR condition, StringVectorP output) {
    this->BeginState = beginstate;
    this->EndState = endstate;
    this->Condition = condition;
    this->Output = output;
}