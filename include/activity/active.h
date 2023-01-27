#if !defined(ACTIVITY_ACTIVE_H_)
#define ACTIVITY_ACTIVE_H_
#include "index.h"
#include "utils.h"
extern int clientfd;
bool processActive(char *username, char *password, char *activationCode, char *);

bool processActive(char *username, char *password, char *activationCode, char *message)
{
    if (!validateUsername(username, message))
    {
        return false;
    }
    if (!validatePassword(password, message))
    {
        return false;
    }
    if (!validateActivationCode(activationCode, message))
    {
        return false;
    }
    Req req = createActiveRequest(username, password, activationCode);
    int bytes = sendRequest(clientfd, req);
    if (bytes < 0)
    {
        strcpy(message, "Error sending request");
        return false;
    }
    if (bytes == 0)
    {
        strcpy(message, "Connection closed");
        return false;
    }
    Res res;
    bytes = recvResponse(clientfd, &res);
    if (bytes < 0)
    {
        strcpy(message, "Error receiving response");
        return false;
    }
    if (bytes == 0)
    {
        strcpy(message, "Connection closed");
        return false;
    }
    bool isSuccess = res.data.resR.success;
    strcpy(message, res.data.resR.message);
    return isSuccess;
}
#endif // ACTIVITY_ACTIVE_H_
