#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd1, fd2;
    int n1, n2, sum;
//	int FIFO1,FIFO2;
char * FIFO1 = "/tmp/desd_fifo";

char * FIFO2 = "/tmp/desd_fifo";
    // Create the FIFO (named pipes)
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Open the first FIFO for reading
   fd1 = open("/tmp/desd_fifo",O_RDONLY);
    if (fd1 < 0) {
        perror("open FIFO1");
        _exit(1);
    }

	read(fd1,&n1,sizeof(n1));
	read(fd1,&n2,sizeof(n2));
	close(fd1);


	sum = n1+n2;

	fd2 = open("/tmp/desd_fifo2",O_WRONLY);

	if(fd2<0){
		perror("OUTPUT FAILED");
		_exit(2);
	}

	write(fd2,&sum,sizeof(sum));
	close(fd2);

	return 0;
	}
