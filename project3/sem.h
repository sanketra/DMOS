/* Team Members: Chaitra Kulkarni, Sanket Radder
*  Defines the semaphore handlers.
*/

#include "threads.h"

typedef struct Semaphore
{
int counter;
TCB_t *start;
}Semaphore_t;

Semaphore_t * CreateSem(int InputValue)
{
Semaphore_t *sem=(Semaphore_t *)malloc(sizeof(Semaphore_t));
sem->counter=InputValue;
sem->start=NULL;
return sem;
}

void P(Semaphore_t *sem)
{
TCB_t *temp;
sem->counter--;
if(sem->counter<0) 
{
printf("Blocking on P(sem)\n");
ucontext_t *current_context = &head->context;
temp=delQ(&head);
addQ(&(sem->start),temp);
swapcontext(current_context, &(head->context));
}
}

void V(Semaphore_t *sem)
{
TCB_t *temp;
sem->counter++;
if(sem->counter<=0)
{
printf("Unlocking on V(sem)\n");
temp=delQ(&(sem->start));
addQ(&head,temp);}
yield();
}






