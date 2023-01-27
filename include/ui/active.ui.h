#if !defined(UI_ACTIVE_H_)
#define UI_ACTIVE_H_
#include "login.ui.h"
WINDOW *active_win;
WINDOW *top_win;
WINDOW *content_win;
WINDOW *username_input_win;
WINDOW *password_input_win;
WINDOW *activation_input_win;
WINDOW *submit_btn_win;
WINDOW *cancel_btn_win;
void initActiveUI()
{
    active_win = stdscr;
    attron(COLOR_PAIR(15));
    box(active_win, 0, 0);
    attroff(COLOR_PAIR(15));
    init_top_win();
    init_content_win();
}

void init_top_win()
{
    top_win = derwin(active_win, 10, COLS / 2.5, LINES / 2 - 10 * 2, COLS / 2 - COLS / (2.5 * 2));
    wattron(top_win, COLOR_PAIR(15) | A_STANDOUT);
    box(top_win, 0, 0);
    // mvwprintw(top_win, 1, 1, "Active");
    wattroff(top_win, COLOR_PAIR(15) | A_STANDOUT);
    init_logo();
    wrefresh(top_win);
}

void init_content_win()
{
    content_win = derwin(active_win, 30, COLS / 2.5, LINES / 2 - 10, COLS / 2 - COLS / (2.5 * 2));
    wattron(content_win, COLOR_PAIR(15));
    box(content_win, 0, 0);
    wattroff(content_win, COLOR_PAIR(15));
    init_username_input_win();
    // init_password_input_win();
    // init_activation_input_win();
    // init_submit_btn_win();
    // init_cancel_btn_win();
    touchwin(content_win);
    wrefresh(content_win);
}
void init_logo()
{
    wattron(top_win, COLOR_PAIR(15));
    mvwprintw(top_win, 4, (getmaxx(top_win) - 46) / 2, "╔═╗╔═╗╔╦╗╦╦  ╦╔═╗╔╦╗╔═╗  ╔═╗╔═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗");
    mvwprintw(top_win, 5, (getmaxx(top_win) - 46) / 2, "╠═╣║   ║ ║╚╗╔╝╠═╣ ║ ║╣   ╠═╣║  ║  ║ ║║ ║║║║ ║");
    mvwprintw(top_win, 6, (getmaxx(top_win) - 46) / 2, "╩ ╩╚═╝ ╩ ╩ ╚╝ ╩ ╩ ╩ ╚═╝  ╩ ╩╚═╝╚═╝╚═╝╚═╝╝╚╝ ╩");
    wattroff(top_win, COLOR_PAIR(15));
    wrefresh(top_win);
}
void init_username_input_win()
{
    username_input_win = derwin(content_win, 3, COLS - 4, 1, 2);
    wattron(username_input_win, COLOR_PAIR(2));
    box(username_input_win, 0, 0);
    mvwprintw(username_input_win, 1, 1, "Username");
    wattroff(username_input_win, COLOR_PAIR(2));
    wrefresh(username_input_win);
}

void init_password_input_win()
{
    password_input_win = derwin(content_win, 3, COLS - 4, 5, 2);
    wattron(password_input_win, COLOR_PAIR(2));
    box(password_input_win, 0, 0);
    mvwprintw(password_input_win, 1, 1, "Password");
    wattroff(password_input_win, COLOR_PAIR(2));
    wrefresh(password_input_win);
}

void init_activation_input_win()
{
    activation_input_win = derwin(content_win, 3, COLS - 4, 9, 2);
    wattron(activation_input_win, COLOR_PAIR(2));
    box(activation_input_win, 0, 0);
    mvwprintw(activation_input_win, 1, 1, "Activation Code");
    wattroff(activation_input_win, COLOR_PAIR(2));
    wrefresh(activation_input_win);
}

void init_submit_btn_win()
{
    submit_btn_win = derwin(content_win, 3, COLS / 2 - 4, 13, 2);
    wattron(submit_btn_win, COLOR_PAIR(3));
    box(submit_btn_win, 0, 0);
    mvwprintw(submit_btn_win, 1, 1, "Submit");
    wattroff(submit_btn_win, COLOR_PAIR(3));
    wrefresh(submit_btn_win);
}

void init_cancel_btn_win()
{
    cancel_btn_win = derwin(content_win, 3, COLS / 2 - 4, 13, COLS / 2 + 2);
    wattron(cancel_btn_win, COLOR_PAIR(3));
    box(cancel_btn_win, 0, 0);
    mvwprintw(cancel_btn_win, 1, 1, "Cancel");
    wattroff(cancel_btn_win, COLOR_PAIR(3));
    wrefresh(cancel_btn_win);
}

void activeUI()
{
    initActiveUI();
    int ch;
    while ((ch = getch()) != KEY_F(1))
    {
        switch (ch)
        {
        case KEY_DOWN:
            break;
        case KEY_UP:
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        case KEY_ENTER:
            break;
        default:
            break;
        }
    }
}

#endif // UI_ACTIVE_H_
