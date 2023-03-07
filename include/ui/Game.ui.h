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
    .owner = false,
    .players = {0},
    .cardsInHand = {0},
    .cardsOnTableSize = 0,
    .cardsOnTable = {0},
    .isPlaying = false,
    .chatMessSize = 0,
    .turn = -1,
};
extern const char CARD_TEMPLATE[][10];
extern const char CARD_SUIT[][4];
extern const char CARD_VALUE[][2];

static WINDOW *mainWin = NULL;
// top
static WINDOW *topWin = NULL;
static WINDOW *exitBtn = NULL;
static WINDOW *roomName = NULL;
static WINDOW *point = NULL;
// game
static WINDOW *gameWin = NULL;
static WINDOW *playerAvatar[MAX_PLAYER - 1] = {NULL};
static WINDOW *cardInHand[CARD_SIZE / MAX_PLAYER] = {NULL};
static WINDOW *cardOnTable[CARD_SIZE / MAX_PLAYER] = {NULL};
static WINDOW *okBtn = NULL;
static WINDOW *cancelBtn = NULL;
// chat
static WINDOW *chatWin = NULL;
static WINDOW *chatInput = NULL;
static WINDOW *sendBtn = NULL;
// mouse
static MEVENT mouseEvent = {0};
//
bool isFocused = true;
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
void init_game(char *, char *);
static void render();
static void render_top();
static void render_point();
static void render_game();
static void render_chat();
static void render_card_in_hand();
static void render_card(WINDOW *cardWin, Card card);
static void render_card_on_table();
static void render_player();
static void render_ok_btn();
static void render_cancel_btn();
static void render_exit_btn();
static void render_room_info();
static void render_chat_input();
static void render_send_btn();
static void render_chat_mess();
static WINDOW *get_target_win();
void listen_mouse_game();
void destroy_game();
static void *render_game_when_recv_res();
static void *render_time();
static void warning_game(const char *mess);
static void checkEndGame();
void inputChat(char *chat);
void init_game(char *curUser, char *roomName)
{
    isFocused = true;
    strcpy(currentRoom.players[0].name, curUser);
    strcpy(currentRoom.roomName, roomName);
    clear();
    refresh();
    mainWin = stdscr;
    box(mainWin, 0, 0);
    // mock();
    currentRoom.turn = -1;
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
    wbkgd(topWin, COLOR_PAIR(2) | A_BOLD);
    render_exit_btn();
    render_room_info();
    render_point();
    touchwin(topWin);
    wrefresh(topWin);
}
void render_point()
{
    wattron(topWin, COLOR_PAIR(17) | A_BOLD);
    mvwprintw(topWin, 2, getmaxx(topWin) - 35, "Hello %s : %d points", currentRoom.players[0].name, currentRoom.players[0].point);
    wattroff(topWin, COLOR_PAIR(17) | A_BOLD);
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
    render_cancel_btn();
    wrefresh(gameWin);
    // touchwin(gameWin);
    // wrefresh(gameWin);
}
void render_chat()
{
    chatWin = derwin(mainWin, getmaxy(mainWin) - 2, getmaxx(mainWin) / 3 - 1, 1, getmaxx(mainWin) / 3 * 2 + 1);
    box(chatWin, 0, 0);
    mvwprintw(chatWin, 2, 19, "%-35s", " ▄████▄   ██░ ██  ▄▄▄     ▄▄▄█████▓");
    mvwprintw(chatWin, 3, 19, "%-35s", "▒██▀ ▀█  ▓██░ ██▒▒████▄   ▓  ██▒ ▓▒");
    mvwprintw(chatWin, 4, 19, "%-35s", "▒▓█    ▄ ▒██▀▀██░▒██  ▀█▄ ▒ ▓██░ ▒░");
    mvwprintw(chatWin, 5, 19, "%-35s", "▒▓▓▄ ▄██▒░▓█ ░██ ░██▄▄▄▄██░ ▓██▓ ░ ");
    mvwprintw(chatWin, 6, 19, "%-35s", "▒ ▓███▀ ░░▓█▒░██▓ ▓█   ▓██▒ ▒██▒ ░ ");
    mvwprintw(chatWin, 7, 19, "%-35s", "░ ░▒ ▒  ░ ▒ ░░▒░▒ ▒▒   ▓▒█░ ▒ ░░   ");
    mvwprintw(chatWin, 8, 19, "%-35s", "  ░  ▒    ▒ ░▒░ ░  ▒   ▒▒ ░   ░    ");
    mvwprintw(chatWin, 9, 19, "%-35s", "░         ░  ░░ ░  ░   ▒    ░      ");
    mvwprintw(chatWin, 10, 19, "%-35s", "░ ░       ░  ░  ░      ░  ░        ");
    mvwprintw(chatWin, 11, 19, "%-35s", "░                                  ");

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
    int turn = currentRoom.turn;
    clear_player();
    if (playerSize > 1)
    {
        playerAvatar[0] = derwin(gameWin, 8, 10, getmaxy(gameWin) / 2 - 6, getmaxx(gameWin) - 13);
        mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, getmaxx(gameWin) - 9 - (strlen("👤 ") + strlen(players[1].name)) / 2, "%s %s", "👤", players[1].name);
        render_player_avatar(playerAvatar[0], players[1].cardSize, turn == 1);
    }
    if (playerSize > 2)
    {
        playerAvatar[1] = derwin(gameWin, 8, 10, 3, getmaxx(gameWin) / 2 - 5);
        mvwprintw(gameWin, 1, getmaxx(gameWin) / 2 - (strlen("👤 ") + strlen(players[2].name)) / 2, "%s %s", "👤", players[2].name);
        render_player_avatar(playerAvatar[1], players[2].cardSize, turn == 2);
    }
    if (playerSize > 3)
    {
        playerAvatar[2] = derwin(gameWin, 8, 10, getmaxy(gameWin) / 2 - 6, 3);
        mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, 8 - (strlen("👤 ") + strlen(players[3].name)) / 2, "%s %s", "👤", players[3].name);
        render_player_avatar(playerAvatar[2], players[3].cardSize, turn == 3);
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
    mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, 8 - 20 / 2, "%15s", "");
    mvwprintw(gameWin, getmaxy(gameWin) / 2 - 8, getmaxx(gameWin) - 9 - 20 / 2, "%15s", "");
    mvwprintw(gameWin, 1, getmaxx(gameWin) / 2 - 20 / 2, "%15s", "");
    wrefresh(gameWin);
}
void render_player_avatar(WINDOW *orig, int cardSize, bool isTurn)
{
    bool isFocus = isTurn && currentRoom.isPlaying;
    int color = isFocus ? 7 : 5;
    wattron(orig, COLOR_PAIR(color));

    mvwprintw(orig, 1, 1, ".------.");
    mvwprintw(orig, 2, 1, "| .--. |");
    mvwprintw(orig, 3, 1, "| :/\\: |");
    mvwprintw(orig, 4, 1, "| (%2d) |", cardSize);
    mvwprintw(orig, 5, 1, "| '--' |");
    mvwprintw(orig, 6, 1, "`------'");

    wattroff(orig, COLOR_PAIR(color));
    box(orig, 0, 0);
    wrefresh(orig);
}
void render_ok_btn()
{
    if (okBtn != NULL)
    {
        wclear(okBtn);
        wrefresh(okBtn);
        delwin(okBtn);
        okBtn = NULL;
    }
    okBtn = derwin(gameWin, 3, 12, getmaxy(gameWin) - 5, getmaxx(gameWin) / 2 - 10);
    wbkgd(okBtn, COLOR_PAIR(4));
    wattron(okBtn, A_BOLD);
    // mvwprintw(okBtn, 1, 3, currentRoom.isPlaying ? "PLAY" : currentRoom.owner ? "START"
    //                                                                           : "WAITTING");
    if (currentRoom.isPlaying)
    {
        mvwprintw(okBtn, 1, 4, "PLAY");
    }
    else
    {
        if (currentRoom.owner)
        {
            mvwprintw(okBtn, 1, 3, "START");
        }
        else
        {
            mvwprintw(okBtn, 1, 1, "WAITTING");
        }
    }

    wattroff(okBtn, A_BOLD);
    box(okBtn, 0, 0);
    wrefresh(okBtn);
}
void render_cancel_btn()
{
    if (cancelBtn != NULL)
    {
        wclear(cancelBtn);
        wrefresh(cancelBtn);
        delwin(cancelBtn);
        cancelBtn = NULL;
    }
    if (currentRoom.turn == 0 && currentRoom.isPlaying)
    {
        cancelBtn = derwin(gameWin, 3, 12, getmaxy(gameWin) - 5, getmaxx(gameWin) / 2 + 7);
        wattron(cancelBtn, A_STANDOUT | A_BOLD);
        mvwprintw(cancelBtn, 1, 4, "SKIP");
        box(cancelBtn, 0, 0);
        wattroff(cancelBtn, A_STANDOUT | A_BOLD);
        wrefresh(cancelBtn);
    }
}
void render_exit_btn()
{
    exitBtn = derwin(topWin, 3, 15, 1, 3);
    box(exitBtn, 0, 0);
    wbkgd(exitBtn, COLOR_PAIR(4) | A_BOLD);
    wattron(exitBtn, A_BOLD);
    mvwprintw(exitBtn, 1, 6, "%s", "EXIT");
    wattroff(exitBtn, A_BOLD);
    wrefresh(exitBtn);
}
void render_room_info()
{
    roomName = derwin(topWin, 3, 28, 1, 25);
    box(roomName, 0, 0);
    wattroff(roomName, A_STANDOUT);
    wattron(roomName, A_BOLD | COLOR_PAIR(2));
    mvwprintw(roomName, 1, 2, "Room's name: %s", currentRoom.roomName);
    wattroff(roomName, A_BOLD | COLOR_PAIR(2));
    wrefresh(roomName);
}
void render_chat_input()
{
    chatInput = derwin(chatWin, 3, getmaxx(chatWin) - 15, getmaxy(chatWin) - 4, 2);
    box(chatInput, 0, 0);
    // wrefresh(chatInput);
}
void render_chat_mess()
{
    ChatMess chat;
    int start = 5;
    int maxY = getmaxy(chatWin);
    int maxX = getmaxx(chatWin);
    for (int i = 0; i < currentRoom.chatMessSize; i++)
    {
        mvwprintw(chatWin, maxY - i - 7, 4, "%s", "");
        chat = currentRoom.chatMess[i];
        // is me
        if (strcmp(chat.username, currentRoom.players[0].name) == 0)
        {
            wattron(chatWin, A_BOLD | COLOR_PAIR(10));
            mvwprintw(chatWin, maxY - i - 7, 4, "%66s", chat.message);
            wattroff(chatWin, A_BOLD | COLOR_PAIR(10));
            continue;
        }
        // is other
        // wattron(chatWin, A_BOLD | COLOR_PAIR(2));
        mvwprintw(chatWin, maxY - i - 7, 4, "%s: %-58s", chat.username, chat.message);
        // wattroff(chatWin, A_BOLD | COLOR_PAIR(2));
    }
    // mvwprintw(chatWin, getmaxy(chatWin) / 2, getmaxx(chatWin) / 2, "%s %d", "CHAT", currentRoom.chatMessSize);
    wrefresh(chatWin);
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
    int cancelBtnX = getbegx(cancelBtn), cancelBtnY = getbegy(cancelBtn), cancelBtnW = getmaxx(cancelBtn), cancelBtnH = getmaxy(cancelBtn);
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
    if (mx >= cancelBtnX && mx <= cancelBtnX + cancelBtnW && my >= cancelBtnY && my <= cancelBtnY + cancelBtnH)
    {
        return currentRoom.turn == 0 ? cancelBtn : NULL;
    }
    return NULL;
}
void listen_mouse_game()
{
    WINDOW *target = NULL;
    int c;
    pthread_t thread, timer;
    pthread_create(&thread, NULL, &render_game_when_recv_res, NULL);
    pthread_create(&timer, NULL, &render_time, NULL);
    pthread_detach(thread);
    pthread_detach(timer);
    char mess[100];
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
            isFocused = false;
            napms(100);
            pthread_cancel(thread);
            pthread_cancel(timer);
            processLeaveRoom(NULL);
            napms(100);
            destroy_game();
            break;
        }
        // game win
        if (target == okBtn)
        {
            if (!onOkBtnClick(&currentRoom, mess))
            {
                warning_game(mess);
                strcpy(mess, "");
                continue;
            }
            continue;
        }
        if (target == cancelBtn)
        {
            onCancelBtnClick(&currentRoom);
            continue;
        }

        // chat win
        if (target == sendBtn)
        {
            // send message

            processChat(mess);
            mvwprintw(chatInput, 1, 2, "%-56s", "");
            wrefresh(chatInput);
            continue;
        }
        if (target == chatInput)
        {
            inputChat(mess);
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
    bzero(&currentRoom, sizeof(CurrentRoom));
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
            render_point();
            render_player();
            render_ok_btn();
            break;
        case CHAT_RES:
            handleChat(&currentRoom, res.data.chat);
            render_chat_mess();
            render_chat_input();
            break;
        case NEW_GAME_RES:
            handleNewGame(&currentRoom, res.data.newGame);
            render_game();
            break;
        case GAME_RES:
            handleGame(&currentRoom, res.data.play);
            render_game();
            break;
        case SKIP_RES:
            handleSkip(&currentRoom, res.data.skip);
            render_game();
            break;
        default:
            break;
        }
        checkEndGame();
    }
}
void *render_time()
{
    int time = 0, seconds = 0, minutes = 0;
    while (true)
    {
        if (!currentRoom.isPlaying)
        {
            time = 0;
            continue;
        }
        time++;
        seconds = time % 60;
        minutes = time / 60;
        wattron(topWin, COLOR_PAIR(17) | A_BOLD);
        mvwprintw(topWin, 2, 55, "Time: %02d:%02d", minutes, seconds);
        wattroff(topWin, COLOR_PAIR(17) | A_BOLD);
        wrefresh(topWin);
        napms(1000);
    }
}
static void warning_game(const char *mess)
{
    noecho();
    WINDOW *warning_win = newwin(10, 50, LINES / 2 + 3, COLS / 2 - 57);
    wattron(warning_win, COLOR_PAIR(4));
    box(warning_win, 0, 0);
    wattron(warning_win, A_STANDOUT);
    mvwprintw(warning_win, 2, 2, "%40s", mess);
    wattroff(warning_win, COLOR_PAIR(4) | A_STANDOUT);
    wattron(warning_win, COLOR_PAIR(14));
    mvwprintw(warning_win, 7, 2, "%s", "Press any key to continue");
    wattroff(warning_win, COLOR_PAIR(14));
    wrefresh(warning_win);
    wgetch(warning_win);
    wclear(warning_win);
    wrefresh(warning_win);
    delwin(warning_win);
    // refresh();
}
void inputChat(char *chat)
{
    mousemask(0, NULL);
    curs_set(true);
    echo();
    mvwprintw(chatInput, 1, 2, "%-56s", "");
    mvwgetstr(chatInput, 1, 2, chat);
    wrefresh(chatInput);
    curs_set(false);
    mousemask(ALL_MOUSE_EVENTS, NULL);
}
void checkEndGame()
{
    if (!currentRoom.isPlaying)
        return;
    int i = -1;
    for (int j = 0; j < currentRoom.currentPlayer; j++)
    {
        if (currentRoom.players[j].cardSize == 0)
        {
            i = j;
        }
    }
    if (i == -1)
    {
        return;
    }
    currentRoom.cardsOnTableSize = 0;
    currentRoom.isPlaying = false;
    bzero(currentRoom.cardsChoosed, sizeof(currentRoom.cardsChoosed));
    for (int k = 0; k < 4; k++)
    {
        currentRoom.players[k].cardSize = 0;
    }
    bzero(currentRoom.cardsInHand, sizeof(currentRoom.cardsInHand));
    char mess[100];
    strcpy(mess, "Player ");
    strcat(mess, currentRoom.players[i].name);
    strcat(mess, " win");
    warning_game(mess);
    render_game();
    napms(100);
}

#endif // GAME_UI_TEST_H
