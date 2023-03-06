#ifndef CONNECT_H_
#define CONNECT_H_
#include <stdio.h>
#include "index.h"
int parentfd = -1; /* parent socket */
int clientfd = -1; /* child socket */
// void test()
// {
//     sizeof(Req);
//     sizeof(ReqT);
//     sizeof(Res);
//     sizeof(CLUB);
//     sizeof(ReqD);
//     Req req;
//     sizeof(req.data.play.cards);
// }

/// @brief Create a new socket for server
/// @param PORT int
/// @return  a file descriptor for the new socket, or -1 for errors.
int initConnectionServer(const int PORT);
/// @brief Create a new socket for client
/// @param HOST const char *
/// @param PORT int
/// @return  a file descriptor for the new socket, or -1 for errors.
int initConnectionClient(const char *HOST, const int PORT);

/// @brief Close a connection
/// @param fd file descriptor
void closeConnection(int fd);

int initConnectionServer(const int PORT)
{
    // int parentfd;                  /* parent socket */
    struct sockaddr_in serveraddr; /* server's addr */
    parentfd = socket(AF_INET, SOCK_STREAM, 0);
    if (parentfd < 0)
    {
        perror("ERROR opening socket");
        return -1;
    }
    /* build the server's Internet address */
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)PORT);
    /* bind: associate the parent socket with a port */
    if (bind(parentfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("ERROR on binding");
        return -1;
    }
    /* listen: make this socket ready to accept connection requests */
    if (listen(parentfd, 5) < 0)
    { /* allow 5 requests to queue up */
        perror("ERROR on listen");
        return -1;
    }
    return parentfd;
}
int initConnectionClient(const char *HOST, const int PORT)
{
    // int clientfd;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    /* socket: create the socket */
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
        // return -1;
    }
    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(HOST);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host as %s", HOST);
        exit(1);
        // return -1;
    }
    /* build the server's Internet address */
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(PORT);
    /* connect: create a connection with the server */
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("ERROR connecting");
        exit(1);
        // return -1;
    }
    return clientfd;
}
void closeConnection(int fd)
{
    close(fd);
}
#endif // CONNECT_H_