#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include "car.h"
#include "simulation.h"

void addCarToQueues(Queue * allQueue[], Queue * allCars)
{
  Car * carToQueue = deQueue(allCars);
  switch(getstartPoint(carToQueue))
  {
    case 'N':
      enQueue(allQueue[0], carToQueue);
      break;
    case 'E':
      enQueue(allQueue[1], carToQueue);
      break;
    case 'S':
      enQueue(allQueue[2], carToQueue);
      break;
    case 'W':
      enQueue(allQueue[3], carToQueue);
      break;
  }
}

void updateintersectionQueue (Queue * allQueue[], Queue * intersectionQueue, double waitTimer, char waitCar)
{
  int i;
  int numToUpdate = 0;
  int const N = 0;
  int const E = 1;
  int const S = 2;
  int const W = 3;
  int qtoUpdate[4];

  //Check if the front of the queues needs to be updated
  for(i = 0; i <= 3; i++)
  {
    if(allQueue[i]->front != NULL && (getstartPoint(allQueue[i]->front->data) != waitCar || waitTimer <= 0))
    {
      Node * tempFront = intersectionQueue->list->head;
      while(tempFront != NULL )
      {
        if(getstartPoint(tempFront->data) ==  getstartPoint(allQueue[i]->front->data))
        {
          break;
        }
        tempFront = tempFront->next;
      }
      if(tempFront == NULL)
      {
        qtoUpdate[numToUpdate] = i;
        numToUpdate += 1;
      }
    }
  }

  //Rules of right of ways if two cars come at the same time
  if(numToUpdate == 2)
  {
    if(qtoUpdate[0] == E && qtoUpdate[1] == N)
    {
      qtoUpdate[0] = N;
      qtoUpdate[1] = E;
    }
    if(qtoUpdate[0] == S && qtoUpdate[1] == E)
    {
      qtoUpdate[0] = E;
      qtoUpdate[1] = S;
    }
    if(qtoUpdate[0] == W && qtoUpdate[1] == S)
    {
      qtoUpdate[0] = S;
      qtoUpdate[1] = W;
    }
    if(qtoUpdate[0] == N && qtoUpdate[1] == W)
    {
      qtoUpdate[0] = W;
      qtoUpdate[1] = N;
    }
  }

  //Rules of right of ways if three cars come at the same time
  if(numToUpdate == 3)
  {
    if((qtoUpdate[0] == E || qtoUpdate[0] == N || qtoUpdate[0] == W) && (qtoUpdate[1] == E || qtoUpdate[1] == N || qtoUpdate[1] == W ) && (qtoUpdate[2] == E || qtoUpdate[2] == N || qtoUpdate[2] == W))
    {
      qtoUpdate[0] = W;
      qtoUpdate[1] = N;
      qtoUpdate[2] = E;
    }
    if((qtoUpdate[0] == S || qtoUpdate[0] == N || qtoUpdate[0] == W) && (qtoUpdate[1] == S || qtoUpdate[1] == N || qtoUpdate[1] == W ) && (qtoUpdate[2] == S || qtoUpdate[2] == N || qtoUpdate[2] == W))
    {
      qtoUpdate[0] = S;
      qtoUpdate[1] = W;
      qtoUpdate[2] = N;
    }
    if((qtoUpdate[0] == S || qtoUpdate[0] == E || qtoUpdate[0] == W) && (qtoUpdate[1] == S || qtoUpdate[1] == E || qtoUpdate[1] == W ) && (qtoUpdate[2] == S || qtoUpdate[2] == E || qtoUpdate[2] == W))
    {
      qtoUpdate[0] = E;
      qtoUpdate[1] = S;
      qtoUpdate[2] = W;
    }
    if((qtoUpdate[0] == S || qtoUpdate[0] == E || qtoUpdate[0] == N) && (qtoUpdate[1] == S || qtoUpdate[1] == E || qtoUpdate[1] == N ) && (qtoUpdate[2] == S || qtoUpdate[2] == E || qtoUpdate[2] == N))
    {
      qtoUpdate[0] = N;
      qtoUpdate[1] = E;
      qtoUpdate[2] = S;
    }
  }

  //Update the intersectionQueue
  for(i = 0; i < numToUpdate; i++)
  {
    if(allQueue[qtoUpdate[i]]->front != NULL && (getstartPoint(allQueue[qtoUpdate[i]]->front->data) != waitCar || waitTimer <= 0))
    {
      Node * tempFront = intersectionQueue->list->head;
      while(tempFront != NULL )
      {
        if(getstartPoint(tempFront->data) ==  getstartPoint(allQueue[qtoUpdate[i]]->front->data))
        {
          break;
        }
        tempFront = tempFront->next;
      }
      if(tempFront == NULL)
      {
        enQueue(intersectionQueue, allQueue[qtoUpdate[i]]->front->data);
      }
    }
  }
}

Car * removeCarFromQueues(Queue * allQueue[], Queue * intersectionQueue)
{
  if(intersectionQueue->front != NULL)
  {
    switch(getstartPoint(intersectionQueue->front->data))
    {
      case 'N':
        deQueue(allQueue[0]);
        break;
      case 'E':
        deQueue(allQueue[1]);
        break;
      case 'S':
        deQueue(allQueue[2]);
        break;
      case 'W':
        deQueue(allQueue[3]);
        break;
    }
    return deQueue(intersectionQueue);
  }
  return NULL;
}

void updateWaitingTime(Queue *allQueue[])
{
  int i = 0;
  for (i = 0; i <= 3; i++)
  {
    Node *tempNode =  allQueue[i]->front;
    while (tempNode != NULL)
    {
      ((Car*)tempNode->data)->waitingTime += 0.5;
      tempNode = tempNode->next;
    }
  }
}

void reportMaxWaitingTime(Queue * order)
{
  double maxWaitingTime = 0;
  Node *tempNode =  order->front;
  while (tempNode != NULL)
  {
    if(maxWaitingTime <= ((Car*)tempNode->data)->waitingTime)
    {
      maxWaitingTime = ((Car*)tempNode->data)->waitingTime;
    }
    tempNode = tempNode->next;
  }
  printf("\n***Max Waiting Time***\n");
  printf("The maximum waiting time from all cars: %lfs\n", maxWaitingTime);
}

void reportAverageWaitingTime(Queue * order, Queue *allQueue[])
{
  double avgWaitingTime = 0;
  double totalWaitingTime = 0;
  double length = (double)order->length;
  double eachavgwaitingTime[4];
  double eachtotalWaitingTime[4];
  double eachlength[4];
  int i;
  Node *tempNode =  order->front;

  //Calculate average waiting time
  while (tempNode != NULL)
  {
    totalWaitingTime += ((Car*)tempNode->data)->waitingTime;
    tempNode = tempNode->next;
  }
  avgWaitingTime = totalWaitingTime/length;
  printf("\n***Average Waiting Time***\n");
  printf("The average waiting time for all cars: %lfs\n", avgWaitingTime);

  //Calculate average waiting time for each queue
  Queue* tempQueue = order;
  while(tempQueue->front != NULL)
  {
    addCarToQueues(allQueue, tempQueue);
  }
  for(i = 0; i <= 3; i++)
  {
    if(allQueue[i]->front != NULL)
    {
      Node * tempFront = allQueue[i]->front;
      eachtotalWaitingTime[i] = 0;
      eachlength[i] = allQueue[i]->length;
      while (tempFront != NULL)
      {
        eachtotalWaitingTime[i] += ((Car*)tempFront->data)->waitingTime;
        tempFront = tempFront->next;
      }
      eachavgwaitingTime[i] = eachtotalWaitingTime[i]/eachlength[i];
      printf("The average waiting time for cars coming from %c direction: %lfs\n", getstartPoint(allQueue[i]->front->data), eachavgwaitingTime[i]);
    }
  }
}
