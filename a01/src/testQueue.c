#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "QueueADT.h"
#include "car.h"

void printCar2(void *toBePrinted)
{

  if(toBePrinted == NULL)
  {
    return;
  }
  char startPoint = ((Car*)toBePrinted)->startPoint;
  char endPoint = ((Car*)toBePrinted)->endPoint;
  double arriveTime = ((Car*)toBePrinted)->arriveTime;

  printf("%c %c %d\n",startPoint, endPoint, (int)arriveTime) ;
}

int main()
{

  Car * a = initializeCar('N', 'L', 2);
  Car * b = initializeCar('S', 'R', 3);
  Car * c = initializeCar('W', 'F', 5);

  printf("*** Test #1: initializeQueue ***\n");
  printf("Expected:\nThe list is empty\n");
  Queue *carQueue = initializeQueue(printCar2, deleteCar, compareCars);
  printf("Received:\n");
  printQueue(carQueue);
  printf("   ***PASS***   \n\n");

  printf("*** Test #2: enQueue ***\n");
  printf("Expected:\nN L 2\nS R 3\nW F 5\n");
  enQueue(carQueue, a);
  enQueue(carQueue, b);
  enQueue(carQueue, c);
  printf("Received:\n");
  printQueue(carQueue);
  printf("   ***PASS***   \n\n");

  printf("*** Test #3: deQueue ***\n");
  printf("Expected:\nS R 3\nW F 5\n");
  deQueue(carQueue);
  printf("Received:\n");
  printQueue(carQueue);
  printf("   ***PASS***   \n\n");


  printf("*** Test #4: peekQueue ***\n");
  printf("Expected:\nS R 3\n");
  printf("Received:\n");
  printCar2(peekQueue(carQueue));
  printf("   ***PASS***   \n\n");

  printf("*** Test #5: deleteQueue ***\n");
  printf("Expected:\nThe list is empty\n");
  deleteQueue(carQueue);
  printf("Received:\n");
  printQueue(carQueue);
  printf("   ***PASS***   \n\n");

  return 0;
}
