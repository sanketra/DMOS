/* Team Members: Chaitra Kulkarni, Sanket Radder
*  Defines the thread functions, adds to the queue and start the first thread
*/

#include<stdio.h>
#include "threads.h"

int global_var = 0;

void function1() {
	int local_var = 10;

	printf("\n\n");

	while(1) {
		printf("Executing inside function 1\n");
		printf("Local variable inside function 1 has value: %d\n", local_var);
		printf("Global variable after increment inside function 1: %d\n", ++global_var);
		yield();
		printf("\n\n***** Returned to function 1 *****\n");	
	}
}

void function2() {
	int local_var = 20;
	
	printf("\n\n");

	while(1) {
		printf("Executing inside function 2\n");
		printf("Local variable inside function 2 has value: %d\n", local_var);
		printf("Global variable after increment inside function 2: %d\n", ++global_var);
		yield();
		printf("\n\n***** Returned to function 2 *****\n");	
	}
}

void function3() {
	int local_var = 30;

	printf("\n\n");

	while(1) {
		printf("Executing inside function 3\n");
		printf("Local variable inside function 3 has value:%d\n", local_var);
		printf("Global variable after increment inside function 3: %d\n", ++global_var);
		yield();
		printf("\n\n***** Returned to function 3 *****\n");	
	}
}

int main() {
	printf("\n");
	initQ(&head);
	start_thread(&function1);	//Initialize and add the threads to queue.
	start_thread(&function2);
	start_thread(&function3);
	run();				//Start the first thread and never return.
	return 0;
}


