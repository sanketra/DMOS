/* Team Members: Chaitra Kulkarni, Sanket Radder
*  Defines the function to initialise a thread control block
*/

#include <ucontext.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TCB {			    // Thread control block.
	struct TCB *prev;
	struct TCB *next;
	ucontext_t context;
	int thread_id;			    // Added to keep track of threads created.
}TCB_t;

// arguments to init_TCB are
//   1. pointer to the function, to be executed
//   2. pointer to the thread stack
//   3. size of the stack
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
	static int counter=1;
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, tcb->thread_id);// context is now cooked
}
