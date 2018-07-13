#ifndef _PATIENT_
#define _PATIENT_

#include <stdio.h>
#include <stdlib.h>

#include "priorityQueueADT.h"

typedef struct patient
{
  char clientID[64];
  int priority;
  char symptomCode[3];
  int arrivalTime;
  int waitingTime;
  int oldPriority;

}Patient;

void loadPatients(char *filename, PQueue * allPatients);
Patient *initializePatient(char clientID[], int priority, char symptomCode[]);
int hashFunction(int maxArrivalTime, char key[]);
void delete(void *toBeDeleted);
void printPatient(void *toBePrinted);
int compareArrivalTime(const void *first,const void *second);
int getWaitingTime(void * data);
int comparePriority(const void *first,const void *second);
int getArrivalTime(void * data);
void updateWaitingTime(PQueue * waitingPatients);



#endif
