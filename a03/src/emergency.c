#include <stdio.h>
#include <string.h>


#include "heaphelper.h"
#include "heap.h"
#include "priorityQueueADT.h"
#include "emergency.h"

void loadPatients(char *filename, PQueue * allPatients)
{
    FILE *fptr = NULL;
    char text[20];
    char clientID[64] ;
    int priority;
    char symptomCode[3];

    fptr = fopen(filename, "r");
    while ( fgets ( text, 20, fptr ) )
    {
      sscanf(text, "%s %d %s",clientID, &priority, symptomCode);
      Patient *temp = initializePatient(clientID, priority, symptomCode);

      enQueue(allPatients, temp);

    }
}

Patient *initializePatient(char clientID[], int priority, char symptomCode[])
{
  Patient *patient = malloc(sizeof(Patient));
  strcpy(patient->clientID , clientID);
  patient->priority = priority;
  strcpy(patient->symptomCode , symptomCode);
  patient->arrivalTime = hashFunction(20, clientID);
  patient->waitingTime = 0;

  return patient;
}


void printPatient(void *toBePrinted)
{
  Patient * temp = (Patient *) toBePrinted;

  printf("%s %d %s %d %d\n", temp->clientID, temp->priority, temp->symptomCode, temp->arrivalTime, temp->waitingTime);

}
int compareArrivalTime(const void *first,const void *second)
{
  int a = (int)((Patient*)first)->arrivalTime;
  int b = (int)((Patient*)second)->arrivalTime;
  return a - b;
}

int comparePriority(const void *first,const void *second)
{
  int a = (int)((Patient*)first)->priority;
  int b = (int)((Patient*)second)->priority;
  return a - b;
}

void delete(void *toBeDeleted)
{
  free(toBeDeleted);
}

int hashFunction(int maxArrivalTime, char key[]) {

	int index = 0;
	int letter;
	int i;
	int total = 0;

	letter = strlen(key);
	for(i = 0; i < letter; i++)
	{
		int temp = key[i] - '0';
		total += temp;

	}
	index = total  % maxArrivalTime;

	return index;
}

int getWaitingTime(void * data)
{
  Patient * temp = (Patient*)data;

  return temp->waitingTime;
}

int getArrivalTime(void * data)
{
  Patient * temp = (Patient*)data;

  return temp->arrivalTime;
}
