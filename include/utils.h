#ifndef UTILS_H_
#define UTILS_H_
#include "index.h"
#include <ctype.h>
bool validateUsername(char *username, char *message);
bool validatePassword(char *password, char *message);

bool validateUsername(char *username, char *message)
{
    if (strlen(username) < 6)
    {
        strcpy(message, "Username must be at least 6 characters");
        return false;
    }
    if (strlen(username) > 20)
    {
        strcpy(message, "Username must be at most 20 characters");
        return false;
    }
    for (int i = 0; i < strlen(username); i++)
    {
        if (username[i] == ' ')
        {
            strcpy(message, "Username must not contain space");
            return false;
        }
    }
    return true;
}

bool validatePassword(char *password, char *message)
{
    if (strlen(password) < 6)
    {
        strcpy(message, "Password must be at least 6 characters");
        return false;
    }
    if (strlen(password) > 20)
    {
        strcpy(message, "Password must be at most 20 characters");
        return false;
    }
    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i] == ' ')
        {
            strcpy(message, "Password must not contain space");
            return false;
        }
    }
    return true;
}
#endif /* UTILS_H_ */