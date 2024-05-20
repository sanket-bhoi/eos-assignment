#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY  0x1118


struct msg {
	
	long type ;
	int r;

}m2;
struct mesg {
		long type;
		int x1,x2;

}m1;

int main () {
	int mqid ,ret,s;

// create message queue 

	mqid=msgget(MQ_KEY,IPC_CREAT | 0600);
	if (mqid < 0) {
		perror("msgget() failed ");
		_exit(1);
	}

	ret=fork();
	if(ret ==0 ){
		
		//mesg_t m1;
		//msg_t m2;
//		m1.type =1;
		m2.type = 11;

		printf("Enter the two number :");
		scanf("%d%d",&m1.x1,&m1.x2);
		ret =msgsnd(mqid,&m1, 2*sizeof(m1.x1),0);
		//ret=msgsnd(mqid,&m1,sizeof(m1.x1),0);		
		printf("child sent : %d %d\n",m1.x1, m1.x2);
		//sleep(1);
		ret=msgrcv(mqid,&m2,sizeof(m2.r),11,0);
		printf("child sum: %d\n",m2.r);
//		ret=msgrcv(mqid,&n1,sizeof(n1.data),1,0);
		_exit(0);

	}

	else {
		
		//msg_t m2;
		//mesg_t m1;
		 m1.type = 1;
//		 m2.type = 11;
		printf("reciver wating for msg :\n");

		ret=msgrcv(mqid,&m1,2*sizeof(m1.x1),1,0);
		printf("Parent received values: %d %d\n", m1.x1, m1.x2);
	
		printf("Msg recievd !\n");
		printf("m1.type= %d, m2.type=%d\n", m1.type, m2.type);

   		m2.r = m1.x1+m1.x2;
		 ret = msgsnd(mqid,&m2,sizeof(m2.r),0);

		printf("Parent sent: %d\n",ret);
//		printf("parent  msg send to child :%d... %d %d \n",ret,n1.data,n2.data);

		wait(&s);
		msgctl(mqid, IPC_RMID, NULL);
}


return 0 ;
}
