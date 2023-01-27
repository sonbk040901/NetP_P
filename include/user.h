#ifndef _USER_H
#define _USER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <ctype.h>
#include <string.h>
#include "dllist.h"
#include "fields.h"
#include "jrb.h"
#include "jval.h"
#include "queue.h"
#define ACTIVATION_CODE "20194658"
typedef enum status
{
    blocked,
    active,
    idle
} Status;
typedef struct _User
{
    char username[127];
    char password[127];
    Status status;
    char errCount;
} *User;

User newUser(char *username, char *password, Status status);
void blockUser(User user);
void activeUser(User user);
void setPassword(User user, char *password);
Status getUserStatus(User user);
char *getUserName(User user);
char *getUserPassword(User user);
void freeUser(User user);
void asyncErrCount(User user);

Dllist makeUsersList(char *filename);
User existsUser(Dllist list, char *username);
void addUser(Dllist list, User user);
void exportList(Dllist list, char *filename);
void freeUserList(Dllist list);
int activate(User user, char *activationCode);
User verify(Dllist list, char *username, char *password);
int checkPassword(User user, char *password);
int updatePassword(User user, char *password);

User newUser(char *username, char *password, Status status)
{
    User user = malloc(sizeof(struct _User));
    strcpy(user->username, username);
    strcpy(user->password, password);
    user->status = status;
    user->errCount = status == blocked ? 3 : 0;
    return user;
}
void blockUser(User user)
{
    user->status = blocked;
}
void activeUser(User user)
{
    user->status = active;
}
void setPassword(User user, char *password)
{
    strcpy(user->password, password);
}
Status getUserStatus(User user)
{
    return user->status;
}
void freeUser(User user)
{
    free(user);
}

char *getUserName(User user)
{
    return user->username;
}
char *getUserPassword(User user)
{
    return user->password;
}
Dllist makeUsersList(char *filename)
{
    Dllist list = new_dllist();
    IS is = new_inputstruct(filename);
    if (is == NULL)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    while (get_line(is) >= 0)
    {
        dll_append(list, new_jval_v(newUser(is->fields[0], is->fields[1], atoi(is->fields[2]))));
    }
    jettison_inputstruct(is);
    return list;
}
User existsUser(Dllist list, char *username)
{
    Dllist root;
    User user;
    dll_traverse(root, list)
    {
        user = (User)jval_v(dll_val(root));
        if (strcmp(user->username, username) == 0)
        {
            return user;
        }
    }
    return (User)0;
}
void addUser(Dllist list, User user)
{
    dll_append(list, new_jval_v(user));
}
void exportList(Dllist list, char *filename)
{
    Dllist temp;
    FILE *fout = fopen(filename, "w+");
    FILE *fErrCount = fopen("errCount.txt", "w+");
    dll_traverse(temp, list)
    {
        User user = (User)jval_v(dll_val(temp));
        // printf("User: %s %s %d\n", user->username, user->password, user->status);
        fprintf(fout, "%s %s %d", user->username, user->password, user->status);
        fprintf(fErrCount, "%s %d", user->username, user->errCount);
        if (temp != dll_last(list))
        {
            fprintf(fout, "\n");
            fprintf(fErrCount, "\n");
        }
    }
    fclose(fout);
    fclose(fErrCount);
}
void freeUserList(Dllist list)
{
    Dllist temp;
    dll_traverse(temp, list)
    {
        User user = (User)jval_v(dll_val(temp));
        freeUser(user);
    }
    free_dllist(list);
}
int activate(User user, char *activationCode)
{
    if (strcmp(activationCode, ACTIVATION_CODE) != 0)
    {
        return 0;
    }
    else
    {
        activeUser(user);
        return 1;
    }
}
User verify(Dllist list, char *username, char *password)
{
    Dllist root;
    User user;
    dll_traverse(root, list)
    {
        user = (User)jval_v(dll_val(root));
        if (strcmp(username, user->username) == 0)
        {
            if (strcmp(password, user->password) == 0)
            {
                return user;
            }
            else
            {
                return (User)0;
            }
        }
    }
    return (User)0;
}
int checkPassword(User user, char *password)
{
    return strcmp(password, user->password) == 0;
}
int updatePassword(User user, char *password)
{
    strcpy(user->password, password);
    return 1;
}
void asyncErrCount(User user)
{
    IS is = new_inputstruct("errCount.txt");
    if (is == NULL)
    {
        perror("errCount.txt");
        exit(EXIT_FAILURE);
    }
    while (get_line(is) >= 0)
    {
        if (strcmp(is->fields[0], user->username) == 0)
        {
            user->errCount = atoi(is->fields[1]);
            break;
        }
    }
    jettison_inputstruct(is);
    return;
}
#endif