#include<sys/type.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MSGKEY 75
struct msgform
{
      long mtype;
      char mtext[1024];
}msg;
int msgqid,pid,*pint;
int client()
{
	msgqid=msgget( MSGKEY,0777);
	pid=getpid();
	pint=(int*)msg.mtext;
	*pint=pid;
	msg.mtype=1;
	msgsnd(msgqid,&msg,sizeof(pint),0);
	msgrcv(msgqid,&msg,1030,pid,0);
	printf("client : receive from pid%d\n",*pint);
}
int server()
{
	int i;
	extern cleanup();
//	for(i=1;i<20;i++)
//		signal(i,cleanup);
	msgqid=msgget(MSGKEY,0777|IPC_CREAT);
	for(;;)
	 {
	  msgrcv (msgqid,&msg,256,1,0);
	  pint=(int*)msg.mtext;
	  pid=*pint;
	  printf("server : receive from pid%d\n",pid);
	  msg.mtype=pid;
	  *pint=getpid();
	  msgsnd(msgqid,&msg,sizeof(pint),0);
	 }
	}
	
}
cleanup()
{
	msgct1(msgqid,IPC_RMID,0);
	exit();
}
main()
{
	if(fork()){
		server();
	}else{
		client();
	}
	wait(0);
}
