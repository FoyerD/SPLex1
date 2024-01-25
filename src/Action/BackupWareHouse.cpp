#include "Action.h"

BackupWareHouse::BackupWareHouse(): BaseAction::BaseAction(){}
BackupWareHouse::~BackupWareHouse(){}

BackupWareHouse* BackupWareHouse::clone() const{
    return new BackupWareHouse(*this);
}

string BackupWareHouse::toString() const{
    return "BackupWareHouse " + statusToString[(int)getStatus()];
}


void BackupWareHouse::act(WareHouse& wareHouse){
    
    complete();
}