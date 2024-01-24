#include "Action.h"

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
*/
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
}

string BaseAction::getErrorMsg() const{return errorMsg;}