#include "index.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/poll.h>
#include "server/requestHandler.h"
#include "server/session.h"
#define MAX_CLIENT 30
void signalHandler(int signum);
void error(char *msg);
int connectHandler(int sockfd);

int main(int argc, char const *argv[])
{
    int parentfd = initConnectionServer(5500);
    int childfd = -1;
    int clientLen;
    struct sockaddr_in clientaddr; /* client addr */
    struct pollfd fds[MAX_CLIENT];
    for (int i = 0; i < MAX_CLIENT; i++)
    {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    fds[0].fd = parentfd;
    int pollval;
    while (true)
    {
        clientLen = sizeof(struct sockaddr_in);
        pollval = poll(fds, MAX_CLIENT, 3500);
        if (pollval == -1)
        {
            perror("\nError polling: ");
            exit(1);
        }
        if (pollval == 0)
        {
            printf("\nTimeout occurred!  No data after 3.5 seconds.\n");
            continue;
        }
        if (fds[0].revents & POLLIN)
        {
            childfd = accept(parentfd, (struct sockaddr *)&clientaddr, &clientLen);
            if (childfd == -1)
            {
                perror("\nError accepting: ");
                exit(1);
            }
            printf("\nNew connection from %s:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
            for (int i = 1; i < MAX_CLIENT; i++)
            {
                if (fds[i].fd == -1)
                {
                    fds[i].fd = childfd;
                    break;
                }
            }
        }
        for (int i = 1; i < MAX_CLIENT; i++)
        {
            if (fds[i].fd == -1)
                continue;
            if (fds[i].revents & POLLIN)
            {
                fds[i].fd = connectHandler(fds[i].fd);
            }
        }
    }
    close(parentfd);

    return 0;
}
void signalHandler(int signo)
{
    pid_t pid;
    int stat;
    /* Wait the child process terminate */
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("\nChild %d terminated\n", pid);
}
void error(char *msg)
{
    perror(msg);
    exit(1);
}
int connectHandler(int sockfd)
{
    int bytes;
    Req req;
    bytes = recvRequest(sockfd, &req);
    if (bytes <= 0)
    {
        closeConnection(sockfd);
        closeSession(getSessionBySockfd(sockfd));
        return -1;
    }
    switch (req.type)
    {
    case LOGIN_REQ:
        printf("Login request\n");
        loginHandler(sockfd, req);
        /* code */
        break;
    case SIGNUP_REQ:
        printf("Signup request\n");
        signupHandler(sockfd, req);
        /* code */
        break;
    case ACTIVE_REQ:
        printf("Active request\n");
        activeHandler(sockfd, req);
        /* code */
        break;
    case PLAY_REQ:
        /* code */
        break;
    case START_GAME_REQ:
        /* code */
        break;
    case CHAT_REQ:

        break;
    case CREATE_ROOM_REQ:

        break;
    case FIND_ROOM_REQ:

        break;
    case JOIN_ROOM_REQ:

        break;
    case LEAVE_ROOM_REQ:

        break;
    default:
        break;
    }
    return sockfd;
}