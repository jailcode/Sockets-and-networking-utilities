#include "../includes/header.h"


# ifndef BUFFER_SIZE
# define BUFFER_SIZE 255
# endif
// format: ip, port, message
int main(int argc, char **argv)
{
    int clientfd;
    char *message;
    char *ip;
    int serverport;
    struct sockaddr_in server_addr;
    int domain;

    if (argc != 4)
        return (0);
    serverport = atoi(argv[2]);
    message = argv[3];
    ip = argv[1];
    domain = AF_INET;
    serverport = 5001;

    if ((clientfd = socket(domain, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        return 1;
    }
    bzero (&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverport);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
        perror(" nuh uh on inet_pton");
        return (1);
    }

    if (connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("nuh uh on connect");
        return (1);
    }
    write(clientfd, message, strlen(message));
    return (0);
}