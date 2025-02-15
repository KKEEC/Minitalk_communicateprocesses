#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

typedef struct s_server_state 
{
    char *message;
    int bitcount;
    char current_char;
} t_server_state;

t_server_state serverdata;

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while(str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void    ft_putnbr(int nbr)
{
    char *str = "0123456789";
    if (nbr >= 10)
        ft_putnbr(nbr / 10);
    write(1, &str[nbr % 10], 1);
}

size_t ft_strlen(char *str)
{
    int i;
    i = 0;
    while(str[i])
        i++;
    return i;
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
        unsigned char   *dst1;
        unsigned char   *src1;
        size_t                  i;

        dst1 = (unsigned char *)dest;
        src1 = (unsigned char *)src;
        if (!dest || !src)
                return (NULL);
        i = 0;
        while (i < n)
        {
                dst1[i] = src1[i];
                i++;
        }
        return (dest);
}

void *ft_realloc(void *ptr, size_t new_size)
{
    void    *result;
    size_t  oldsize;
    size_t  copysize;
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    if (!ptr)
    {
        result = malloc(new_size);
        if (!result)
            return NULL;
        return result;
    }
    oldsize = ft_strlen((char *)ptr) + 1;
    if (oldsize < new_size)
        copysize = oldsize;
    else
        copysize = new_size;
    result = malloc(new_size);
    if (!result)
        return NULL; 
    ft_memcpy(result, ptr, copysize);
    free (ptr);
    return result;
}

void handle_signal(int sig)
{
    //ft_putstr("Signal received!");
    
    if (sig == SIGUSR1)
        serverdata.current_char |= (1 << serverdata.bitcount);  
    if (sig == SIGUSR2)
        serverdata.current_char &= ~(1 << serverdata.bitcount);


    serverdata.bitcount++;

    //ft_putstr("Bitcount: ");
    //ft_putnbr(serverdata.bitcount);
    //write(1, "\n", 1);

    if (serverdata.bitcount == 8)
    {
        //ft_putstr("Character completed!");

        if (serverdata.current_char == '\0')
        {
            //ft_putstr("Message received: ");
            ft_putstr(serverdata.message);
            free(serverdata.message);
            
            serverdata.message = (char *)malloc(1);
            if (!serverdata.message)
                return;  // Ensure no invalid memory access

            serverdata.message[0] = '\0';
        }
        else 
        {
            size_t len = ft_strlen(serverdata.message);
            serverdata.message = ft_realloc(serverdata.message, len + 2);
            if (!serverdata.message)
                return;

            serverdata.message[len] = serverdata.current_char;
            serverdata.message[len + 1] = '\0';

            //write(1, "Received character: ", 20);
            //write(1, &serverdata.current_char, 1);
            //write(1, "\n", 1);

            //ft_putstr("Current stored message: ");
            //ft_putstr(serverdata.message);
        }
        
        serverdata.bitcount = 0;
        serverdata.current_char = 0;
    }
}


int main()
{
    pid_t pid = getpid();
    struct sigaction sa;

    serverdata.message = (char *)malloc(1);
    if (!serverdata.message)
        return (1);
    serverdata.message[0] = '\0';
    serverdata.bitcount = 0;
    serverdata.current_char = 0; 

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_signal;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    ft_putnbr(pid);
    write(1, "\n", 1);
    while(1)
    {
        //ft_putstr("Waiting for signals...");
        pause();
        
    }
}