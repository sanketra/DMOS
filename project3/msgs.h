#include "sem.h"

typedef struct port 
{
	int msgs[10][10];
	int in, out;
	Semaphore_t *mutex, *full, *empty;
}PORT;

PORT p[100];


void init_port() 
{
	int i=0;
	for(i=0;i<100;i++)
	{
		p[i].mutex=CreateSem(1);
		p[i].full=CreateSem(0);
		p[i].empty=CreateSem(10);
	}
}
	

void send(PORT *p, int *msg)
{
    P(p->mutex);
	int i=0;
    	
  	for(i=0;i<10;i++)
	{
		p->msgs[p->in][i] = msg[i];
    }

  	printf("Message sent to port P at index: %d\n",p->in);
	p->in = ((p->in)+1)%10;
    V(p->mutex);
}

void receive(PORT *p, int *msg)
{
    P(p->mutex);
	int i=0;
    //if(p->in==p->out)
  
	for(i=0;i<10;i++)
  	{
  		msg[i]=p->msgs[p->out][i];
  	}

  	printf("Message read from port P at index: %d\n",p->out);
  	p->out = ((p->out)+1)%10;
    V(p->mutex);
}
