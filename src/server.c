#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 320
#endif
/*
struct in_addr{
    unsigned long s_addr;
};*/
/*
struct sockaddr_in{
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};*/

int main(int argc, char **argv)
{
    int serverfd, clientfd;
    int domain;
    struct sockaddr_in my_addr, cli_addr;
    int portno;
    int clilen;
    char buffer[BUFFER_SIZE + 1];
    domain = AF_INET; // IPV4
    portno = 5001;
    if ((serverfd = socket(domain, SOCK_STREAM, 0)) < 0)
    {
        printf("socket() call failed\n");
        return (1);
    }
    bzero (&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET ;// must match with domain
    my_addr.sin_port = htons(portno);

    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serverfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) < 0)
    {
        printf("binding error\n");
        exit(1);
    }
    while(1){
        listen(serverfd, BUFFER_SIZE);
        clilen = sizeof(cli_addr);
        clientfd = accept(serverfd, (struct sockaddr *)&cli_addr, &clilen);
        if (clientfd < 0)
        {
            perror("nuh uh on accept\n");
            exit(1);
        }
        bzero(buffer, BUFFER_SIZE); // ig buffer size is like the packet size here
        read(clientfd, buffer, BUFFER_SIZE);
        printf("client says: %s\n", buffer);
        write(clientfd, "message received\n", 17);
    }

    return (0);
}
