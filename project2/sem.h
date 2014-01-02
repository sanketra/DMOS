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
return sem;
}

void P(Semaphore_t *sem)
{
TCB_t *temp;
sem->counter--;
if(sem->counter<0) 
{
temp=delQ(&head);
ucontext_t *current_context = &head->context;
swapcontext(current_context, &(head->context));
addQ(&(sem->start),temp);
}
}

void V(Semaphore_t *sem)
{
TCB_t *temp;
sem->counter++;
if(sem->counter<=0)
{
temp=delQ(&(sem->start));
addQ(&head,temp);}
yield();
}






