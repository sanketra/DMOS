/* Team Members: Chaitra Kulkarni, Sanket Radder
*  Read- Writer problem.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

Semaphore_t *r_sem, *w_sem, *mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0;
int global_ID=1;
void reader_entry(int ID)
{
	printf("\n[reader: #%d]\ttrying to read\n", ID);
	P(mutex);
	if (wwc > 0 || wc > 0) {
	    printf("[reader: #%d]\tblocking for writer\n", ID);
	    rwc++;		// increment waiting reader count.
	    V(mutex);		// let other processes use the mutex.
	    P(r_sem);		// sleep on r_sem
	    rwc--;		// program now has mutex and r_sem, go
			        // into CS.
	}
	rc++;
	if (rwc > 0)
	    V(r_sem);
	else
	    V(mutex);
}

void reader_exit(int ID)
{
	P(mutex);
	rc--;			printf("\n i'm no longer a reader\n");
	if (rc == 0 && wwc > 0) 
	{
	    V(w_sem);
	} else
	    V(mutex);

}

void writer_entry(int ID)
{
	printf("\t\t\t\t[writer: #%d]\ttrying to write\n", ID);
	P(mutex);
	if (rc > 0 || wc > 0) {
	    printf("\n\t\t\t\t[writer: #%d] blocking for others\n",ID);
	    wwc++;		// increment waiting writers
	    V(mutex);		// let go of the mutex, since i'll be
	    // blocked
	    P(w_sem); // wait in my line, when i wake up i DON'T 
		 // need a P(mutex since i've been given it 
	    			// by the waking process.
	    wwc--;		// i'm no longer waiting
	}
	wc++;			// increment writers
	V(mutex);		// let go of the mutex
}

void writer_exit(int ID)
{
	P(mutex);
	wc--;
	if (rwc > 0) {		// first, i let all the readers go.
	    V(r_sem);
	} else if (wwc > 0) {	// then i let another writer go
	    V(w_sem);
	} else {		// lastly, i give up the mutex
	    V(mutex);
	}
}



void reader(void)
{ 
  int ID;
  ID = global_ID++;
  while(1){
	reader_entry(ID);
	printf
	    ("\n[reader #%d]\t****READING****\n", ID);
	sleep(1);
	reader_exit(ID);
  };
}

void writer(void)
{
  int ID;
  ID = global_ID++;
  while(1){
 	writer_entry(ID);
	printf
	    ("\n\t\t\t\t[writer: #%d]\t&&&WRITING!&&&\n", ID);
	sleep(1);
	writer_exit(ID);
  };
}



//-------------------------------------------------------

int main()
{
    mutex=CreateSem(1);
    r_sem=CreateSem(0);
    w_sem=CreateSem(0);
	printf("\n creating a reader 1\n");
    start_thread(reader, NULL);
	printf("\n creating a reader 2\n");
    start_thread(reader, NULL);
	printf("\n creating a reader 3\n");	
    start_thread(reader, NULL);
	printf("\n creating a reader 4\n");
    start_thread(reader, NULL);
	printf("\n creating a writer 1\n");
    start_thread(writer, NULL);
	printf("\n creating a writer 2\n");
    start_thread(writer, NULL);
	run();
    while (1) sleep(1);
}   



	
