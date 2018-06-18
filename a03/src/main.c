#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"heaphelper.h"

#include"heap.h"
#include"priorityQueueADT.h"

#include"emergency.h"




int main (int argc, char *argv[])
{

  PQueue * arrivingPatients = createPriorityQueue(5, 0, delete, printPatient, compareArrivalTime);
  PQueue * waitingPatients = createPriorityQueue(5, 0, delete, printPatient, comparePriority);

  loadPatients(argv[1], arrivingPatients);

  int counter = 0;
  int doctorTimer = 0;
  Patient * currentPatient = NULL;

  while(arrivingPatients->front != NULL || waitingPatients->front != NULL || doctorTimer != 0)
  {
    printf("[Counter Before: %d]\n", counter);
    while (arrivingPatients->front != NULL && counter == getArrivalTime(arrivingPatients->front->data))
    {
      Patient * arrivedPatient = getFront(arrivingPatients);

      printf("arrivedPatient: ");
      printPatient(arrivedPatient);
      deQueue(arrivingPatients);
      enQueue(waitingPatients, arrivedPatient);
    }
    printf("arrivingPatients: \n");
    printPriorityQueue(arrivingPatients);
    printf("waitingPatients: \n");
    printPriorityQueue(waitingPatients);



    if(doctorTimer <= 0 && waitingPatients->front != NULL)
    {
      Patient * currentPatient = getFront(waitingPatients);
      printf("currentPatient: ");
      printPatient(currentPatient);
      deQueue(waitingPatients);
      doctorTimer = 5;
    }

    counter ++;
    doctorTimer --;

    printf("Counter After: %d\n", counter);
    printPriorityQueue(waitingPatients);
    if(currentPatient != NULL)
    {
      printf("currentPatient: ");
      printPatient(currentPatient);
    }

  }

  printPriorityQueue(waitingPatients);

  /*while(arrivingPatients->front != NULL || currentPatient != NULL)
  {
    while (arrivingPatients->front != NULL && counter == getWaitingTime(arrivingPatients->front->data))
    {
      Patient * arrivedPatient = getFront(arrivingPatients);
      deQueue(arrivingPatients);
      enQueue(waitingPatients, arrivedPatient);

      counter ++;
    }

  }*/


  return 0;
}
