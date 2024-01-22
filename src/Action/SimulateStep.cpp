#include "Action.h"


/**
 * @param numOfSteps - number of steps te action simulates
*/
SimulateStep::SimulateStep(int numOfSteps):
                        BaseAction::BaseAction(),
                        numOfSteps(numOfSteps){}
SimulateStep::~SimulateStep(){}

SimulateStep* SimulateStep::clone() const{
    return new SimulateStep(*this);
}

string SimulateStep::toString() const{
    return "simulateStep " + std::to_string(numOfSteps);
}


/**
 * calles calles singleStep numOfSteps times
*/
void SimulateStep::act(WareHouse& wareHouse){
    for(int i = 0; i < numOfSteps;i++){
        singleStep(wareHouse);
    }
}

void SimulateStep::singleStep(WareHouse& WareHouse){
    for(Order& currOrder : WareHouse.getOrder();)
}