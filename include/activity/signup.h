#if !defined(ACTIVITY_SIGNUP_H_)
#define ACTIVITY_SIGNUP_H_
#include "index.h"
bool processSignup(char *username, char *password, char message[100]);

bool processSignup(char *username, char *password, char message[100])
{
    Req req = createSignupRequest(username, password);
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
#endif // ACTIVITY_SIGNUP_H_