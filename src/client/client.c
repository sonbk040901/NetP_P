#include "index.h"
#include "login.h"
#include "signup.h"
#include "login.ui.h"
#include "init.h"
int main(int argc, char const *argv[])
{
    // processLogin("admin", "admin", "message");
    int clientfd = initConnectionClient("127.0.0.1", 5500);
    // Req req = createLoginRequest(argv[1], argv[2]);
    // Req req = createSignupRequest(argv[1], argv[2]);
    // Req req = createActiveRequest(argv[1], argv[2], "123456");
    // sendRequest(clientfd, req);
    // Res res;
    // sleep(3);
    // recvResponse(clientfd, &res);
    // printf("%s %s %d\n", res.data.resR.success ? "true" : "false", res.data.resR.message, clientfd);
    // closeConnection(clientfd);
    init_curses();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    curs_set(false);
    init_login();
    listen_mouse_event_login();
    destroy_curses();
    return 0;
}
