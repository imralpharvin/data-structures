#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include "car.h"
#include "simulation.h"

int main(int argc, char *argv[])
{
  //Initialize a queue for each direction
  Queue *N = initializeQueue(printCar, deleteCar, compareCars);
  Queue *E = initializeQueue(printCar, deleteCar, compareCars);
  Queue *S = initializeQueue(printCar, deleteCar, compareCars);
  Queue *W = initializeQueue(printCar, deleteCar, compareCars);
  Queue *allQueue[4];
  allQueue[0] = N;
  allQueue[1] = E;
  allQueue[2] = S;
  allQueue[3] = W;

  //Initialize a queue and load cars from sample input
  if(argc < 2)
  {
    printf("Error: No filename specified!\n");
    return 0;
  }
  Queue *allCars = initializeQueue(printCar, deleteCar, compareCars);
  loadCars(argv[1], allCars);

  //Initialize a queue for intersectionQueue that determines which will be used to determine who has the right of way and a queue for cars who left the intersection
  Queue *intersectionQueue = initializeQueue(printCar, deleteCar, compareCars);
  Queue *order = initializeQueue(printCar, deleteCar, compareCars);
  double counter = 1;
  double intersectionTimer = 0;
  Car * intersectionCar = NULL;
  double waitTimer = 0;
  char waitCar = 'X';

  //Simulation
  while((allCars->front != NULL || intersectionCar != NULL || intersectionQueue->front !=NULL || N->front != NULL || W->front != NULL || E->front != NULL || S->front != NULL))
  {
    //Enqueue to their respective queue when they arrive
    while (allCars->front != NULL && counter == getarriveTime(allCars->front->data))
    {
      addCarToQueues(allQueue , allCars);
    }

    //Enqueue to the intersectionQueue or waitlist of cars going through the intersection
    updateintersectionQueue(allQueue, intersectionQueue, waitTimer, waitCar);

    //Dequeue from intersectionQueue and go to intersection
    if(intersectionTimer <= 0)
    {
      intersectionCar = removeCarFromQueues(allQueue, intersectionQueue);
      if(intersectionCar != NULL)
      {
        intersectionCar->intersectionTime = counter;
        enQueue(order, intersectionCar);
        waitTimer = 1.0;
        waitCar = getstartPoint(intersectionCar);
        switch(getendPoint(intersectionCar))
        {
          case 'L':
            intersectionTimer = 3.5;
            break;
          case 'R':
            intersectionTimer = 1.5;
            break;
          case 'F':
            intersectionTimer = 2;
            break;
        }
      }
    }
    //Update counter and timers
    counter += 0.5;
    intersectionTimer -= 0.5;
    waitTimer -= 0.5;
    updateWaitingTime(allQueue);
  }
  //Report necessary information from assignment
  printf("\n***** Four-Way Stop Simulation *****\n");
  printf("\n***Order of cars going through the intersection***\n");
  printf("Directions | Arriving Time | Waiting Time | End Time\n");
  printQueue(order);
  reportMaxWaitingTime(order);
  reportAverageWaitingTime(order, allQueue);

  //Delete Queues initialized
  deleteQueue(N);
  deleteQueue(S);
  deleteQueue(E);
  deleteQueue(W);
  deleteQueue(allCars);
  deleteQueue(intersectionQueue);
  deleteQueue(order);
  return 0;
}
