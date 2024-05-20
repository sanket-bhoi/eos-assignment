#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(void){
	
	int fd1,fd2;
	int n1,n2,sum;

	printf("Enter the two numbers :");
	scanf("%d %d",&n1,&n2);

	fd1 = open("/tmp/desd_fifo",O_WRONLY);
	if(fd1<0)
	{
		perror("open() failed");
		_exit(1);
	}
	write(fd1, &n1, sizeof(n1));
    write(fd1, &n2, sizeof(n2));
    close(fd1);
	
	fd2 = open("/tmp/desd_fifo",O_WRONLY);
	if(fd2<0){
		perror("output failed");
		_exit(2);
	}

	read(fd2,&sum,sizeof(sum));
	close(fd2);

	printf("The sum is %d\n",sum);

	return 0;

}

