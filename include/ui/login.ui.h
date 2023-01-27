#if !defined(UI_LOGIN_H_)
#define UI_LOGIN_H_
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "screen.h"
#include "login.h"
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
bool is_login = true;
MEVENT m_event;
char username[100];
char password[100];
// prototypes
// implementation

void login()
{

    splashscreen();
}
void signup()
{
    splashscreen();
}

void init_login(void)
{
    main_win_login = stdscr;
    box(main_win_login, 0, 0);
    init_top_win_login();
    init_input_win_login();
    refresh();
}
void init_top_win_login(void)
{
    top_win_login = subwindow(main_win_login, 8, 50, getmaxy(main_win_login) / 2 - 18, getmaxx(main_win_login) / 2 - 25);
    top_btn_login = subwindow(top_win_login, 3, 11, 4, 3);
    wattron(top_win_login, A_BOLD | COLOR_PAIR(4));
    box(top_win_login, 0, 0);
    wattroff(top_win_login, A_BOLD | COLOR_PAIR(4));
    wattron(top_btn_login, A_BOLD | COLOR_PAIR(14));
    box(top_btn_login, 0, 0);
    wattroff(top_btn_login, A_BOLD | COLOR_PAIR(14));
    wrefresh(input_win_login);
    wrefresh(top_btn_login);
    wrefresh(top_win_login);
    switch_top_win_login();
}
void init_input_win_login(void)
{
    input_win_login = subwindow(main_win_login, 25, 50, getmaxy(main_win_login) / 2 - 10, getmaxx(main_win_login) / 2 - 25);
    username_input_login = subwindow(input_win_login, 3, 40, 11, 5);
    password_input_login = subwindow(input_win_login, 3, 40, 15, 5);
    submit_btn_login = subwindow(input_win_login, 3, 10, 19, 12);
    cancel_btn_login = subwindow(input_win_login, 3, 10, 19, 27);
    wattron(username_input_login, A_BOLD | COLOR_PAIR(10));
    box(username_input_login, 0, 0);
    wattroff(username_input_login, A_BOLD | COLOR_PAIR(10));
    wattron(password_input_login, A_BOLD | COLOR_PAIR(10));
    box(password_input_login, 0, 0);
    wattroff(password_input_login, A_BOLD | COLOR_PAIR(10));
    wattron(submit_btn_login, A_BOLD | COLOR_PAIR(10));
    box(submit_btn_login, 0, 0);
    mvwprintw(submit_btn_login, 1, 2, "%-7s", "Submit");
    wattroff(submit_btn_login, A_BOLD | COLOR_PAIR(10));
    wattron(input_win_login, A_BOLD | COLOR_PAIR(4));
    box(input_win_login, 0, 0);
    wattroff(input_win_login, A_BOLD | COLOR_PAIR(4));
    mvwprintw(username_input_login, 1, 2, "%-30s", "Username: ");
    mvwprintw(password_input_login, 1, 2, "%-30s", "Password: ");
    mvwprintw(cancel_btn_login, 1, 2, "%-7s", "Cancel");
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
    wattron(input_win_login, A_BOLD | COLOR_PAIR(14));
    if (is_login)
    {
        mvwprintw(input_win_login, 1, 10, "%-35s", "  _                 _");
        mvwprintw(input_win_login, 2, 10, "%-35s", " | |               (_)");
        mvwprintw(input_win_login, 3, 10, "%-35s", " | |     ___   __ _ _ _ __");
        mvwprintw(input_win_login, 4, 10, "%-35s", " | |    / _ \\ / _` | | '_ \\");
        mvwprintw(input_win_login, 5, 10, "%-35s", " | |___| (_) | (_| | | | | |");
        mvwprintw(input_win_login, 6, 10, "%-35s", " \\_____/\\___/ \\__, |_|_| |_|");
        mvwprintw(input_win_login, 7, 10, "%-35s", "               __/ |");
        mvwprintw(input_win_login, 8, 10, "%-35s", "              |___/");
    }
    else
    {
        mvwprintw(input_win_login, 1, 10, "%-35s", " _____ _                        ");
        mvwprintw(input_win_login, 2, 10, "%-35s", "/  ___(_)                       ");
        mvwprintw(input_win_login, 3, 10, "%-35s", "\\ `--. _  __ _ _ __  _   _ _ __ ");
        mvwprintw(input_win_login, 4, 10, "%-35s", " `--. \\ |/ _` | '_ \\| | | | '_ \\");
        mvwprintw(input_win_login, 5, 10, "%-35s", "/\\__/ / | (_| | | | | |_| | |_) |");
        mvwprintw(input_win_login, 6, 10, "%-35s", "\\____/|_|\\__, |_| |_|\\__,_| .__/ ");
        mvwprintw(input_win_login, 7, 10, "%-35s", "          __/ |           | |    ");
        mvwprintw(input_win_login, 8, 10, "%-35s", "         |___/            |_|    ");
    }
    wattroff(input_win_login, A_BOLD | COLOR_PAIR(14));
    wrefresh(input_win_login);
}
WINDOW *get_target_win_login()
{
    int tbbx = getbegx(top_btn_login), tbby = getbegy(top_btn_login), tbbw = getmaxx(top_btn_login), tbbh = getmaxy(top_btn_login);
    int uibx = getbegx(username_input_login), uiby = getbegy(username_input_login), uibw = getmaxx(username_input_login), uibh = getmaxy(username_input_login);
    int pibx = getbegx(password_input_login), piby = getbegy(password_input_login), pibw = getmaxx(password_input_login), pibh = getmaxy(password_input_login);
    int sbbx = getbegx(submit_btn_login), sbby = getbegy(submit_btn_login), sbbw = getmaxx(submit_btn_login), sbbh = getmaxy(submit_btn_login);
    int cbbx = getbegx(cancel_btn_login), cbby = getbegy(cancel_btn_login), cbbw = getmaxx(cancel_btn_login), cbbh = getmaxy(cancel_btn_login);
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
        // noecho();
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
                input(1);
            }
            else if (target == password_input_login)
            {
                input(2);
            }
            else if (target == submit_btn_login)
            {
                success = is_login ? processLogin(username, password, message) : processSignup(username, password, message);
                if (success)
                {
                    del_login();
                    splashscreen();
                    break;
                }
                else
                {
                    wattr_on(input_win_login, A_BOLD | COLOR_PAIR(14), NULL);
                    mvwprintw(input_win_login, 10, 10, "%-35s", message);
                    wrefresh(input_win_login);
                    napms(2000);
                    wattr_off(input_win_login, A_BOLD | COLOR_PAIR(14), NULL);
                    mvwprintw(input_win_login, 10, 10, "%-35s", "                                   ");
                    wrefresh(input_win_login);
                }
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
