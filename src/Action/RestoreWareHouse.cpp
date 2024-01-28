#include "Action.h"
#include "WareHouse.h"
RestoreWareHouse::RestoreWareHouse(): BaseAction::BaseAction(){}
RestoreWareHouse::~RestoreWareHouse(){}

RestoreWareHouse* RestoreWareHouse::clone() const{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const{
    return "restore " + statusToString[(int)BaseAction::getStatus()];
}


void RestoreWareHouse::act(WareHouse& wareHouse){
    if(backup == nullptr){
        error("No backup available");
        return;
    }
    wareHouse = WareHouse(*backup);
    complete();
}