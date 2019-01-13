#include <stdio.h>
#include <stdlib.h>

#include "LinkedListAPI.h"
#include "QueueADT.h"
#include "car.h"


Car *initializeCar(char startPoint, char endPoint, double arriveTime)
{
  Car *car = malloc(sizeof(Car));
  car->startPoint = startPoint;
  car->endPoint = endPoint;
  car->arriveTime = arriveTime;
  car->waitingTime = 0;
  car->intersectionTime = 0;

  return car;
}


char getstartPoint(Car *car)
{
	return car->startPoint;
}

char getendPoint(Car *car)
{
	return car->endPoint;
}


double getarriveTime(Car *car)
{
  if(car == NULL)
  {
    printf("NULL");
    return -1;
  }
	return car->arriveTime;

}

void printCar(void *toBePrinted)
{

  if(toBePrinted == NULL)
  {
    return;
  }
  char startPoint = ((Car*)toBePrinted)->startPoint;
  char endPoint = ((Car*)toBePrinted)->endPoint;
  double arriveTime = ((Car*)toBePrinted)->arriveTime;
  double waitingTime = ((Car*)toBePrinted)->waitingTime;
  double intersectionTime = ((Car*)toBePrinted)->intersectionTime;


  printf("   %c->%c           %.1lf            %.1lf            %.1lf\n",startPoint, endPoint, arriveTime, waitingTime, intersectionTime) ;
}


void deleteCar(void *toBeDeleted)
{
  free(toBeDeleted);
}

int compareCars(const void *first,const void *second)
{
  double a = ((Car*)first)->arriveTime;
  double b = ((Car*)second)->arriveTime;
  return a - b;
}


void loadCars(char *filename, Queue * allCars)
{
    FILE *fptr = NULL;
    char text[10];
  	char startPoint;
  	char endPoint;
  	double arriveTime = 0;
    List *carsSorted = initializeList(printCar, deleteCar, compareCars);

    fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
      printf("No file\n");
      exit(1);
    }
    while ( fgets ( text, 10, fptr ) )
    {
      sscanf(text, "%c %c %lf",&startPoint, &endPoint, &arriveTime);

      Car * tempCar = initializeCar(startPoint, endPoint, arriveTime);
      insertSorted(carsSorted, tempCar);


    }

    Node *tempNode = carsSorted->head;

    while(tempNode != NULL)
    {
      enQueue(allCars,tempNode->data);
      tempNode = tempNode->next;
    }

    if(allCars->length == 0)
    {
      printf("No cars in the list.\n");
      exit(1);
    }

    free(carsSorted);
    free(tempNode);
    fclose(fptr);
}
