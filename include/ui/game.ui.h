#ifndef UI_GAME_H_
#define UI_GAME_H_
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "room.ui.h"
#include <locale.h>
// const char txt_cnt_signup[2][100] = {"Don't have an account?", "Sign up to play with us."};
// const char txt_cnt_login[2][100] = {"Have an account?", "Login and play now."};
char CARDTEMPLATE[54][10] = {"3♠", "3♣", "3♦", "3♥", "4♠", "4♣", "4♦", "4♥", "5♠", "5♣", "5♦", "5♥", "6♠", "6♣", "6♦", "6♥", "7♠", "7♣", "7♦", "7♥", "8♠", "8♣", "8♦", "8♥", "9♠", "9♣", "9♦", "9♥", "10♠", "10♣", "10♦", "10♥", "J♠", "J♣", "J♦", "J♥", "Q♠", "Q♣", "Q♦", "Q♥", "K♠", "K♣", "K♦", "K♥", "A♠", "A♣", "A♦", "A♥", "2♠", "2♣", "2♦", "2♥"};
char card_number[3], card_character[10];
int cardArray[13] = {0, 22, 31, 43, 50, 6, 7, 8, 9, 10, 11, 34, 13};
int numberOfCard = 13;
extern bool is_create;
// global variables
WINDOW *main_win_game;
WINDOW *top_win_game;
WINDOW *top_home_btn_game;
WINDOW *top_exit_btn_game;
WINDOW *input_win_game;
WINDOW *chat_win_game;
WINDOW *input_chat_game;
WINDOW *submit_btn_game;
WINDOW *cancel_btn_game;
WINDOW *send_btn_game;
WINDOW *card_win[13];
WINDOW *player[3];
WINDOW *show_card_win[13];
int card_choosing[13];
int start;
MEVENT m_event;
// prototypes
// implementation
void init_game();
void init_top_win_game();
void init_chat_win_game();
void listen_mouse_event_game();
WINDOW *get_target_win_game();
void del_game();
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void sortCard()
{
    for (int i = 0; i < numberOfCard - 1; i++)
        for (int j = numberOfCard - 1; j > i; j--)
            if (cardArray[j] < cardArray[j - 1])
            {
                swap(&cardArray[j], &cardArray[j - 1]);
            }
}
void deleteCard(int index)
{

    for (int i = index; i < 13; i++)
    {
        cardArray[i] = cardArray[i + 1];
        card_choosing[i] = card_choosing[i + 1];
    }

    numberOfCard--;
}
int number_card_choosing()
{
    int dem = 0;
    for (int i = 0; i < numberOfCard; i++)
    {
        dem += card_choosing[i] == 1 ? 1 : 0;
    }
    return dem;
}
void sendCard()
{
    int dem = 0;
    int start1 = getmaxx(input_win_game) / 2 - 5 * number_card_choosing() / 2 - 5;
    for (int i = 0; i < 10; i++)
    {
        mvwprintw(input_win_game, 13 + i, 20, "%80s", " ");
    }

    for (int i = 0; i < numberOfCard; i++)
    {
        if (card_choosing[i] != 0)
        {
            delwin(show_card_win[dem]);
            show_card_win[dem] = subwindow(input_win_game, 8, 12, 15, start1 + dem * 5);
            print_one_card(show_card_win[dem], cardArray[i]);
            dem++;
            deleteCard(i);
            i--;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        mvwprintw(input_win_game, getmaxy(input_win_game) - 17 + i, 2, "%110s", " ");
    }

    wrefresh(input_win_game);
    print_cards();
}
void init_game()
{
    // setlocale(LC_ALL, "");
    // wattroff(stdscr,)
    clear();
    refresh();
    main_win_game = stdscr;
    box(main_win_game, 0, 0);
    init_top_win_game();
    init_input_win_game();
    init_chat_win_game();
    refresh();
}
void init_top_win_game()
{
    top_win_game = subwindow(main_win_game, 5, getmaxx(main_win_game) / 3 * 2, 1, 1);
    top_home_btn_game = subwindow(top_win_game, 3, 18, 1, 3);
    top_exit_btn_game = subwindow(top_win_game, 3, 18, 1, getmaxx(top_win_game) - 21);

    box(top_win_game, 0, 0);
    box(top_home_btn_game, 0, 0);
    box(top_exit_btn_game, 0, 0);

    wbkgd(top_home_btn_game, COLOR_PAIR(4) | A_BOLD);
    wbkgd(top_exit_btn_game, COLOR_PAIR(6) | A_BOLD);
    wbkgd(top_win_game, COLOR_PAIR(1) | A_BOLD);

    wrefresh(top_home_btn_game);
    wrefresh(top_exit_btn_game);
    wrefresh(top_win_game);

    // mvwprintw(top_win_game, 2, 2, "%-40s", txt_cnt_signup[0]);
    // mvwprintw(top_win_game, 3, 2, "%-40s", txt_cnt_signup[1]);
    mvwprintw(top_home_btn_game, 1, 2, "%-13s", "Home");
    mvwprintw(top_exit_btn_game, 1, 2, "%-13s", "Exit");

    wattroff(top_home_btn_game, COLOR_PAIR(4) | A_BOLD);
    wbkgd(top_exit_btn_game, COLOR_PAIR(6) | A_BOLD);
    wbkgd(top_win_game, COLOR_PAIR(1) | A_BOLD);
    wrefresh(top_home_btn_game);
    wrefresh(top_exit_btn_game);
    wrefresh(top_win_game);
}
void init_input_win_game()
{
    input_win_game = subwindow(main_win_game, getmaxy(main_win_game) - 7, getmaxx(main_win_game) / 3 * 2, 6, 1);
    cancel_btn_game = subwindow(input_win_game, 3, 10, getmaxy(input_win_game) - 4, 20);
    submit_btn_game = subwindow(input_win_game, 3, 10, getmaxy(input_win_game) - 4, getmaxx(input_win_game) - 30);
    box(submit_btn_game, 0, 0);
    box(input_win_game, 0, 0);
    box(cancel_btn_game, 0, 0);
    mvwprintw(submit_btn_game, 1, 2, "%-7s", "Submit");
    mvwprintw(cancel_btn_game, 1, 2, "%-7s", "Cancel");

    wrefresh(submit_btn_game);
    wrefresh(cancel_btn_game);
    wrefresh(input_win_game);
    sortCard();
    print_cards();
    print_player();
}
void print_player_card(WINDOW *orig, int number)
{
    wattron(orig, COLOR_PAIR(5));
    // wattron(orig, A_STANDOUT);

    mvwprintw(orig, 1, 1, ".------.");
    mvwprintw(orig, 2, 1, "| .--. |");
    mvwprintw(orig, 3, 1, "| :/\\: |");
    mvwprintw(orig, 4, 1, "| (%2d) |", 10);
    mvwprintw(orig, 5, 1, "| '--' |");
    mvwprintw(orig, 6, 1, "`------'");
    // wattroff(orig, A_STANDOUT);

    wattroff(orig, COLOR_PAIR(5));
    box(orig, 0, 0);
    wrefresh(orig);
}
void print_player()
{

    mvwprintw(input_win_game, getmaxy(input_win_game) / 2 - 8, 8 - strlen("👤 Hoan") / 2, "👤 Hoan");
    mvwprintw(input_win_game, getmaxy(input_win_game) / 2 - 8, getmaxx(input_win_game) - 9 - strlen("👤 Tam") / 2, "👤 Tam");
    mvwprintw(input_win_game, 1, getmaxx(input_win_game) / 2 - strlen("👤 Truong") / 2, "👤 Truong");
    player[0] = subwindow(input_win_game, 8, 10, getmaxy(input_win_game) / 2 - 6, 3);
    player[1] = subwindow(input_win_game, 8, 10, getmaxy(input_win_game) / 2 - 6, getmaxx(input_win_game) - 14);
    player[2] = subwindow(input_win_game, 8, 10, 3, getmaxx(input_win_game) / 2 - 5);
    // box(player[0], 0, 0);
    // box(player[1], 0, 0);
    // box(player[2], 0, 0);
    print_player_card(player[0], 10);
    print_player_card(player[1], 10);
    print_player_card(player[2], 10);
    wrefresh(input_win_game);
}
void print_cards()
{
    start = getmaxx(input_win_game) / 2 - 5 * numberOfCard / 2 - 5;

    for (int i = 0; i < numberOfCard; i++)
    {
        delwin(card_win[i]);
        if (card_choosing[i] == 0)
        {
            card_win[i] = subwindow(input_win_game, 8, 12, getmaxy(input_win_game) - 15, start + i * 5);
        }
        else
        {
            card_win[i] = subwindow(input_win_game, 8, 12, getmaxy(input_win_game) - 17, start + i * 5);
        }
        print_one_card(card_win[i], cardArray[i]);
    }
    wrefresh(input_win_game);
}

void print_one_card(WINDOW *orig, int number)
{
    attron(A_STANDOUT);
    if (number > 27 && number < 32)
        strcpy(card_number, "10");
    else
        strncpy(card_number, CARDTEMPLATE[number], 1);
    if (number % 4 == 0)
    {
        strcpy(card_character, "♠");
        wattron(orig, COLOR_PAIR(5));
    }
    if (number % 4 == 1)
    {
        strcpy(card_character, "♣");
        wattron(orig, COLOR_PAIR(5));
    }
    if (number % 4 == 2)
    {
        strcpy(card_character, "♦");
        wattron(orig, COLOR_PAIR(9));
    }
    if (number % 4 == 3)
    {
        strcpy(card_character, "♥");
        wattron(orig, COLOR_PAIR(9));
    }
    mvwprintw(orig, 1, 0, " .--------.");
    mvwprintw(orig, 2, 0, " |%-2s.---. |", card_number);
    mvwprintw(orig, 3, 0, " |%s :/\\:  |", card_character);
    mvwprintw(orig, 4, 0, " |  (__)%s |", card_character);
    mvwprintw(orig, 5, 0, " |  '--'%-2s|", card_number);
    mvwprintw(orig, 6, 0, " `--------'");
    memset(card_number, 0, 3);
    memset(card_character, 0, 10);
    if (number % 4 < 2)
        wattroff(orig, COLOR_PAIR(5));
    else
        wattroff(orig, COLOR_PAIR(9));
    box(orig, 1, 1);
    attroff(A_STANDOUT);
    refresh();
}
void get_chat_message()
{
    char *message = (char *)malloc(sizeof(char) * 100);
    memset(message, 0, 100);
    mvwgetnstr(input_chat_game, 1, 1, message, 100);
    if (strlen(message) > 0)
    {
        mvwprintw(chat_win_game, getmaxy(chat_win_game) - 3, 2, "%s", message);
        wrefresh(chat_win_game);
    }
    free(message);
}
void show_chat_message(char *message)
{
    mvwprintw(chat_win_game, getmaxy(chat_win_game) - 3, 2, "%s", message);
    wrefresh(chat_win_game);
}
void init_chat_win_game()
{
    chat_win_game = subwindow(main_win_game, getmaxy(main_win_game) - 2, getmaxx(stdscr) / 3 - 1, 1, getmaxx(main_win_game) / 3 * 2 + 1);
    input_chat_game = subwindow(chat_win_game, 3, getmaxx(chat_win_game) - 15, getmaxy(chat_win_game) - 4, 2);
    send_btn_game = subwindow(chat_win_game, 3, 10, getmaxy(chat_win_game) - 4, getmaxx(input_chat_game) + 3);

    box(send_btn_game, 0, 0);
    box(chat_win_game, 0, 0);
    box(input_chat_game, 0, 0);
    mvwprintw(send_btn_game, 1, 2, "%-7s", "Send");

    mvwprintw(chat_win_game, 1, 10, "%-35s", " _____ _           _   ");
    mvwprintw(chat_win_game, 2, 10, "%-35s", "/  __ \\ |         | |  ");
    mvwprintw(chat_win_game, 3, 10, "%-35s", "| /  \\/ |__   __ _| |_ ");
    mvwprintw(chat_win_game, 4, 10, "%-35s", "| |   | '_ \\ / _` | __|");
    mvwprintw(chat_win_game, 5, 10, "%-35s", "| \\__/\\ | | | (_| | |_ ");
    mvwprintw(chat_win_game, 6, 10, "%-35s", " \\____/_| |_|\\__,_|\\__|");

    wrefresh(input_chat_game);
    wrefresh(send_btn_game);
    wrefresh(chat_win_game);
}
WINDOW *get_target_win_game()
{
    int tcbbx = getbegx(top_home_btn_game), tcbby = getbegy(top_home_btn_game), tcbbw = getmaxx(top_home_btn_game), tcbbh = getmaxy(top_home_btn_game);
    int tsbbx = getbegx(top_exit_btn_game), tsbby = getbegy(top_exit_btn_game), tsbbw = getmaxx(top_exit_btn_game), tsbbh = getmaxy(top_exit_btn_game);
    // int pibx = getbegx(password_input), piby = getbegy(password_input), pibw = getmaxx(password_input), pibh = getmaxy(password_input);
    int sbbx = getbegx(submit_btn_game), sbby = getbegy(submit_btn_game), sbbw = getmaxx(submit_btn_game), sbbh = getmaxy(submit_btn_game);
    int cbbx = getbegx(cancel_btn_game), cbby = getbegy(cancel_btn_game), cbbw = getmaxx(cancel_btn_game), cbbh = getmaxy(cancel_btn_game);
    int mx = m_event.x, my = m_event.y;
    if (mx >= tcbbx && mx <= tcbbx + tcbbw && my >= tcbby && my <= tcbby + tcbbh)
    {
        return top_home_btn_game;
    }
    if (mx >= tsbbx && mx <= tsbbx + tsbbw && my >= tsbby && my <= tsbby + tsbbh)
    {
        return top_exit_btn_game;
    }
    // if (mx >= pibx && mx <= pibx + pibw && my >= piby && my <= piby + pibh)
    // {
    //     return password_input;
    // }
    if (mx >= sbbx && mx <= sbbx + sbbw && my >= sbby && my <= sbby + sbbh)
    {
        return submit_btn_game;
    }
    if (mx >= cbbx && mx <= cbbx + cbbw && my >= cbby && my <= cbby + cbbh)
    {
        return cancel_btn_game;
    }
    return NULL;
}
void choose_card()
{
    int mx = m_event.x, my = m_event.y;
    int cardx = (mx - start - 1) / 5;
    // cardx = cardx > 12 ? 12 : cardx;
    if (mx > start && cardx <= 12 && cardx >= 0)
    {
        card_choosing[cardx] = !card_choosing[cardx];
        if (card_choosing[cardx] == 0)
        {
            mvwprintw(input_win_game, getmaxy(input_win_game) - 16, start + cardx * 5, "%12s", " ");
            mvwprintw(input_win_game, getmaxy(input_win_game) - 17, start + cardx * 5, "%12s", " ");
        }
        else
        {
            mvwprintw(input_win_game, getmaxy(input_win_game) - 8, start + cardx * 5, "%12s", " ");
            mvwprintw(input_win_game, getmaxy(input_win_game) - 9, start + cardx * 5, "%12s", " ");
        }
    }
    print_cards();
}

void del_game()
{
    // delwin(input_number_game);
    // delwin(password_input);
    delwin(submit_btn_game);
    delwin(cancel_btn_game);
    // delwin(input_win_game);
    delwin(top_home_btn_game);
    delwin(top_exit_btn_game);
    delwin(top_win_game);
    // delwin(main_win_game);
    refresh();
    // endwin();
}

void listen_mouse_event_game(void)
{
    WINDOW *target = NULL;
    int c;
    while (1)
    {
        // noecho();
        keypad(main_win_game, true);
        c = wgetch(main_win_game);
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
            choose_card();
            target = get_target_win_game();
            if (target == top_home_btn_game)
            {
                is_create = 1;
                // switch_top_win_game();
                // switch_input_win_game();
            }
            else if (target == top_exit_btn_game)
            {
                is_create = 0;
                // switch_top_win_game();
                // switch_input_win_game();
            }
            // else if (target == password_input)
            // {
            // 	input_password();
            // }
            else if (target == submit_btn_game)
            {
                sendCard();
                napms(150);
                // del_login();
            }
            else if (target == cancel_btn_game)
            {
                napms(100);
                del_game();
                break;
            }
        }
    }
}
#endif