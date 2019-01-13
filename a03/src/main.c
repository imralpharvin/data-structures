#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

  printf("Emergency Clinic\n");
  while(arrivingPatients->front != NULL || waitingPatients->front != NULL || doctorTimer != 0)
  {
    while (arrivingPatients->front != NULL && counter == getArrivalTime(arrivingPatients->front->data))
    {
      Patient * arrivedPatient = getFront(arrivingPatients);


      deQueue(arrivingPatients);
      enQueue(waitingPatients, arrivedPatient);
    }



    Patient * currentPatient;

    if(doctorTimer <= 0 && waitingPatients->front != NULL)
    {
      printf("%3d: ", counter);
      currentPatient = getFront(waitingPatients);
      printPatient(currentPatient);
      deQueue(waitingPatients);

      if(strcmp(currentPatient->symptomCode, "CV" ) == 0)
      {
        doctorTimer = 5;
      }

      else if(strcmp(currentPatient->symptomCode, "HN" ) == 0)
      {
        doctorTimer = 6;
      }

      else if(strcmp(currentPatient->symptomCode, "EV" ) == 0)
      {
        doctorTimer = 7;
      }

      else if(strcmp(currentPatient->symptomCode, "GI" ) == 0)
      {
        doctorTimer = 8;
      }

      else if(strcmp(currentPatient->symptomCode, "MH" ) == 0)
      {
        doctorTimer = 9;
      }

      else if(strcmp(currentPatient->symptomCode, "NC" ) == 0)
      {
        doctorTimer = 10;
      }

      else if(strcmp(currentPatient->symptomCode, "EC" ) == 0)
      {
        doctorTimer = 11;
      }

      else if(strcmp(currentPatient->symptomCode, "RC" ) == 0)
      {
        doctorTimer = 12;
      }

      else if(strcmp(currentPatient->symptomCode, "SK" ) == 0)
      {
        doctorTimer = 13;
      }

      else if(strcmp(currentPatient->symptomCode, "SA" ) == 0)
      {
        doctorTimer = 14;
      }

      else if(strcmp(currentPatient->symptomCode, "TR" ) == 0)
      {
        doctorTimer = 15;
      }

    }

    counter ++;
    doctorTimer --;
    updateWaitingTime(waitingPatients);


  }

/********************************************ADDITION**********************************************/

  loadPatients(argv[1], arrivingPatients);

  return 0;
}
