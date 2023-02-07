#if !defined(UI_LOGIN_H_)
#define UI_LOGIN_H_
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "screen.h"
#include "login.h"
#include "signup.h"
#include "active.ui.h"
#include "room.ui.h"
const char txt_cnt_signup[2][100] = {"Don't have an account?", "Sign up to play with us."};
const char txt_cnt_login[2][100] = {"Have an account?", "Login and play now."};

// global variables
WINDOW *main_win_login;
WINDOW *top_win_login;
WINDOW *input_win_login;
WINDOW *top_btn_login;
WINDOW *username_input_login;
WINDOW *password_input_login;
WINDOW *submit_btn_login;
WINDOW *cancel_btn_login;
WINDOW *active_btn_login;
bool is_login = true;
MEVENT m_event;
char username[100];
char password[100];
// prototypes
// implementation

void init_login(void)
{
    clear();
    refresh();
    main_win_login = stdscr;
    box(main_win_login, 0, 0);
    initscr();
    init_top_win_login();
    init_input_win_login();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    refresh();
}
void init_top_win_login(void)
{
    top_win_login = subwindow(main_win_login, 8, 60, getmaxy(main_win_login) / 2 - 18, getmaxx(main_win_login) / 2 - 30);
    top_btn_login = subwindow(top_win_login, 3, 11, 4, 3);
    active_btn_login = subwindow(top_win_login, 3, 20, 4, 37);
    wattron(top_win_login, A_BOLD | COLOR_PAIR(4));
    box(top_win_login, 0, 0);
    wattroff(top_win_login, A_BOLD | COLOR_PAIR(4));
    wattron(top_btn_login, A_BOLD | COLOR_PAIR(14));
    box(top_btn_login, 0, 0);
    wattroff(top_btn_login, A_BOLD | COLOR_PAIR(14));
    wattron(active_btn_login, COLOR_PAIR(15));
    box(active_btn_login, 0, 0);
    wattron(active_btn_login, A_UNDERLINE);
    mvwprintw(active_btn_login, 1, 3, "%s", "Active account");
    wattroff(active_btn_login, A_UNDERLINE | COLOR_PAIR(15));
    touchwin(main_win_login);
    wrefresh(main_win_login);
    switch_top_win_login();
}
void init_input_win_login(void)
{
    input_win_login = subwindow(main_win_login, 30, 60, getmaxy(main_win_login) / 2 - 10, getmaxx(main_win_login) / 2 - 30);
    username_input_login = subwindow(input_win_login, 3, 50, 11, 5);
    password_input_login = subwindow(input_win_login, 3, 50, 15, 5);
    submit_btn_login = subwindow(input_win_login, 3, 12, 22, 15);
    cancel_btn_login = subwindow(input_win_login, 3, 12, 22, 32);
    wattron(username_input_login, A_BOLD | COLOR_PAIR(10));
    box(username_input_login, 0, 0);
    wattroff(username_input_login, A_BOLD | COLOR_PAIR(10));
    wattron(password_input_login, A_BOLD | COLOR_PAIR(10));
    box(password_input_login, 0, 0);
    wattroff(password_input_login, A_BOLD | COLOR_PAIR(10));
    wattron(submit_btn_login, A_BOLD | COLOR_PAIR(10));
    box(submit_btn_login, 0, 0);
    mvwprintw(submit_btn_login, 1, 3, "%-7s", "Submit");
    wattroff(submit_btn_login, A_BOLD | COLOR_PAIR(10));
    wattron(input_win_login, A_BOLD | COLOR_PAIR(4));
    box(input_win_login, 0, 0);
    wattroff(input_win_login, A_BOLD | COLOR_PAIR(4));

    mvwprintw(username_input_login, 1, 2, "%-30s", "Username: ");
    mvwprintw(password_input_login, 1, 2, "%-30s", "Password: ");
    mvwprintw(cancel_btn_login, 1, 3, "%-7s", "Cancel");
    wrefresh(username_input_login);
    wrefresh(password_input_login);
    wrefresh(submit_btn_login);
    wrefresh(input_win_login);
    switch_input_win_login();
}
void switch_top_win_login(void)
{
    wattron(top_win_login, A_BOLD | COLOR_PAIR(11));
    wattron(top_btn_login, A_BOLD | COLOR_PAIR(14));
    if (is_login)
    {
        mvwprintw(top_win_login, 2, 2, "   %-37s", txt_cnt_signup[0]);
        mvwprintw(top_win_login, 3, 2, "   %-37s", txt_cnt_signup[1]);
        mvwprintw(top_btn_login, 1, 2, "%-8s", "Sign up");
    }
    else
    {
        mvwprintw(top_win_login, 2, 2, "   %-37s", txt_cnt_login[0]);
        mvwprintw(top_win_login, 3, 2, "   %-37s", txt_cnt_login[1]);
        mvwprintw(top_btn_login, 1, 2, "%-8s", "Login");
    }
    wattroff(top_win_login, A_BOLD | COLOR_PAIR(11));
    wattroff(top_btn_login, A_BOLD | COLOR_PAIR(14));
    wrefresh(top_btn_login);
    wrefresh(top_win_login);
}
void switch_input_win_login(void)
{
    wattron(input_win_login, A_BOLD | COLOR_PAIR(10));
    if (is_login)
    {
        mvwprintw(input_win_login, 3, 8, "%50s", "");
        mvwprintw(input_win_login, 3, 8, "%-70s", "  ██╗      ██████╗  ██████╗ ██╗███╗   ██╗");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 4, 8, "%50s", "");
        mvwprintw(input_win_login, 4, 8, "%-70s", "  ██║     ██╔═══██╗██╔════╝ ██║████╗  ██║");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 5, 8, "%50s", "");
        mvwprintw(input_win_login, 5, 8, "%-70s", "  ██║     ██║   ██║██║  ███╗██║██╔██╗ ██║");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 6, 8, "%50s", "");
        mvwprintw(input_win_login, 6, 8, "%-70s", "  ██║     ██║   ██║██║   ██║██║██║╚██╗██║");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 7, 8, "%50s", "");
        mvwprintw(input_win_login, 7, 8, "%-70s", "  ███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 8, 8, "%50s", "");
        mvwprintw(input_win_login, 8, 8, "%-70s", "  ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝");
    }
    else
    {
        mvwprintw(input_win_login, 3, 8, "%-40s", "███████╗██╗ ██████╗ ███╗   ██╗██╗   ██╗██████╗ ");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 4, 8, "%-40s", "██╔════╝██║██╔════╝ ████╗  ██║██║   ██║██╔══██╗");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 5, 8, "%-40s", "███████╗██║██║  ███╗██╔██╗ ██║██║   ██║██████╔╝");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 6, 8, "%-40s", "╚════██║██║██║   ██║██║╚██╗██║██║   ██║██╔═══╝ ");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 7, 8, "%-40s", "███████║██║╚██████╔╝██║ ╚████║╚██████╔╝██║     ");
        napms(100);
        wrefresh(input_win_login);
        mvwprintw(input_win_login, 8, 8, "%-40s", "╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝     ");
    }

    wattroff(input_win_login, A_BOLD | COLOR_PAIR(10));
    wrefresh(input_win_login);
}
WINDOW *get_target_win_login()
{
    int tbbx = getbegx(top_btn_login), tbby = getbegy(top_btn_login), tbbw = getmaxx(top_btn_login), tbbh = getmaxy(top_btn_login);
    int uibx = getbegx(username_input_login), uiby = getbegy(username_input_login), uibw = getmaxx(username_input_login), uibh = getmaxy(username_input_login);
    int pibx = getbegx(password_input_login), piby = getbegy(password_input_login), pibw = getmaxx(password_input_login), pibh = getmaxy(password_input_login);
    int sbbx = getbegx(submit_btn_login), sbby = getbegy(submit_btn_login), sbbw = getmaxx(submit_btn_login), sbbh = getmaxy(submit_btn_login);
    int cbbx = getbegx(cancel_btn_login), cbby = getbegy(cancel_btn_login), cbbw = getmaxx(cancel_btn_login), cbbh = getmaxy(cancel_btn_login);
    int abbx = getbegx(active_btn_login), abby = getbegy(active_btn_login), abbw = getmaxx(active_btn_login), abbh = getmaxy(active_btn_login);
    int mx = m_event.x, my = m_event.y;
    if (mx >= tbbx && mx <= tbbx + tbbw && my >= tbby && my <= tbby + tbbh)
    {
        return top_btn_login;
    }
    if (mx >= uibx && mx <= uibx + uibw && my >= uiby && my <= uiby + uibh)
    {
        return username_input_login;
    }
    if (mx >= pibx && mx <= pibx + pibw && my >= piby && my <= piby + pibh)
    {
        return password_input_login;
    }
    if (mx >= sbbx && mx <= sbbx + sbbw && my >= sbby && my <= sbby + sbbh)
    {
        return submit_btn_login;
    }
    if (mx >= cbbx && mx <= cbbx + cbbw && my >= cbby && my <= cbby + cbbh)
    {
        return cancel_btn_login;
    }
    if (mx >= abbx && mx <= abbx + abbw && my >= abby && my <= abby + abbh)
    {
        return active_btn_login;
    }
    beep();
    return NULL;
}

void input(int i_type)
{
    mousemask(0, NULL);
    curs_set(true);
    echo();

    if (i_type == 2)
    {
        mvwprintw(password_input_login, 1, 12, "%-20s", "");
        mvwscanw(password_input_login, 1, 12, "%s", password);
        curs_set(false);
        for (int i = 0; i < strlen(password); i++)
        {
            mvwprintw(password_input_login, 1, 12 + i, "*");
            napms(20);
            wrefresh(password_input_login);
        }
    }
    else
    {
        mvwprintw(username_input_login, 1, 12, "%-20s", "");
        mvwscanw(username_input_login, 1, 12, "%s", username);
    }
    curs_set(false);

    noecho();
    mousemask(ALL_MOUSE_EVENTS, NULL);
}
void del_login(void)
{
    delwin(username_input_login);
    delwin(password_input_login);
    delwin(submit_btn_login);
    delwin(cancel_btn_login);
    delwin(input_win_login);
    delwin(top_btn_login);
    delwin(top_win_login);
    // delwin(main_win_login);
    clear();
    touchwin(main_win_login);
    refresh();
    // endwin();
}

void listen_mouse_event_login(void)
{
    WINDOW *target = NULL;
    int c;
    bool success = false;
    char message[127];
    while (true)
    {
        keypad(main_win_login, true);
        c = wgetch(main_win_login);
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
            target = get_target_win_login();
            if (target == top_btn_login)
            {
                is_login = !is_login;
                switch_top_win_login();
                switch_input_win_login();
            }
            else if (target == username_input_login)
            {
                mvwprintw(input_win_login, 19, 10, "%-40s", "");
                wrefresh(input_win_login);
                input(1);
            }
            else if (target == password_input_login)
            {
                mvwprintw(input_win_login, 19, 10, "%-40s", "");
                wrefresh(input_win_login);
                input(2);
            }
            else if (target == submit_btn_login)
            {
                success = is_login ? processLogin(username, password, message) : processSignup(username, password, message);
                if (success)
                {
                    if (is_login)
                    {
                        del_login();
                        splashscreen();
                        init_room(username);
                        listen_mouse_event_room();
                        init_login();
                    }
                    else
                    {
                        wattr_on(input_win_login, A_BOLD | COLOR_PAIR(14), NULL);
                        mvwprintw(input_win_login, 19, 10, "%-40s", message);
                        wrefresh(input_win_login);
                        wattr_off(input_win_login, A_BOLD | COLOR_PAIR(14), NULL);
                    }
                }
                else
                {
                    wattr_on(input_win_login, A_BOLD | COLOR_PAIR(16), NULL);
                    mvwprintw(input_win_login, 19, 10, "%-40s", message);
                    wrefresh(input_win_login);
                    wattr_off(input_win_login, A_BOLD | COLOR_PAIR(16), NULL);
                }
            }
            else if (target == active_btn_login)
            {
                del_login();
                activeUI();
                init_login();
            }
            else if (target == cancel_btn_login)
            {
                napms(100);
                del_login();
                break;
            }
        }
    }
}
#endif // UI_LOGIN_H_
