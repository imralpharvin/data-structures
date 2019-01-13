/**
 * @file simulation.h
 * @author Ralph Arvin De Castro
 * @date June 2018
 * @brief File containing the function definitions needed for the simulation
 */

#ifndef _SIMULATION_
#define _SIMULATION_

#include <stdio.h>
#include <stdlib.h>

/**Adds car to their respective queues
*@param allQueue double pointer of queue N S E W
*@param allCars pointer queue of all cars
**/
void addCarToQueues(Queue * allQueue[], Queue * allCars);

/**Updates intersection queue or the wait list for the intersection
*@param allQueue double pointer of queue N S E W
*@param intersectionQueue pointer of queue that has the wait list
*@param waitTimer timer that determines if a car can move to the front of the queue
*@param waitCar the car that must wait
**/
void updateintersectionQueue (Queue * allQueue[], Queue * intersectionQueue, double waitTimer, char waitCar);

/**remove car from queues once it goes through the intersection
*@return pointer to the car that is removed
*@param allQueue double pointer of queue N S E W
*@param intersectionQueue pointer of queue that has the wait list
**/
Car * removeCarFromQueues (Queue * allQueue[], Queue * intersectionQueue);

/**Updates waiting time of each car in the queue
*@param allQueue double pointer of queue N S E W
**/
void updateWaitingTime(Queue *allQueue[]);

/**Calculate and print maximum waiting time
*@param order pointer to a queue that has the order of the cars going through the intersection
**/
void reportMaxWaitingTime(Queue * order);

/**Calculate and print average waiting times
*@param order pointer to a queue that has the order of the cars going through the intersection
*@param allQueue double pointer of queue N S E W
**/
void reportAverageWaitingTime(Queue * order, Queue *allQueue[]);


#endif
