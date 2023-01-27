#if !defined(UI_ACTIVE_H_)
#define UI_ACTIVE_H_
#include "login.ui.h"
#include "active.h"
WINDOW *active_win;
WINDOW *top_win;
WINDOW *content_win;
WINDOW *username_input_win;
WINDOW *password_input_win;
WINDOW *activation_input_win;
WINDOW *submit_btn_win;
WINDOW *cancel_btn_win;
extern char username[100];
extern char password[100];
char activation_code[100];
void initActiveUI()
{
    initscr();
    active_win = stdscr;
    attron(COLOR_PAIR(15));
    box(active_win, 0, 0);
    attroff(COLOR_PAIR(15));
    init_top_win_active();
    init_content_win_active();
}

void init_top_win_active()
{
    top_win = derwin(active_win, 10, COLS / 4, LINES / 2 - 10 * 2, COLS / 2 - COLS / (4 * 2));
    wattron(top_win, COLOR_PAIR(15) | A_STANDOUT);
    box(top_win, 0, 0);
    // mvwprintw(top_win, 1, 1, "Active");
    wattroff(top_win, COLOR_PAIR(15) | A_STANDOUT);
    init_logo_active();
    wrefresh(top_win);
}

void init_content_win_active()
{
    content_win = derwin(active_win, 30, COLS / 4, LINES / 2 - 10, COLS / 2 - COLS / (4 * 2));
    wattron(content_win, COLOR_PAIR(15));
    box(content_win, 0, 0);
    wattroff(content_win, COLOR_PAIR(15));
    init_username_input_win_active();
    init_password_input_win_active();
    init_activation_input_win_active();
    init_submit_btn_win_active();
    init_cancel_btn_win_active();
    // touchwin(content_win);
    wrefresh(content_win);
}
void init_logo_active()
{
    wattron(top_win, COLOR_PAIR(15));
    mvwprintw(top_win, 4, (getmaxx(top_win) - 46) / 2, "╔═╗╔═╗╔╦╗╦╦  ╦╔═╗╔╦╗╔═╗  ╔═╗╔═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗");
    mvwprintw(top_win, 5, (getmaxx(top_win) - 46) / 2, "╠═╣║   ║ ║╚╗╔╝╠═╣ ║ ║╣   ╠═╣║  ║  ║ ║║ ║║║║ ║");
    mvwprintw(top_win, 6, (getmaxx(top_win) - 46) / 2, "╩ ╩╚═╝ ╩ ╩ ╚╝ ╩ ╩ ╩ ╚═╝  ╩ ╩╚═╝╚═╝╚═╝╚═╝╝╚╝ ╩");
    wattroff(top_win, COLOR_PAIR(15));
    wrefresh(top_win);
}
void init_username_input_win_active()
{
    int maxx = getmaxx(content_win);
    int maxy = getmaxy(content_win);
    username_input_win = derwin(content_win, 3, maxx - 10, 4, 5);
    wattron(username_input_win, COLOR_PAIR(10));
    box(username_input_win, 0, 0);
    wattroff(username_input_win, COLOR_PAIR(10));
    mvwprintw(username_input_win, 1, 2, "Username:");
    wrefresh(username_input_win);
}

void init_password_input_win_active()
{
    int maxx = getmaxx(content_win);
    int maxy = getmaxy(content_win);
    password_input_win = derwin(content_win, 3, maxx - 10, 8, 5);
    wattron(password_input_win, COLOR_PAIR(10));
    box(password_input_win, 0, 0);
    wattroff(password_input_win, COLOR_PAIR(10));
    mvwprintw(password_input_win, 1, 2, "Password:");
    wrefresh(password_input_win);
}

void init_activation_input_win_active()
{
    int maxx = getmaxx(content_win);
    int maxy = getmaxy(content_win);
    activation_input_win = derwin(content_win, 3, maxx - 10, 12, 5);
    wattron(activation_input_win, COLOR_PAIR(10));
    box(activation_input_win, 0, 0);
    wattroff(activation_input_win, COLOR_PAIR(10));
    mvwprintw(activation_input_win, 1, 2, "Activation Code:");
    wrefresh(activation_input_win);
}

void init_submit_btn_win_active()
{
    submit_btn_win = derwin(content_win, 3, 15, 18, 10);
    wattron(submit_btn_win, COLOR_PAIR(11));
    box(submit_btn_win, 0, 0);
    mvwprintw(submit_btn_win, 1, (15 - 9) / 2, "Activate");
    wattroff(submit_btn_win, COLOR_PAIR(11));
    wrefresh(submit_btn_win);
}

void init_cancel_btn_win_active()
{
    cancel_btn_win = derwin(content_win, 3, 15, 18, 30);
    box(cancel_btn_win, 0, 0);
    mvwprintw(cancel_btn_win, 1, (15 - 7) / 2, "Cancel");
    wrefresh(cancel_btn_win);
}

void destroy_active()
{
    delwin(top_win);
    delwin(username_input_win);
    delwin(password_input_win);
    delwin(activation_input_win);
    delwin(submit_btn_win);
    delwin(cancel_btn_win);
    delwin(active_win);
    delwin(content_win);
    // delwin(active_win);
    clear();
    touchwin(active_win);
    wrefresh(active_win);
}
WINDOW *get_target_win_active(MEVENT mouse)
{
    int uibx = getbegx(username_input_win), uiby = getbegy(username_input_win), uibw = getmaxx(username_input_win), uibh = getmaxy(username_input_win);
    int pibx = getbegx(password_input_win), piby = getbegy(password_input_win), pibw = getmaxx(password_input_win), pibh = getmaxy(password_input_win);
    int aibx = getbegx(activation_input_win), aiby = getbegy(activation_input_win), aibw = getmaxx(activation_input_win), aibh = getmaxy(activation_input_win);
    int sbx = getbegx(submit_btn_win), sby = getbegy(submit_btn_win), sbw = getmaxx(submit_btn_win), sbh = getmaxy(submit_btn_win);
    int cbx = getbegx(cancel_btn_win), cby = getbegy(cancel_btn_win), cbw = getmaxx(cancel_btn_win), cbh = getmaxy(cancel_btn_win);
    int x = mouse.x, y = mouse.y;
    if (x >= uibx && x <= uibx + uibw && y >= uiby && y <= uiby + uibh)
    {
        return username_input_win;
    }
    else if (x >= pibx && x <= pibx + pibw && y >= piby && y <= piby + pibh)
    {
        return password_input_win;
    }
    else if (x >= aibx && x <= aibx + aibw && y >= aiby && y <= aiby + aibh)
    {
        return activation_input_win;
    }
    else if (x >= sbx && x <= sbx + sbw && y >= sby && y <= sby + sbh)
    {
        return submit_btn_win;
    }
    else if (x >= cbx && x <= cbx + cbw && y >= cby && y <= cby + cbh)
    {
        return cancel_btn_win;
    }
    else
    {
        return NULL;
    }
}
void input_username()
{
    mousemask(0, NULL);
    curs_set(true);
    echo();
    mvwprintw(username_input_win, 1, 12, "%-20s", "");
    mvwscanw(username_input_win, 1, 12, "%s", username);
    wrefresh(username_input_win);
    curs_set(false);
    mousemask(ALL_MOUSE_EVENTS, NULL);
}
void input_password()
{
    mousemask(0, NULL);
    curs_set(true);
    echo();
    mvwprintw(password_input_win, 1, 12, "%-20s", "");
    wrefresh(password_input_win);
    mvwscanw(password_input_win, 1, 12, "%s", password);
    curs_set(false);
    for (int i = 0; i < strlen(password); i++)
    {
        mvwprintw(password_input_win, 1, 12 + i, "*");
        wrefresh(password_input_win);
        napms(20);
    }
    mousemask(ALL_MOUSE_EVENTS, NULL);
}

void input_activation()
{
    mousemask(0, NULL);
    curs_set(true);
    echo();
    mvwprintw(activation_input_win, 1, 19, "%-20s", "");
    mvwscanw(activation_input_win, 1, 19, "%s", activation_code);
    wrefresh(activation_input_win);
    curs_set(false);
    mousemask(ALL_MOUSE_EVENTS, NULL);
}
void activeUI()
{
    initActiveUI();
    int ch;
    MEVENT mouse;
    WINDOW *target_win;
    char message[100];
    while (true)
    {
        keypad(active_win, true);
        ch = wgetch(active_win);
        if (ch != KEY_MOUSE)
        {
            continue;
        }
        if (getmouse(&mouse) != OK)
            continue;

        target_win = get_target_win_active(mouse);
        if (target_win == NULL)
        {
            beep();
            continue;
        }
        if (target_win == username_input_win)
        {
            input_username();
            continue;
        }
        if (target_win == password_input_win)
        {
            /* code */
            input_password();
            continue;
        }
        if (target_win == activation_input_win)
        {
            /* code */
            input_activation();
            continue;
        }
        if (target_win == submit_btn_win)
        {
            mvwprintw(content_win, 16, 10, "%40s", "");
            if (processActive(username, password, activation_code, message))
            {
                mvwprintw(content_win, 16, 10, "%s", message);
                wrefresh(content_win);
                napms(2000);
                destroy_active();
                break;
            }
            else
            {
                mvwprintw(content_win, 16, 10, "%s", message);
                wrefresh(content_win);
                continue;
            }
        }
        if (target_win == cancel_btn_win)
        {
            /* code */
            destroy_active();
            break;
        }
    }
}

#endif // UI_ACTIVE_H_
