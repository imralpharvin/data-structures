/**
 * @file car.h
 * @author Ralph Arvin De Castro
 * @date June 2018
 * @brief File containing the function definitions needed for car struct
 */

#ifndef _CAR_
#define _CAR_

#include <stdio.h>
#include <stdlib.h>

/**
 *Car. It contains elements which are startPoint(from N S E or W) and endPoint(to R F or L) character and an arrival, waiting and intersection(what time they went to the intersection) time of the car.
 **/
typedef struct car
{
  char startPoint;
  char endPoint;
  double arriveTime;
  double waitingTime;
  double intersectionTime;
}Car;

/**Function to allocate memory to the car, set proper data to its members
*@return pointer to the car
*@param startPoint character N S E W or direction of where the car was coming from
*@param endPoint character R F L or direction of the car is going to
*@param arriveTime time that the car arrives in the queue
**/
Car *initializeCar(char startPoint, char endPoint, double arriveTime);

/**Gets the starting direction of the car
*@return character startPoint N S E W
*@param car pointer to a car struct
**/
char getstartPoint(Car *car);


/**Gets the end direction of the car
*@return character endPoint R F L
*@param car pointer to a car struct
**/
char getendPoint(Car *car);

/**Gets the arriveTime of the car
*@return arrival time of the car
*@param car pointer to a car struct
**/
double getarriveTime(Car *car);

/**Prints the elements of the car
*@param toBePrinted void pointer to be casted to a car type
**/
void printCar(void *toBePrinted);

/**Frees the car struct
*@param toBeDeleted void pointer to be casted to a car type
**/
void deleteCar(void *toBeDeleted);

/**Compares the arrival time of cars
*@return integer that determines the comparison of two cars
*@param first void pointer to be casted to an integer
*@param second void pointer to be casted to an integer
**/
int compareCars(const void *first,const void *second);

/**Parse file and put car data in a queue
*@param filename name of the file that has the data
*@param allCars pointer to a queue where all the car data will be enqueued
**/
void loadCars(char *filename, Queue *allCars);

#endif
