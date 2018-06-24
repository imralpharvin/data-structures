#include <stdio.h>
#include <string.h>
#include <math.h>



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

void updateWaitingTime(PQueue * waitingPatients)
{
  int j;

  for(j = 1; j <= waitingPatients->heap->size; j++)
  {
    if( j == 1)
    {
      Node * changeNode = waitingPatients->front;

      Patient * changePatient = (Patient*)changeNode->data;

      changePatient->waitingTime ++;


    }
    else
    {
      int heapLevel = 0;
      int heapLevelSum = 0;
      int heapBottom = 0;
      int i;
      int j1 = j -1;
      while(heapLevelSum + pow(2 , heapLevel) <= j1)
      {
        heapLevelSum = heapLevelSum + pow(2 , heapLevel);
        heapLevel++;
      }

      heapBottom = j1 - heapLevelSum;
      Node * changeNode = waitingPatients->front;

      int heapBottomSum = pow(2 , heapLevel);
      /*printf("Level: %d, Size: %d [%d + %d], Next:%d\n", heapLevel, j1, heapLevelSum, heapBottom ,heapBottomSum);*/
      int mid = heapBottomSum/2;

      for(i = 0; i < heapLevel; i++)
      {
        if(heapBottom < mid)
        {
          changeNode = changeNode->left;
        }
        else
        {
          changeNode = changeNode->right;
          heapBottom = heapBottom -mid;

        }
          mid = mid/2;
      }

      Patient * changePatient = (Patient*)changeNode->data;

      changePatient->waitingTime ++;
      if(changePatient->waitingTime == 10)
      {
        if(changePatient->priority > 1)
        {
          changePatient->priority --;
        }
        changePatient->waitingTime = 0;
      }
      heapifyUp(waitingPatients->heap, changeNode);

    }
  }
}
