#ifndef INIT_H_
#define INIT_H_
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#define SCR_MAX_SIZE_X 140
#define SCR_MAX_SIZE_Y 42
// prototypes
void init_colors();
void init_curses();
// implementation
void init_curses()
{
    setlocale(LC_ALL, "");
    nocbreak();
    initscr();
    init_colors();
}
void init_colors()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(8, COLOR_BLACK, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_WHITE);
    init_pair(10, COLOR_CYAN, COLOR_BLACK);
    init_pair(11, COLOR_BLUE, COLOR_BLACK);
    init_pair(12, COLOR_YELLOW, COLOR_BLACK);
    init_pair(13, COLOR_WHITE, COLOR_BLACK);
    init_pair(14, COLOR_GREEN, COLOR_BLACK);
    init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(16, COLOR_RED, COLOR_BLACK);
    init_pair(17, COLOR_RED, COLOR_CYAN);
}

void destroy_curses()
{
    delwin(stdscr);
    refresh();
    endwin();
}
#endif