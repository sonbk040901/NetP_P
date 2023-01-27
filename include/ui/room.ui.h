#ifndef UI_ROOM_H_
#define UI_ROOM_H_
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include "screen.h"
// #include "game.ui.h"
// const char txt_cnt_signup[2][100] = {"Don't have an account?", "Sign up to play with us."};
// const char txt_cnt_login[2][100] = {"Have an account?", "Login and play now."};
// global variables
WINDOW *main_win_room;
WINDOW *top_win_room;
WINDOW *top_create_btn_room;
WINDOW *top_search_btn_room;
WINDOW *input_win_room;
WINDOW *chat_win_room;
WINDOW *input_number_room;
WINDOW *input_chat_room;
WINDOW *submit_btn_room;
WINDOW *cancel_btn_room;
WINDOW *send_btn_room;

WINDOW *card_win[13];
bool is_create = true;
char number_input[10];
MEVENT m_event;
// prototypes
// implementation
void init_room(char *username);
void init_top_win_room();
void init_chat_win_room();
void listen_mouse_event_room();
void switch_top_win_room();
WINDOW *get_target_win_room();
void del_room();
void input_number();

void input_number()
{
    mousemask(0, NULL);
    curs_set(true);
    echo();
    mvwscanw(input_number_room, 1, 12, "%s", number_input);
    noecho();
    curs_set(false);
    mousemask(ALL_MOUSE_EVENTS, NULL);
}

void init_room(char *username)
{
    clear();
    refresh();
    main_win_room = stdscr;
    box(main_win_room, 0, 0);
    initscr();
    init_top_win_room();
    init_input_win_room();
    // init_chat_win_room();
    refresh();
}
void init_top_win_room()
{
    top_win_room = subwindow(main_win_room, 8, 80, 1, getmaxx(main_win_room) / 2 - 40);
    top_create_btn_room = subwindow(top_win_room, 3, 18, 4, 3);
    top_search_btn_room = subwindow(top_win_room, 3, 18, 4, 59);

    box(top_win_room, 0, 0);
    box(top_create_btn_room, 0, 0);
    box(top_search_btn_room, 0, 0);

    wbkgd(top_create_btn_room, COLOR_PAIR(4) | A_BOLD);
    wbkgd(top_search_btn_room, COLOR_PAIR(6) | A_BOLD);
    wbkgd(top_win_room, COLOR_PAIR(1) | A_BOLD);

    wrefresh(top_create_btn_room);
    wrefresh(top_search_btn_room);
    wrefresh(top_win_room);

    // mvwprintw(top_win_room, 2, 2, "%-40s", txt_cnt_signup[0]);
    // mvwprintw(top_win_room, 3, 2, "%-40s", txt_cnt_signup[1]);
    mvwprintw(top_create_btn_room, 1, 2, "%-13s", "Create Room");
    mvwprintw(top_search_btn_room, 1, 2, "%-13s", "Search Room");

    wrefresh(top_create_btn_room);
    wrefresh(top_search_btn_room);
    wrefresh(top_win_room);
}
void init_input_win_room()
{
    input_win_room = subwindow(main_win_room, 35, 80, 9, getmaxx(main_win_room) / 2 - 40);
    submit_btn_room = subwindow(input_win_room, 3, 10, 30, 12);
    cancel_btn_room = subwindow(input_win_room, 3, 10, 30, 58);
    input_number_room = subwindow(input_win_room, 3, 30, 19, 25);
    box(submit_btn_room, 0, 0);
    box(input_win_room, 0, 0);
    box(cancel_btn_room, 0, 0);
    box(input_number_room, 0, 0);
    mvwprintw(submit_btn_room, 1, 2, "%-7s", "Submit");
    mvwprintw(cancel_btn_room, 1, 2, "%-7s", "Cancel");

    wrefresh(input_number_room);
    wrefresh(submit_btn_room);
    wrefresh(cancel_btn_room);
    wrefresh(input_win_room);
    switch_input_win_room();
}

void init_chat_win_room()
{
    chat_win_room = subwindow(main_win_room, 43, getmaxx(stdscr) - 92, getmaxy(main_win_room) / 9, getmaxx(main_win_room) / 2 + 5);
    send_btn_room = subwindow(chat_win_room, 3, 10, 38, 55);
    input_chat_room = subwindow(chat_win_room, 3, 50, 38, 2);
    box(send_btn_room, 0, 0);
    box(chat_win_room, 0, 0);
    box(input_chat_room, 0, 0);
    mvwprintw(send_btn_room, 1, 2, "%-7s", "Send");

    mvwprintw(chat_win_room, 1, 10, "%-35s", " _____ _           _   ");
    mvwprintw(chat_win_room, 2, 10, "%-35s", "/  __ \\ |         | |  ");
    mvwprintw(chat_win_room, 3, 10, "%-35s", "| /  \\/ |__   __ _| |_ ");
    mvwprintw(chat_win_room, 4, 10, "%-35s", "| |   | '_ \\ / _` | __|");
    mvwprintw(chat_win_room, 5, 10, "%-35s", "| \\__/\\ | | | (_| | |_ ");
    mvwprintw(chat_win_room, 6, 10, "%-35s", " \\____/_| |_|\\__,_|\\__|");

    wrefresh(input_chat_room);
    wrefresh(send_btn_room);
    wrefresh(chat_win_room);
    switch_input_win_room();
}
void switch_input_win_room()
{

    if (is_create)
    {

        mvwprintw(input_win_room, 1, 10, "%-35s", " _____                _           ______                      ");
        mvwprintw(input_win_room, 2, 10, "%-35s", "/  __ \\              | |          | ___ \\                     ");
        mvwprintw(input_win_room, 3, 10, "%-35s", "| /  \\/_ __ ___  __ _| |_ ___     | |_/ /___   ___  _ __ ___  ");
        mvwprintw(input_win_room, 4, 10, "%-35s", "| |   | '__/ _ \\/ _` | __/ _ \\    |    // _ \\ / _ \\| '_ ` _ \\ ");
        mvwprintw(input_win_room, 5, 10, "%-35s", "| \\__/\\ | |  __/ (_| | ||  __/    | |\\ \\ (_) | (_) | | | | | |");
        mvwprintw(input_win_room, 6, 10, "%-35s", " \\____/_|  \\___|\\__,_|\\__\\___|    \\_| \\_\\___/ \\___/|_| |_| |_|");
        // mvwprintw(input_win_room, 8, 10, "%-35s", "              |___/");
        // mvwprintw(input_win_room, 16, 10, "%-35s", " \\____/_|  \\___|\\__,_|\\__\\___|    \\_| \\_\\___/ \\___/|_| |_| |_|");
    }
    else
    {
        mvwprintw(input_win_room, 1, 10, "%-35s", " _____                     _      ______                      ");
        mvwprintw(input_win_room, 2, 10, "%-35s", "/  ___|                   | |     | ___ \\                     ");
        mvwprintw(input_win_room, 3, 10, "%-35s", "\\ `--.  ___  __ _ _ __ ___| |__   | |_/ /___   ___  _ __ ___  ");
        mvwprintw(input_win_room, 4, 10, "%-35s", " `--. \\/ _ \\/ _` | '__/ __| '_ \\  |    // _ \\ / _ \\| '_ ` _ \\ ");
        mvwprintw(input_win_room, 5, 10, "%-35s", "/\\__/ /  __/ (_| | | | (__| | | | | |\\ \\ (_) | (_) | | | | | |");
        mvwprintw(input_win_room, 6, 10, "%-35s", "\\____/ \\___|\\__,_|_|  \\___|_| |_| \\_| \\_\\___/ \\___/|_| |_| |_|");
    }
    wrefresh(input_win_room);
}
WINDOW *get_target_win_room()
{
    int tcbbx = getbegx(top_create_btn_room), tcbby = getbegy(top_create_btn_room), tcbbw = getmaxx(top_create_btn_room), tcbbh = getmaxy(top_create_btn_room);
    int tsbbx = getbegx(top_search_btn_room), tsbby = getbegy(top_search_btn_room), tsbbw = getmaxx(top_search_btn_room), tsbbh = getmaxy(top_search_btn_room);
    int inbx = getbegx(input_number_room), inby = getbegy(input_number_room), inbw = getmaxx(input_number_room), inbh = getmaxy(input_number_room);
    // int pibx = getbegx(password_input), piby = getbegy(password_input), pibw = getmaxx(password_input), pibh = getmaxy(password_input);
    int sbbx = getbegx(submit_btn_room), sbby = getbegy(submit_btn_room), sbbw = getmaxx(submit_btn_room), sbbh = getmaxy(submit_btn_room);
    int cbbx = getbegx(cancel_btn_room), cbby = getbegy(cancel_btn_room), cbbw = getmaxx(cancel_btn_room), cbbh = getmaxy(cancel_btn_room);
    int mx = m_event.x, my = m_event.y;
    if (mx >= tcbbx && mx <= tcbbx + tcbbw && my >= tcbby && my <= tcbby + tcbbh)
    {
        return top_create_btn_room;
    }
    if (mx >= tsbbx && mx <= tsbbx + tsbbw && my >= tsbby && my <= tsbby + tsbbh)
    {
        return top_search_btn_room;
    }
    if (mx >= inbx && mx <= inbx + inbw && my >= inby && my <= inby + inbh)
    {
        return input_number_room;
    }
    // if (mx >= pibx && mx <= pibx + pibw && my >= piby && my <= piby + pibh)
    // {
    //     return password_input;
    // }
    if (mx >= sbbx && mx <= sbbx + sbbw && my >= sbby && my <= sbby + sbbh)
    {
        return submit_btn_room;
    }
    if (mx >= cbbx && mx <= cbbx + cbbw && my >= cbby && my <= cbby + cbbh)
    {
        return cancel_btn_room;
    }
    return NULL;
}
// void scan_username()
// {
//     char *username = (char *)malloc(sizeof(char) * 20);
//     echo();
//     mvwscanw(input_number_room, 1, 2, "%s", username);
//     noecho();
//     mvwprintw(input_number_room, 1, 2, "%-20s", username);
//     wrefresh(input_number_room);
//     free(username);
// }
// void scan_password()
// {
//     char *password = (char *)malloc(sizeof(char) * 20);
//     echo();
//     mvwscanw(password_input, 1, 2, "%s", password);
//     noecho();
//     mvwprintw(password_input, 1, 2, "%-20s", password);
//     wrefresh(password_input);
//     free(password);
// }
void del_room()
{
    // delwin(input_number_room);
    // delwin(password_input);
    delwin(submit_btn_room);
    delwin(cancel_btn_room);
    // delwin(input_win_room);
    delwin(top_create_btn_room);
    delwin(top_search_btn_room);
    delwin(top_win_room);
    // delwin(main_win_room);
    refresh();
    // endwin();
}
void listen_mouse_event_room(void)
{
    WINDOW *target = NULL;
    int c;
    while (1)
    {

        // noecho();
        keypad(main_win_room, true);
        c = wgetch(main_win_room);
        if (c == KEY_MOUSE)
        {
            if (getmouse(&m_event) != OK)
            {
                continue;
            }
        }
        else
        {
            continue;
        }
        if (m_event.bstate & BUTTON1_CLICKED)
        {
            target = get_target_win_room();
            if (target == top_create_btn_room)
            {
                is_create = 1;
                // switch_top_win_room();
                switch_input_win_room();
            }
            else if (target == top_search_btn_room)
            {
                is_create = 0;
                // switch_top_win_room();
                switch_input_win_room();
            }
            else if (target == input_number_room)
            {
                input_number();
            }
            // else if (target == password_input)
            // {
            // 	input_password();
            // }
            else if (target == submit_btn_room)
            {
                if (is_create)
                {
                    splashscreen();
                }
                else
                {
                    splashscreen();
                }
                napms(150);
                del_room();
                break;
            }
            else if (target == cancel_btn_room)
            {
                napms(100);
                del_room();
                break;
            }
        }
    }
}
#endif