#ifndef UI_ROOM_H_
#define UI_ROOM_H_
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include "screen.h"
#include "Game.ui.h"
#include "room.h"
// const char txt_cnt_signup[2][100] = {"Don't have an account?", "Sign up to play with us."};
// const char txt_cnt_login[2][100] = {"Have an account?", "Login and play now."};
// global variables
WINDOW *main_win_room;
WINDOW *top_win_room;
WINDOW *top_create_btn_room;
WINDOW *top_search_btn_room;
WINDOW *input_win_room;
WINDOW *chat_win_room;
WINDOW *input_string_room;
WINDOW *input_chat_room;
WINDOW *submit_btn_room;
WINDOW *cancel_btn_room;
WINDOW *pre_btn_room;
WINDOW *next_btn_room;
WINDOW *send_btn_room;
int choose_num[4];
int start;
WINDOW *number_win[4];
bool is_create = true;
int current_page_room = 1;
int total_page_room = 4;
char string_input[100];
MEVENT m_event;
extern char username[100];
RoomInfo room_list[10];
int room_list_size = 0;
// prototypes
// implementation
void init_room(char *);
void init_top_win_room();
// void init_chat_win_room();
void listen_mouse_event_room();
// void switch_top_win_room();
WINDOW *get_target_win_room();
void del_room();
static void warning(const char *message);
void get_input_string_room()
{
    clearScr(input_string_room);
    mousemask(0, NULL);
    curs_set(true);
    echo();
    mvwscanw(input_string_room, 1, 3, "%s", string_input);
    noecho();
    curs_set(false);
    mousemask(ALL_MOUSE_EVENTS, NULL);
}
void init_room(char *usernamw)
{
    strcpy(username, usernamw);
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
    top_win_room = subwindow(main_win_room, 8, 80, getmaxy(main_win_room) / 2 - 20, getmaxx(main_win_room) / 2 - 40);
    top_create_btn_room = subwindow(top_win_room, 3, 18, 4, 3);
    top_search_btn_room = subwindow(top_win_room, 3, 18, 4, 59);

    box(top_win_room, 0, 0);
    box(top_create_btn_room, 0, 0);
    box(top_search_btn_room, 0, 0);

    wbkgd(top_create_btn_room, COLOR_PAIR(14) | A_BOLD);
    wbkgd(top_search_btn_room, COLOR_PAIR(10) | A_BOLD);
    wbkgd(top_win_room, COLOR_PAIR(16) | A_BOLD);

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
    input_win_room = subwindow(main_win_room, 35, 80, getmaxy(main_win_room) / 2 - 12, getmaxx(main_win_room) / 2 - 40);
    switch_input_win_room();
}

void choose_number()
{
    int mx = m_event.x, my = m_event.y;
    int numberx = (mx - start - getbegx(input_win_room)) / 13;
    // cardx = cardx > 12 ? 12 : cardx;
    if (mx > start && numberx <= 3 && numberx >= 0 && my > getbegy(number_win[0]) && my < getbegy(number_win[0]) + 8)
    {
        choose_num[numberx] = !choose_num[numberx];
        for (int i = 0; i < 4; i++)
        {
            if (i != numberx)
            {
                choose_num[i] = 0;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        delwin(number_win[i]);
        number_win[i] = subwindow(input_win_room, 8, 12, getmaxy(input_win_room) - 17, start + i * 13);
        if (choose_num[i] == 1)
            wbkgd(number_win[i], COLOR_PAIR(16) | A_BOLD);
        else
            wbkgd(number_win[i], A_BOLD);
        mvwprintw(number_win[i], 1, 0, " .--------.");
        mvwprintw(number_win[i], 2, 0, " |  .--.  |");
        mvwprintw(number_win[i], 3, 0, " |  :/\\:  |");
        mvwprintw(number_win[i], 4, 0, " |  (0%d)  |", i + 1);
        mvwprintw(number_win[i], 5, 0, " |  '--'  |");
        mvwprintw(number_win[i], 6, 0, " `--------'");
        box(number_win[i], 0, 0);
    }

    wrefresh(input_win_room);
}
void clearScr(WINDOW *org)
{
    for (int i = 2; i < getmaxy(org); i++)
    {
        for (int j = 2; j < getmaxx(org); j++)
        {
            mvwprintw(org, i - 1, j - 1, "%s", " ");
        }
    }
    box(org, 0, 0);
    wrefresh(org);
}
void print_list_room()
{
    mvwprintw(input_win_room, 9, 12, "%-5s %-15s %-15s %-8s %-10s", "ID", "Name", "Owner", "Player", "Status");
    // for (int i = 10 * (current_page_room - 1); i < current_page_room * 10; i++)
    // {
    //     mvwprintw(input_win_room, 10 + i - 10 * (current_page_room - 1), 15, "%-4d %-10s %-20s %-10s", i, "Room 1", "Hoan", "2/4");
    // }
    char str[10] = "    ";
    for (int i = 10 * (current_page_room - 1); i < current_page_room * 10; i++)
    {
        if (i < room_list_size)
        {
            str[0] = room_list[i].currentPlayer + '0';
            str[1] = '/';
            str[2] = room_list[i].maxPlayer + '0';
            mvwprintw(input_win_room, 11 + i - 10 * (current_page_room - 1), 12, "%-5d %-15s %-15s %-8s %-10s", room_list[i].id, room_list[i].roomName, room_list[i].owner, str, room_list[i].status ? "Playing" : "Waiting");
        }
        else
        {
            mvwprintw(input_win_room, 11 + i - 10 * (current_page_room - 1), 12, "%-5d %-15s %-15s %-8s %-10s", i + 1, "----------", "----------", "--/--", "----------");
        }
    }
    wrefresh(input_win_room);
}
void switch_input_win_room()
{
    clearScr(input_win_room);
    if (is_create)
    {
        wattron(input_win_room, COLOR_PAIR(12) | A_BOLD);
        mvwprintw(input_win_room, 1, 10, "%-35s", " _____                _           ______                      ");
        mvwprintw(input_win_room, 2, 10, "%-35s", "/  __ \\              | |          | ___ \\                     ");
        mvwprintw(input_win_room, 3, 10, "%-35s", "| /  \\/_ __ ___  __ _| |_ ___     | |_/ /___   ___  _ __ ___  ");
        mvwprintw(input_win_room, 4, 10, "%-35s", "| |   | '__/ _ \\/ _` | __/ _ \\    |    // _ \\ / _ \\| '_ ` _ \\ ");
        mvwprintw(input_win_room, 5, 10, "%-35s", "| \\__/\\ | |  __/ (_| | ||  __/    | |\\ \\ (_) | (_) | | | | | |");
        mvwprintw(input_win_room, 6, 10, "%-35s", " \\____/_|  \\___|\\__,_|\\__\\___|    \\_| \\_\\___/ \\___/|_| |_| |_|");
        // mvwprintw(input_win_room, 8, 10, "%-35s", "              |___/");
        // mvwprintw(input_win_room, 16, 10, "%-35s", " \\____/_|  \\___|\\__,_|\\__\\___|    \\_| \\_\\___/ \\___/|_| |_| |_|");
        wattroff(input_win_room, COLOR_PAIR(12) | A_BOLD);
        submit_btn_room = subwindow(input_win_room, 3, 10, 28, 58);
        cancel_btn_room = subwindow(input_win_room, 3, 10, 28, 14);
        input_string_room = subwindow(input_win_room, 3, 20, 12, 34);
        box(input_win_room, 0, 0);
        box(submit_btn_room, 0, 0);
        box(cancel_btn_room, 0, 0);
        wbkgd(input_string_room, A_BOLD | COLOR_PAIR(10));
        box(input_string_room, 0, 0);
        mvwprintw(input_win_room, 13, 24, "%-10s", "Room Name");
        mvwprintw(input_win_room, 16, 30, "%-35s", "Choose number of players");
        mvwprintw(input_string_room, 1, 3, "%s", string_input);
        start = getmaxx(input_win_room) / 2 - 12 * 4 / 2;
        for (int i = 0; i < 4; i++)
        {
            delwin(number_win[i]);
            number_win[i] = subwindow(input_win_room, 8, 12, getmaxy(input_win_room) - 17, start + i * 13);
            if (choose_num[i] == 1)
                wbkgd(number_win[i], COLOR_PAIR(16) | A_BOLD);
            else
                wbkgd(number_win[i], A_BOLD);
            mvwprintw(number_win[i], 1, 0, " .--------.");
            mvwprintw(number_win[i], 2, 0, " |  .--.  |");
            mvwprintw(number_win[i], 3, 0, " |  :/\\:  |");
            mvwprintw(number_win[i], 4, 0, " |  (0%d)  |", i + 1);
            mvwprintw(number_win[i], 5, 0, " |  '--'  |");
            mvwprintw(number_win[i], 6, 0, " `--------'");
            box(number_win[i], 0, 0);
        }
        wbkgd(submit_btn_room, COLOR_PAIR(10) | A_BOLD);
        mvwprintw(submit_btn_room, 1, 2, "%-7s", "Submit");
        mvwprintw(cancel_btn_room, 1, 2, "%-7s", "Cancel");
        wrefresh(submit_btn_room);
        wrefresh(cancel_btn_room);
        wrefresh(input_win_room);
    }
    else
    {
        wattron(input_win_room, COLOR_PAIR(15) | A_BOLD);

        mvwprintw(input_win_room, 1, 10, "%-35s", " _____                     _      ______                      ");
        mvwprintw(input_win_room, 2, 10, "%-35s", "/  ___|                   | |     | ___ \\                     ");
        mvwprintw(input_win_room, 3, 10, "%-35s", "\\ `--.  ___  __ _ _ __ ___| |__   | |_/ /___   ___  _ __ ___  ");
        mvwprintw(input_win_room, 4, 10, "%-35s", " `--. \\/ _ \\/ _` | '__/ __| '_ \\  |    // _ \\ / _ \\| '_ ` _ \\ ");
        mvwprintw(input_win_room, 5, 10, "%-35s", "/\\__/ /  __/ (_| | | | (__| | | | | |\\ \\ (_) | (_) | | | | | |");
        mvwprintw(input_win_room, 6, 10, "%-35s", "\\____/ \\___|\\__,_|_|  \\___|_| |_| \\_| \\_\\___/ \\___/|_| |_| |_|");
        wattroff(input_win_room, COLOR_PAIR(15) | A_BOLD);

        submit_btn_room = subwindow(input_win_room, 3, 10, 28, 58);
        cancel_btn_room = subwindow(input_win_room, 3, 10, 28, 14);
        pre_btn_room = subwindow(input_win_room, 3, 5, 13, 3);
        next_btn_room = subwindow(input_win_room, 3, 5, 13, getmaxx(input_win_room) - 8);
        mvwprintw(input_win_room, 23, 32, "%-20s", "Enter Room's Name");
        input_string_room = subwindow(input_win_room, 3, 20, 24, 31);

        wbkgd(input_string_room, A_BOLD | COLOR_PAIR(10));
        box(input_string_room, 0, 0);

        box(pre_btn_room, 0, 0);
        box(next_btn_room, 0, 0);
        box(submit_btn_room, 0, 0);
        box(cancel_btn_room, 0, 0);
        wbkgd(pre_btn_room, COLOR_PAIR(12) | A_BOLD);
        mvwprintw(pre_btn_room, 1, 2, "%-s", "<");
        wbkgd(next_btn_room, COLOR_PAIR(12) | A_BOLD);
        mvwprintw(next_btn_room, 1, 2, "%-s", ">");
        wbkgd(submit_btn_room, COLOR_PAIR(10) | A_BOLD);
        mvwprintw(submit_btn_room, 1, 2, "%-s", "Submit");
        mvwprintw(cancel_btn_room, 1, 2, "%-s", "Cancel");
        wrefresh(pre_btn_room);
        wrefresh(next_btn_room);
        wrefresh(input_string_room);
        wrefresh(submit_btn_room);
        wrefresh(cancel_btn_room);
        print_list_room();
    }
    wrefresh(input_win_room);
}
WINDOW *get_target_win_room()
{
    int tcbbx = getbegx(top_create_btn_room), tcbby = getbegy(top_create_btn_room), tcbbw = getmaxx(top_create_btn_room), tcbbh = getmaxy(top_create_btn_room);
    int tsbbx = getbegx(top_search_btn_room), tsbby = getbegy(top_search_btn_room), tsbbw = getmaxx(top_search_btn_room), tsbbh = getmaxy(top_search_btn_room);
    int inbx = getbegx(input_string_room), inby = getbegy(input_string_room), inbw = getmaxx(input_string_room), inbh = getmaxy(input_string_room);
    // int pibx = getbegx(password_input), piby = getbegy(password_input), pibw = getmaxx(password_input), pibh = getmaxy(password_input);
    int cbbx = getbegx(submit_btn_room), cbby = getbegy(submit_btn_room), cbbw = getmaxx(submit_btn_room), cbbh = getmaxy(submit_btn_room);
    int cbbx2 = getbegx(cancel_btn_room), cbby2 = getbegy(cancel_btn_room), cbbw2 = getmaxx(cancel_btn_room), cbbh2 = getmaxy(cancel_btn_room);
    int pbbx = getbegx(pre_btn_room), pbby = getbegy(pre_btn_room), pbbw = getmaxx(pre_btn_room), pbbh = getmaxy(pre_btn_room);
    int nbbx = getbegx(next_btn_room), nbby = getbegy(next_btn_room), nbbw = getmaxx(next_btn_room), nbbh = getmaxy(next_btn_room);
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
        return input_string_room;
    }
    if (mx >= cbbx && mx <= cbbx + cbbw && my >= cbby && my <= cbby + cbbh)
    {
        return submit_btn_room;
    }
    if (mx >= cbbx2 && mx <= cbbx2 + cbbw2 && my >= cbby2 && my <= cbby2 + cbbh2)
    {
        return cancel_btn_room;
    }
    if (!is_create && mx >= pbbx && mx <= pbbx + pbbw && my >= pbby && my <= pbby + pbbh)
    {
        return pre_btn_room;
    }
    if (!is_create && mx >= nbbx && mx <= nbbx + nbbw && my >= nbby && my <= nbby + nbbh)
    {
        return next_btn_room;
    }
    return NULL;
}

void del_room()
{
    // delwin(input_string_room);
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
    char mess[100];
    bool success = false;
    Res res;
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
            if (is_create == 1)
                choose_number();

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
                switch_input_win_room();
                processFindRoom("", &room_list_size, room_list);
                print_list_room();
                // switch_top_win_room();
            }
            else if (target == input_string_room)
            {
                get_input_string_room();
            }
            else if (target == submit_btn_room)
            {
                del_room();
                napms(150);
                if (is_create)
                {
                    success = processCreateRoom(string_input, getPlayerNum(), mess);
                    if (success)
                    {
                        splashscreen();
                        init_game(username, string_input);
                        listen_mouse_game();
                    }
                    else
                        warning(mess);
                }
                else
                {
                    success = processJoinRoom(string_input, mess);
                    if (success)
                    {
                        splashscreen();
                        init_game(username, string_input);
                        listen_mouse_game();
                    }
                    else
                        warning(mess);
                }
                napms(150);
                init_room(username);
            }
            else if (target == cancel_btn_room)
            {
                // del_room();
                napms(150);
                // splashscreen();
                // init_login();
                // listen_mouse_event_login();
                // napms(150);
                del_room();
                break;
                // init_room(username);
            }
            else if (target == pre_btn_room)
            {
                if (current_page_room > 1)
                {
                    current_page_room--;
                    print_list_room();
                }
            }
            else if (target == next_btn_room)
            {
                if (current_page_room < total_page_room)
                {
                    current_page_room++;
                    print_list_room();
                }
            }
        }
    }
}
int getPlayerNum()
{
    for (int i = 0; i < 4; i++)
    {
        if (choose_num[i] == 1)
        {
            return i + 1;
        }
    }
}
static void warning(const char *message)
{
    WINDOW *warning_win = newwin(10, 50, LINES / 2, COLS / 2 - 25);
    wattron(warning_win, COLOR_PAIR(4));
    box(warning_win, 0, 0);
    wattron(warning_win, A_STANDOUT);
    mvwprintw(warning_win, 2, 2, "%40s", message);
    wattroff(warning_win, COLOR_PAIR(4) | A_STANDOUT);
    wattron(warning_win, COLOR_PAIR(14));
    mvwprintw(warning_win, 7, 2, "%s", "Press any key to continue");
    wattroff(warning_win, COLOR_PAIR(14));
    wrefresh(warning_win);
    wgetch(warning_win);
    delwin(warning_win);
    refresh();
}
#endif