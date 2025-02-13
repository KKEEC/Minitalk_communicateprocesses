#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = getpid();
    
    while(1)
    {
        usleep(10000);
        printf("PID of server is %d\n", pid);
    }
}