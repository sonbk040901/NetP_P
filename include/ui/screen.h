#ifndef SCREEN_H_
#define SCREEN_H_
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"
// prototype
// defination
void splashscreen(void);
WINDOW *subwindow(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
void splashscreen(void)
{
    int i;
    char str[] = "Welcome to the game";
    char loadstring[] = "Loading...";
    clear();
    refresh();
    attron(A_BOLD | COLOR_PAIR(10));
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 10, getmaxx(stdscr) / 2 - 100 / 2, " _    _      _                            _          _   _                                       ");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 9, getmaxx(stdscr) / 2 - 100 / 2, "| |  | |    | |                          | |        | | | |                                      ");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 8, getmaxx(stdscr) / 2 - 100 / 2, "| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   | |_| |__   ___    __ _  __ _ _ __ ___   ___ ");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 7, getmaxx(stdscr) / 2 - 100 / 2, "| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | __| '_ \\ / _ \\  / _` |/ _` | '_ ` _ \\ / _ \\");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 6, getmaxx(stdscr) / 2 - 100 / 2, "\\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |_| | | |  __/ | (_| | (_| | | | | | |  __/");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 5, getmaxx(stdscr) / 2 - 100 / 2, " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \\__|_| |_|\\___|  \\__, |\\__,_|_| |_| |_|\\___|");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 4, getmaxx(stdscr) / 2 - 100 / 2, "                                                                       __/ |                     ");
    mvwprintw(stdscr, getmaxy(stdscr) / 2 - 3, getmaxx(stdscr) / 2 - 100 / 2, "                                                                      |___/                      ");
    attroff(A_BOLD | COLOR_PAIR(10));
    attron(A_BOLD | COLOR_PAIR(12));
    mvprintw(getmaxy(stdscr) / 2 + 1, getmaxx(stdscr) / 2 - strlen(loadstring) / 2, loadstring);
    attroff(COLOR_PAIR(12));
    attron(A_BOLD | COLOR_PAIR(11));
    refresh();
    for (i = 0; i < 97; i++)
    {
        attron(A_STANDOUT);
        mvaddch(getmaxy(stdscr) / 2, i + getmaxx(stdscr) / 2 - 50, ' ');
        mvaddch(getmaxy(stdscr) / 2 + 1, i + getmaxx(stdscr) / 2 - 50, ' ');
        mvaddch(getmaxy(stdscr) / 2 + 2, i + getmaxx(stdscr) / 2 - 50, ' ');
        napms(10);
        refresh();
    }
    attroff(A_STANDOUT);
    attroff(A_BOLD | COLOR_PAIR(11));
    attroff(A_BOLD | COLOR_PAIR(12));
    refresh();
}
WINDOW *subwindow(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x)
{
    WINDOW *win;
    int x = getbegx(orig) + begin_x;
    int y = getbegy(orig) + begin_y;
    win = subwin(orig, nlines, ncols, y, x);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}
#endif // SCREEN_H_