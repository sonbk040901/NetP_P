#include "index.h"
#include "login.h"
#include "signup.h"
#include "login.ui.h"
#include "room.ui.h"
#include "game.ui.h"
#include "init.h"
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./client <server ip> <server port>\n");
        exit(0);
    }
    int clientfd = initConnectionClient(argv[1], atoi(argv[2]));
    init_curses();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    curs_set(false);
    init_login();
    listen_mouse_event_login();

    destroy_curses();
    return 0;
}
