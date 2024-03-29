#include "Action.h"
#include "WareHouse.h"
/**
 * sets errorMsg to epty string
 * sets status to ACTIVE
*/
BaseAction::BaseAction():
                        errorMsg(""),
                        status(ActionStatus::COMPLETED){}
BaseAction::~BaseAction(){};


/**
 * sets status to ERROR
 * sets errorMsg to errorMsg given
 * prints the error to the screen
*/
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    std::cout << "ERROR: " + getErrorMsg() << std::endl;
}

string BaseAction::getErrorMsg() const{return errorMsg;}

ActionStatus BaseAction::getStatus() const{return status;}