#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int ft_atoi(char *str)
{
    int i;
    int result;

    i = 0;
    result = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    while(str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0';
        i++;
    }
    return (result);
}
void sigusr(int pid, char *message)
{
    printf("%s \n", message);
    kill(pid, SIGUSR1);
}

int main(int argc, char *argv[])
{
    int pidval;
    pidval = ft_atoi(argv[1]);
    char *message = argv[2];
    printf("value of pid is %d\n", pidval);
    sigusr(pidval, message);
}