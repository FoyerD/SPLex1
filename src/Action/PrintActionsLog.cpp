#include "Action.h"

PrintActionsLog::PrintActionsLog(): BaseAction::BaseAction(){}
PrintActionsLog::~PrintActionsLog(){}

PrintActionsLog* PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const{
    return "log";
}


void PrintActionsLog::act(WareHouse& wareHouse){
    for(BaseAction* currAction : wareHouse.getActions()){
        
    }
    complete();
}