// void f(void (*f1)(), void (*f2)())
// {
//     f1();
//     f2();
// }

#if !defined(ACTIVITY_LOGIN_H_)
#define ACTIVITY_LOGIN_H_
#include <stdbool.h>
#include "index.h"
#include "utils.h"
extern int clientfd;
/**
 * @brief process login
 *
 * @param username
 * @param password
 * @param message output message
 * @return true (if login success)
 * @return false (if login failed)
 */
bool processLogin(char *username, char *password, char message[100]);

bool processLogin(char *username, char *password, char message[100])
{
    if (!validateUsername(username, message))
    {
        return false;
    }
    if (!validatePassword(password, message))
    {
        return false;
    }
    Req req = createLoginRequest(username, password);
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
#endif // ACTIVITY_LOGIN_H_
