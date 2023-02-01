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
bool validateActivationCode(char *activationCode, char *message)
{
    if (strlen(activationCode) != 8)
    {
        strcpy(message, "Activation code must be 6 characters");
        return false;
    }
    for (int i = 0; i < strlen(activationCode); i++)
    {
        if (!isdigit(activationCode[i]))
        {
            strcpy(message, "Activation code must be a number");
            return false;
        }
    }
    return true;
}
bool validateRoomName(char *roomName, char *message)
{
    if (strlen(roomName) < 6)
    {
        strcpy(message, "Room name must be at least 6 characters");
        return false;
    }
    if (strlen(roomName) > 20)
    {
        strcpy(message, "Room name must be at most 20 characters");
        return false;
    }
}
bool validateMaxPlayer(int maxPlayer, char *message)
{
    if (maxPlayer < 2)
    {
        strcpy(message, "Play with bot is not supported yet");
        return false;
    }
    if (maxPlayer > 4)
    {
        strcpy(message, "Max player must be at most 4");
        return false;
    }
}
#endif /* UTILS_H_ */