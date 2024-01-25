#include "Action.h"

BackupWareHouse::BackupWareHouse(): BaseAction::BaseAction(){}
BackupWareHouse::~BackupWareHouse(){}

BackupWareHouse* BackupWareHouse::clone() const{
    return new BackupWareHouse(*this);
}

string BackupWareHouse::toString() const{
    return "backup " + statusToString[(int)getStatus()];
}


void BackupWareHouse::act(WareHouse& wareHouse){
    if(backup != nullptr) delete backup;
    backup = new WareHouse(wareHouse);
    complete();
}