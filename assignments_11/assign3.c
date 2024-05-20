#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int);
int main() {		
    int ret, arr[2];
    char ch = 'A';

    // Create the pipe
    ret = pipe(arr);
    if (ret < 0) {
        perror("pipe");
        return 1;
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sigaction(SIGINT, &sa, NULL);

    int count = 0;

    while(1) {
        write(arr[1], &ch, 1);
        count++;
        printf("bytes written: %d\n", count);
    }
    void sigint_handler(int sig){
    printf("SIGINT caught: %d\n", sig);
    close(arr[1]);
    close(arr[0]);
    _exit(0);
}


    return 0;
}

