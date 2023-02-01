#if !defined(GAME_UI_TEST_H)
#define GAME_UI_TEST_H
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include <locale.h>
#include "tienlen.h"
#include "player.h"
#include <pthread.h>
#include "game.h"

// mock
//
static CurrentRoom currentRoom = {
    .id = 0,
    .roomName = {0},
    .maxPlayer = 0,
    .currentPlayer = 0,
    .players = {0},
    .cardsInHand = {0},
    .cardsOnTableSize = 0,
    .cardsOnTable = {0},
    .isPlaying = false};

extern const char CARD_TEMPLATE[][10];
extern const char CARD_SUIT[][4];
extern const char CARD_VALUE[][2];

static WINDOW *mainWin = NULL;
// top
static WINDOW *topWin = NULL;
static WINDOW *exitBtn = NULL;
// game
static WINDOW *gameWin = NULL;
static WINDOW *playerAvatar[MAX_PLAYER - 1] = {NULL};
static WINDOW *cardInHand[CARD_SIZE / MAX_PLAYER] = {NULL};
static WINDOW *cardOnTable[CARD_SIZE / MAX_PLAYER] = {NULL};
static WINDOW *okBtn = NULL;
// chat
static WINDOW *chatWin = NULL;
static WINDOW *chatInput = NULL;
static WINDOW *sendBtn = NULL;
// mouse
static MEVENT mouseEvent = {0};
//
// mock
void mock()
{
    // currentRoom.isPlaying = true;
    // for (int i = 0; i < 13; i++)
    // {
    //     currentRoom.cardsInHand[i] = createCard(HEART, THREE);
    // }
    // currentRoom.currentPlayer = 4;
    // currentRoom.cardsOnTableSize = 5;
    // for (int i = 0; i < 5; i++)
    // {
    //     currentRoom.cardsOnTable[i] = createCard(CLUB, FOUR);
    // }

    // for (int i = 0; i < 4; i++)
    // {
    //     strcpy(currentRoom.players[i].name, "son");
    //     currentRoom.players[i].cardSize = 13 - i;
    // }
}
//
static int cardInHandSize = 0;
void init_game(char *);
static void render();
static void render_top();
static void render_game();
static void render_chat();
static void render_card_in_hand();
static void render_card(WINDOW *cardWin, Card card);
static void render_card_on_table();
static void render_player();
static void render_ok_btn();
static void render_exit_btn();
static void render_chat_input();
static void render_send_btn();
static void render_chat_mess();
static WINDOW *get_target_win();
void listen_mouse_game();
void destroy_game();
static void *render_game_when_recv_res();
void init_game(char *curUser)
{
    strcpy(currentRoom.players[0].name, curUser);
    clear();
    refresh();
    mainWin = stdscr;
    box(mainWin, 0, 0);
    mock();
    render();
    refresh();
}
void render()
{
    render_top();
    render_game();
    render_chat();
}
void render_top()
{
    topWin = derwin(mainWin, 5, getmaxx(mainWin) / 3 * 2, 1, 1);
    box(topWin, 0, 0);
    wbkgd(topWin, COLOR_PAIR(1) | A_BOLD);
    render_exit_btn();
    touchwin(topWin);
    wrefresh(topWin);
}
void render_game()
{
    gameWin = derwin(mainWin, getmaxy(mainWin) - 7, getmaxx(mainWin) / 3 * 2, 6, 1);
    box(gameWin, 0, 0);
    render_card_in_hand();
    render_card_on_table();
    render_player();
    render_ok_btn();
    // touchwin(gameWin);
    // wrefresh(gameWin);
}
void render_chat()
{
    chatWin = derwin(mainWin, getmaxy(mainWin) - 2, getmaxx(mainWin) / 3 - 1, 1, getmaxx(mainWin) / 3 * 2 + 1);
    box(chatWin, 0, 0);

    mvwprintw(chatWin, 1, 10, "%-35s", " _____ _           _   ");
    mvwprintw(chatWin, 2, 10, "%-35s", "/  __ \\ |         | |  ");
    mvwprintw(chatWin, 3, 10, "%-35s", "| /  \\/ |__   __ _| |_ ");
    mvwprintw(chatWin, 4, 10, "%-35s", "| |   | '_ \\ / _` | __|");
    mvwprintw(chatWin, 5, 10, "%-35s", "| \\__/\\ | | | (_| | |_ ");
    mvwprintw(chatWin, 6, 10, "%-35s", " \\____/_| |_|\\__,_|\\__|");

    render_chat_input();
    render_chat_mess();
    render_send_btn();
    touchwin(chatWin);
    wrefresh(chatWin);
}
void render_card_in_hand()
{
    int cardInHandNum = currentRoom.players[0].cardSize;
    int start = getmaxx(gameWin) / 2 - 5 * cardInHandNum / 2 - 5;
    bool *cardsChoosed = currentRoom.cardsChoosed;
    clear_card_in_hand();
    for (int i = 0; i < cardInHandNum; i++)
    {
        cardInHand[i] = derwin(gameWin, 8, 12, getmaxy(gameWin) - (cardsChoosed[i] ? 17 : 15), start + 5 * i);
        render_card(cardInHand[i], currentRoom.cardsInHand[i]);
    }
}
void render_card(WINDOW *cardWin, Card card)
{
    char *suit = CARD_SUIT[card.suit];
    char *value = CARD_VALUE[card.value];
    attron(A_STANDOUT);
    if (card.suit == HEART || card.suit == DIAMOND)
    {
        wattron(cardWin, COLOR_PAIR(9));
    }
    else
    {
        wattron(cardWin, COLOR_PAIR(5));
    }
    mvwprintw(cardWin, 1, 0, " .--------.");
    mvwprintw(cardWin, 2, 0, " |%-2s.---. |", value);
    mvwprintw(cardWin, 3, 0, " |%s :/\\:  |", suit);
    mvwprintw(cardWin, 4, 0, " |  (__)%s |", suit);
    mvwprintw(cardWin, 5, 0, " |  '--'%-2s|", value);
    mvwprintw(cardWin, 6, 0, " `--------'");
    wattroff(cardWin, COLOR_PAIR(5) | COLOR_PAIR(9));
    box(cardWin, 1, 1);
    attroff(A_STANDOUT);
    wrefresh(cardWin);
}

void render_card_on_table()
{
    int cardOnTableNum = currentRoom.cardsOnTableSize;
    int start = getmaxx(gameWin) / 2 - 5 * cardOnTableNum / 2 - 5;
    clear_card_on_table();
    for (int i = 0; i < cardOnTableNum; i++)
    {
        cardOnTable[i] = derwin(gameWin, 8, 12, 20, start + 5 * i);
        render_card(cardOnTable[i], currentRoom.cardsOnTable[i]);
    }
}
void clear_card_on_table()
{
    for (int i = 0; i < CARD_SIZE / MAX_PLAYER; i++)
    {
        wclear(cardOnTable[i]);
        wrefresh(cardOnTable[i]);
        delwin(cardOnTable[i]);
        cardOnTable[i] = NULL;
    }
}
void clear_card_in_hand()
{
    for (int i = 0; i < CARD_SIZE / MAX_PLAYER; i++)
    {
        wclear(cardInHand[i]);
        wrefresh(cardInHand[i]);
        delwin(cardInHand[i]);
        cardInHand[i] = NULL;
    }
}
void render_player()
{
    int playerNum = currentRoom.currentPlayer;
    int playerSize = currentRoom.currentPlayer;
    Player *players = currentRoom.players;
    clear_player();
    if (playerSize > 1)
    {
        playerAvatar[0] = derwin(gameWin, 8, 10, getmaxy(gameWin) / 2 - 6, getmaxx(gameWin) - 13);
        mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, getmaxx(gameWin) - 9 - (strlen("👤 ") + strlen(players[1].name)) / 2, "%s %s", "👤", players[1].name);
        render_player_avatar(playerAvatar[0], players[1].cardSize);
    }
    if (playerSize > 2)
    {
        playerAvatar[1] = derwin(gameWin, 8, 10, 3, getmaxx(gameWin) / 2 - 5);
        mvwprintw(gameWin, 1, getmaxx(gameWin) / 2 - (strlen("👤 ") + strlen(players[2].name)) / 2, "%s %s", "👤", players[2].name);
        render_player_avatar(playerAvatar[1], players[2].cardSize);
    }
    if (playerSize > 3)
    {
        playerAvatar[2] = derwin(gameWin, 8, 10, getmaxy(gameWin) / 2 - 6, 3);
        mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, 8 - (strlen("👤 ") + strlen(players[3].name)) / 2, "%s %s", "👤", players[3].name);
        render_player_avatar(playerAvatar[2], players[3].cardSize);
    }
    touchwin(gameWin);
    wrefresh(gameWin);
}
void clear_player()
{
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        wclear(playerAvatar[i]);
        wrefresh(playerAvatar[i]);
        delwin(playerAvatar[i]);
        playerAvatar[i] = NULL;
    }
    mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, 8 - 20 / 2, "%s", "");
    mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, getmaxx(gameWin) - 9 - 20 / 2, "%s", "");
    mvwprintw(gameWin, 1, getmaxx(gameWin) / 2 - 20 / 2, "%s", "");
    wrefresh(gameWin);
}
void render_player_avatar(WINDOW *orig, int cardSize)
{
    wattron(orig, COLOR_PAIR(5));

    mvwprintw(orig, 1, 1, ".------.");
    mvwprintw(orig, 2, 1, "| .--. |");
    mvwprintw(orig, 3, 1, "| :/\\: |");
    mvwprintw(orig, 4, 1, "| (%2d) |", cardSize);
    mvwprintw(orig, 5, 1, "| '--' |");
    mvwprintw(orig, 6, 1, "`------'");

    wattroff(orig, COLOR_PAIR(5));
    box(orig, 0, 0);
    wrefresh(orig);
}
void render_ok_btn()
{
    // bool isPlaying = currentRoom.isPlaying;
    okBtn = derwin(gameWin, 3, 10, getmaxy(gameWin) - 5, getmaxx(gameWin) / 2 - 5);
    wbkgd(okBtn, COLOR_PAIR(4));
    wattron(okBtn, A_BOLD);
    mvwprintw(okBtn, 1, 3, currentRoom.isPlaying ? "PLAY" : "OK");
    wattroff(okBtn, A_BOLD);
    box(okBtn, 0, 0);
    wrefresh(okBtn);
}
void render_exit_btn()
{
    exitBtn = derwin(topWin, 3, 18, 1, 3);
    box(exitBtn, 0, 0);
    wbkgd(exitBtn, COLOR_PAIR(4) | A_BOLD);
    mvwprintw(exitBtn, 1, 4, "%-13s", "EXIT");
    wrefresh(exitBtn);
}
void render_chat_input()
{
    chatInput = derwin(chatWin, 3, getmaxx(chatWin) - 15, getmaxy(chatWin) - 4, 2);
    box(chatInput, 0, 0);
    // wrefresh(chatInput);
}
void render_chat_mess()
{
    // int start = 1;
    // for (int i = 0; i < currentRoom.chatSize; i++)
    // {
    //     mvwprintw(chatWin, start, 2, "%s", currentRoom.chat[i]);
    //     start += 2;
    // }
    // wrefresh(chatWin);
}
void render_send_btn()
{
    sendBtn = subwindow(chatWin, 3, 10, getmaxy(chatWin) - 4, getmaxx(chatInput) + 3);
    box(sendBtn, 0, 0);
    wbkgd(sendBtn, COLOR_PAIR(4) | A_BOLD);
    mvwprintw(sendBtn, 1, 3, "%-5s", "SEND");
    wrefresh(sendBtn);
}
void choose_card()
{
    int mx = mouseEvent.x, my = mouseEvent.y;
    int cardInHandNum = currentRoom.players[0].cardSize;
    int start = getmaxx(gameWin) / 2 - 5 * cardInHandNum / 2 - 5;
    int cardx = (mx - start - 1) / 5;
    // cardx = cardx > 12 ? 12 : cardx;
    bool *choosed_card = currentRoom.cardsChoosed;
    if (mx > start && cardx <= 12 && cardx >= 0 && my > getmaxy(gameWin) - 10 && my < getmaxy(gameWin))
    {
        beep();
        choosed_card[cardx] = !choosed_card[cardx];
    }
    render_card_in_hand();
}
WINDOW *get_target_win()
{
    int mx = mouseEvent.x, my = mouseEvent.y;
    int exitBtnX = getbegx(exitBtn), exitBtnY = getbegy(exitBtn), exitBtnW = getmaxx(exitBtn), exitBtnH = getmaxy(exitBtn);
    int okBtnX = getbegx(okBtn), okBtnY = getbegy(okBtn), okBtnW = getmaxx(okBtn), okBtnH = getmaxy(okBtn);
    int sendBtnX = getbegx(sendBtn), sendBtnY = getbegy(sendBtn), sendBtnW = getmaxx(sendBtn), sendBtnH = getmaxy(sendBtn);
    int chatInputX = getbegx(chatInput), chatInputY = getbegy(chatInput), chatInputW = getmaxx(chatInput), chatInputH = getmaxy(chatInput);
    if (mx >= exitBtnX && mx <= exitBtnX + exitBtnW && my >= exitBtnY && my <= exitBtnY + exitBtnH)
    {
        return exitBtn;
    }
    if (mx >= okBtnX && mx <= okBtnX + okBtnW && my >= okBtnY && my <= okBtnY + okBtnH)
    {
        return okBtn;
    }
    if (mx >= sendBtnX && mx <= sendBtnX + sendBtnW && my >= sendBtnY && my <= sendBtnY + sendBtnH)
    {
        return sendBtn;
    }
    if (mx >= chatInputX && mx <= chatInputX + chatInputW && my >= chatInputY && my <= chatInputY + chatInputH)
    {
        return chatInput;
    }
    return NULL;
}
void listen_mouse_game()
{
    WINDOW *target = NULL;
    int c;
    pthread_t thread;
    pthread_create(&thread, NULL, &render_game_when_recv_res, NULL);
    pthread_detach(thread);
    while (true)
    {
        keypad(mainWin, true);
        c = wgetch(mainWin);
        if (c != KEY_MOUSE || getmouse(&mouseEvent) != OK)
        {
            continue;
        }
        if (!(mouseEvent.bstate & BUTTON1_CLICKED))
        {
            continue;
        }
        choose_card();
        target = get_target_win();
        if (target == NULL)
        {
            continue;
        }
        // top win
        if (target == exitBtn)
        {
            pthread_cancel(thread);
            napms(100);
            destroy_game();
            break;
        }
        // game win
        if (target == okBtn)
        {
            if (currentRoom.isPlaying)
            {
                currentRoom.isPlaying = false;
                beep();
                // play game
            }
            else
            {
                currentRoom.isPlaying = true;
                // start game
            }
            continue;
        }

        // chat win
        if (target == sendBtn)
        {
            beep();
            // send message
            continue;
        }
        if (target == chatInput)
        {
            beep();
            // input message
            continue;
        }
    }
}
void destroy_game()
{
    // delwin(exitBtn);
    // delwin(topWin);
    // del
    clear();
    refresh();
    // endwin();
}
void *render_game_when_recv_res()
{
    Res res;
    while (true)
    {
        recvResponse(clientfd, &res);
        switch (res.type)
        {
        case UPDATE_ROOM_RES:
            /* code */
            handleUpdateRoom(&currentRoom, res.data.updateRoom);
            render_player();
            break;

        default:
            break;
        }
    }
}
#endif // GAME_UI_TEST_H
