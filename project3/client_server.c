
#include "msgs.h"

void client()
{
while(1){
  P(p[99].empty);
  int a[10];
  int i=0;
  printf("\nClient 0: Sending \n");
  for(i=0;i<10;i++) { 
  a[i]=i;
  printf("%d\t", a[i]); 
  }
  printf("\n");

  send(&p[99], a);
  for(i=0;i<10;i++)
  printf("%d\t", p[99].msgs[p[99].in - 1][i]);
  printf("\n");
  printf("Client 0: Send success\n");
  sleep(5);
  V(p[99].full);
  //yield();
  P(p[0].full);
  int b[10];
  receive(&p[0],b);
  printf("Client 0: Receive \n");
  for(i=0;i<10;i++)
  printf("%d\t", b[i]);
  printf("\nClient 0: Receive success\n");
  sleep(10);
  V(p[0].empty);
  printf("*******************************************************************\n");
}
}

void client1()
{
while(1){
  P(p[99].empty);
  int a[10];
  int i=0;
  printf("\nClient 1: Sending \n");
  for(i=0;i<10;i++) { 
  a[i]=i+20;
  printf("%d\t", a[i]); 
  }
  printf("\n");

  send(&p[99], a);
  for(i=0;i<10;i++)
  printf("%d\t", p[99].msgs[p[99].in - 1][i]);
  printf("\n");
  printf("Client 1: Send success\n");
  sleep(5);
  V(p[99].full);
  //yield();
  P(p[20].full);
  int b[10];
  receive(&p[20],b);
  printf("Client 1: Receive \n");
  for(i=0;i<10;i++)
  printf("%d\t", b[i]);
  printf("\nClient 1: Receive success\n");
  sleep(10);
  V(p[20].empty);
  printf("*******************************************************************\n");
}
}

void server()
{
while(1){
  P(p[99].full);
  printf("Server: Receiving \n");
  int a[10];
  receive(&p[99],a);
  int i=0;
 
  for(i=0;i<10;i++)
  printf("%d\t", a[i]);
  printf("\nServer: Receive Success \n");
  sleep(5);
  V(p[99].empty);
  //yield();
  P(p[a[0]].empty);
  printf("Server: Sending \n");
  for(i=0;i<10;i++) {
  a[i]+=10;
  printf("%d\t", a[i]);
  }
  printf("\n");
  
  send(&p[a[0]], a);
  for(i=0;i<10;i++)
  printf("%d\t", p[a[0]].msgs[p[a[0]].in-1][i]);
  printf("\n");
  printf("Server: Send success");
  sleep(5);
  V(p[a[0]].full);
  //yield();
}
}


//-------------------------------------------------------

int main()
{   int a[] = {0,1,2,3,4};
   p[0].in=0; p[0].out=0;
   p[20].in=0; p[20].out=0;
   p[99].in=0; p[99].out=0;
    init_port();
	printf("\nCreating a client\n");
    start_thread(client, &a[0]);
	printf("\nCreating a client\n");
    start_thread(client1, &a[1]);
	printf("\nCreating a server\n");
    start_thread(server, NULL);
	run();
    while (1) sleep(1);
}   



	
