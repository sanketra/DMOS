/* Team Members: Chaitra Kulkarni, Sanket Radder
*  Defines the queue handler functions.
*/

#include "TCB.h"

/*initQ()
* Initialises the queue
*/
void initQ(TCB_t **runQ) {
	(*runQ) = '\0';
}

/*addQ()
* adds the tcb item into the queue
*/
void addQ(TCB_t **runQ, TCB_t *item) {
	if(*runQ == '\0') {
		printf("Run Queue is empty!! Adding first thread...\n");
		*runQ = item;
		(*runQ)->prev = item;
		(*runQ)->next = item;
	} else {
		printf("Adding thread %d to the run queue...\n", item->thread_id);
		TCB_t *temp = (*runQ)->prev;
		temp->next = item;
		item->prev = temp;
		item->next = (*runQ);
		(*runQ)->prev = item;
	}
	sleep(2);
}

/*delQ()
* deletes the tcb item from the queue
*/
TCB_t* delQ(TCB_t **runQ) {
	TCB_t *returnValue = '\0';

	if((*runQ) == '\0') {
		printf("Queue is empty...Nothing to delete\n");
		return returnValue;
	} else {
		returnValue = (*runQ);
		
		if((*runQ)->next==(*runQ)) {
			(*runQ) = '\0';
		} else {
			(*runQ)=(*runQ)->next;
			(*runQ)->prev = returnValue->prev;
			returnValue->prev->next = (*runQ);
		}
		
		returnValue->prev = '\0';
		returnValue->next = '\0';
		return returnValue;
	}
}

/*rotateQ()
* deletes the front item and adds it at the last
*/
void rotateQ(TCB_t **runQ) {
	printf("Rotating the Run Queue...\n");
	sleep(2);
	*runQ=(*runQ)->next;
	
	//Below code to rotate by deleting the first node and adding it at last.
	//TCB_t *temp = delQ(runQ);
	//addQ(runQ, temp);
}
