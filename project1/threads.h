/* Team Members: Chaitra Kulkarni, Sanket Radder
*  Defines the thread handlers.
*/

#include "q.h"

TCB_t *head = '\0';
static int thread_count = 1;

/*start_thread(*fn)
* Creates a TCB_t and a stack
* initialises the TCB_t and adds to the run queue.
*/
void start_thread(void *func) {
	TCB_t *myTCB = (TCB_t *)malloc(sizeof(TCB_t));
	void *stackPtr = (void *) malloc(8192);

	init_TCB(myTCB, func, stackPtr, 8192);
	myTCB->thread_id = thread_count;
	thread_count++;
	addQ(&head, myTCB);
}
 
/*run()
* starts the first thread
*/
void run() {
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(head->context));
}

/*yield()
* swap the context and run the next thread in the run queue.
*/
void yield() {
	ucontext_t *current_context = &head->context;
	printf("Thread: %d calls yield function\n",head->thread_id);
	rotateQ(&head);
	swapcontext(current_context, &(head->context));
}
