#if !defined(SESSION_H_)
#define SESSION_H_
#include "user.h"

typedef struct _Session
{
    char username[127];
    int sockfd;
} *Session;
Dllist sessions = NULL;
Session initSession(char *username, int sockfd);
void freeSession(Session session);
void closeSession(Session session);
void freeSessions();
Session getSessionBySockfd(int sockfd);
Session getSessionByUser(char *username);
char *getUserBySockfd(int sockfd);
int getSocketByUser(char *username);
bool isUserOnline(char *username);

Session initSession(char *username, int sockfd)
{
    if (!sessions)
    {
        sessions = new_dllist();
    }
    Session session = (Session)malloc(sizeof(struct _Session));
    strcpy(session->username, username);
    session->sockfd = sockfd;
    dll_append(sessions, new_jval_v(session));
    printf("User %s online\n", username);
    exportSessions();

    return session;
}
void freeSession(Session session)
{
    free(session);
}
void closeSession(Session session)
{
    if (!session)
    {
        return;
    }

    Dllist ptr;
    dll_traverse(ptr, sessions)
    {
        Session temp = (Session)jval_v(ptr->val);
        if (temp == session)
        {
            printf("User %s has been logged out\n", session->username);
            dll_delete_node(ptr);
            break;
        }
    }
    freeSession(session);
    exportSessions();
}
void freeSessions()
{
    Dllist ptr;
    dll_traverse(ptr, sessions)
    {
        freeSession((Session)jval_v(ptr->val));
    }
    free_dllist(sessions);
}

Session getSessionBySockfd(int sockfd)
{
    if (!sessions)
    {
        return NULL;
    }
    Dllist ptr;
    dll_traverse(ptr, sessions)
    {
        Session session = (Session)jval_v(ptr->val);
        if (session->sockfd == sockfd)
        {
            return session;
        }
    }
    return NULL;
}

Session getSessionByUser(char *username)
{
    Dllist ptr;
    dll_traverse(ptr, sessions)
    {
        Session session = (Session)jval_v(ptr->val);
        if (strcmp(session->username, username) == 0)
        {
            return session;
        }
    }
    return NULL;
}

char *getUserBySockfd(int sockfd)
{
    Session session = getSessionBySockfd(sockfd);
    if (session == NULL)
    {
        return NULL;
    }
    return session->username;
}

int getSocketByUser(char *username)
{
    Session session = getSessionByUser(username);
    if (session == NULL)
    {
        return -1;
    }
    return session->sockfd;
}

bool isUserOnline(char *username)
{
    return getSessionByUser(username) != NULL;
}

/*For test*/

void exportSessions()
{
    FILE *fp = fopen("session.txt", "w+");
    Dllist ptr;
    dll_traverse(ptr, sessions)
    {
        Session session = (Session)jval_v(ptr->val);
        fprintf(fp, "%s %d\n", session->username, session->sockfd);
    }
    fclose(fp);
}
#endif // SESSION_H_
