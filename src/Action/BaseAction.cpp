#include "Action.h"
#include "WareHouse.h"
/**
 * sets errorMsg to epty string
 * sets status to ACTIVE
*/
BaseAction::BaseAction():
                        errorMsg("INTERRUPTED"),
                        status(ActionStatus::ERROR){}
BaseAction::~BaseAction(){};

/**
 * sets status to COMPLETE
*/
void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
    errorMsg = "";    
}

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