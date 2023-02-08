#include "index.h"
#include "login.h"
#include "signup.h"
#include "login.ui.h"
#include "room.ui.h"
#include "game.ui.h"
#include "init.h"
int main(/*int argc, char const *argv[]*/)
{
    int clientfd = initConnectionClient("10.70.40.167", 5500);
    init_curses();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    curs_set(false);
    init_login();
    listen_mouse_event_login();

    destroy_curses();
    return 0;
}
