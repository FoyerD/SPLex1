#include "Volunteer.h"

/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param maxDistance - The maximum distance of ANY order the volunteer can take
 * @param distancePerStep - The distance the volunteer does in one step
*/
DriverVolunteer::DriverVolunteer(int id,string name, int maxDistance, int distancePerStep):
                                Volunteer::Volunteer(id,name),
                                maxDistance(maxDistance),
                                distancePerStep(distancePerStep),
                                distanceLeft(0){}
