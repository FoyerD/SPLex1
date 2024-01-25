#include "Action.h"

PrintActionsLog::PrintActionsLog(): BaseAction::BaseAction(){}
PrintActionsLog::~PrintActionsLog(){}

PrintActionsLog* PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const{
    return "log " + statusToString[(int)getStatus()];
}


void PrintActionsLog::act(WareHouse& wareHouse){
    string toPrint("");
    for(BaseAction* currAction : wareHouse.getActions()){
        toPrint += currAction->toString() + "\n";
    }
    std::cout << toPrint << std::endl;
    complete();
}