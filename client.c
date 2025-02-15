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

void send_char(int pidval, char c)
{
    int i;

    i = 0;
    while(i < 8)
    {
        if ((c >> i) & 1)
            kill(pidval, SIGUSR1);
        else
            kill(pidval, SIGUSR2);
        usleep(500);
        i++;
    }
}   

void send_string(int pidval, const char *message)
{
    int i;

    i = 0;
    while(message[i] != '\0')
    {
        send_char(pidval, message[i]);
        i++;
    }
    send_char(pidval, '\0');
}


int main(int argc, char *argv[])
{
    int pidval;

    if (argc != 3)
    {
        printf("Usage: %s <PID> <message>\n", argv[0]);
        return 1;
    }

    pidval = ft_atoi(argv[1]);
    char *message = argv[2];

    send_string(pidval, message);
    //kill(pidval, SIGINT);
}