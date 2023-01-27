#include "index.h"
#include "login.h"
// #include "login.ui.h"
int main(int argc, char const *argv[])
{
    // processLogin("admin", "admin", "message");
    int clientfd = initConnectionClient("127.0.0.1", 5500);
    Req req = createLoginRequest(argv[1], argv[2]);
    // Req req = createSignupRequest(argv[1], argv[2]);
    sendRequest(clientfd, req);
    Res res;
    sleep(3);
    recvResponse(clientfd, &res);
    printf("%s %s %d\n", res.data.resR.success ? "true" : "false", res.data.resR.message, clientfd);
    closeConnection(clientfd);
    return 0;
}
