#if !defined(REQUEST_HANDLER_H_)
#define REQUEST_HANDLER_H_
#include "user.h"
#include "index.h"
#include "room.h"
#include <sys/types.h>
void loginHandler(int, Req);
void signupHandler(int, Req);
void activeHandler(int, Req);

void loginHandler(int sockfd, Req req)
{
    Dllist userList = makeUsersList("users.txt");
    User user = existsUser(userList, req.data.login.username);
    Res res;
    if (!user)
    {
        res = createRResponse(false, "User not found");
        goto done;
    }
    if (user->status == idle)
    {
        res = createRResponse(false, "User is not active");
        goto done;
    }

    asyncErrCount(user);
    if (user->errCount >= 3)
    {
        res = createRResponse(false, "User was blocked");
        goto done;
    }
    if (!checkPassword(user, req.data.login.password))
    {
        user->errCount++;
        if (user->errCount >= 3)
        {
            res = createRResponse(false, "User is blocked");
            blockUser(user);
        }
        else
            res = createRResponse(false, "Wrong password");
        goto done;
    }
    res = createRResponse(true, "Login successfully");
    initSession(user->username, sockfd);
    user->errCount = 0;
done:
    sendResponse(sockfd, res);
    exportList(userList, "users.txt");
    freeUserList(userList);
}
void signupHandler(int sockfd, Req req)
{
    Dllist userList = makeUsersList("users.txt");
    User user = existsUser(userList, req.data.signup.username);
    Res res;
    if (user)
    {
        res = createRResponse(false, "User already exists");
        goto done;
    }
    user = newUser(req.data.signup.username, req.data.signup.password, idle);
    addUser(userList, user);
    res = createRResponse(true, "Signup successfully");
    // res = (Res){
    //     .type = R_RES,
    //     .data.resR = {
    //         .success = true,
    //         .message = "Signup successfully",
    //     },
    // };
done:
    sendResponse(sockfd, res);
    exportList(userList, "users.txt");
    freeUserList(userList);
}

void activeHandler(int sockfd, Req req)
{
    Dllist userList = makeUsersList("users.txt");
    ActiveReqD data = req.data.active;
    User user = existsUser(userList, data.userData.username);
    Res res;
    if (!user)
    {
        res = createRResponse(false, "User not found");
        goto done;
    }
    if (user->status == active)
    {
        res = createRResponse(false, "User is already active");
        goto done;
    }
    if (activate(user, data.activationCode))
    {
        res = createRResponse(true, "User is activated");
        activeUser(user);
    }
    else
        res = createRResponse(false, "Wrong activation code");
done:
    sendResponse(sockfd, res);
    exportList(userList, "users.txt");
    freeUserList(userList);
}
#endif // REQUEST_HANDLER_H_
