#if !defined(ACTIVITY_GAME_H_)
#define ACTIVITY_GAME_H_
#include "index.h"
#include "rules.h"
extern int clientfd;
typedef struct _chatMess
{
    char username[20];
    char message[100];
} ChatMess;

typedef struct _currentRoom
{
    int id;
    char roomName[20];
    int maxPlayer;                             // Maximum number of players in room
    int currentPlayer;                         // Number of current player in room
    bool owner;                                // Owner of room
    int turn;                                  // Turn of player
    Player players[4];                         // players[0] is you
    Card cardsInHand[CARD_SIZE / MAX_PLAYER];  // cards in hand
    int cardsOnTableSize;                      // number of cards on table
    Card cardsOnTable[CARD_SIZE];              // cards on table
    bool cardsChoosed[CARD_SIZE / MAX_PLAYER]; // true: card is choosed
    bool isPlaying;                            // false: waiting, true: playing
    ChatMess chatMess[30];                     // chat message
    int chatMessSize;                          // number of chat message
} CurrentRoom;
void handleUpdateRoom(CurrentRoom *room, UpdateRoomResD data);
void handleChat(CurrentRoom *room, ChatResD data);
void handleNewGame(CurrentRoom *room, NewGameResD data);
void handleGame(CurrentRoom *room, PlayResD data);
void handleSkip(CurrentRoom *room, SkipResD data);
bool processLeaveRoom(char *mess);
bool onOkBtnClick(CurrentRoom *, char *message);
void onCancelBtnClick(CurrentRoom *);
void processChat(char *mess);
bool processPlayGame(CurrentRoom *room, char *mess);

void handleUpdateRoom(CurrentRoom *room, UpdateRoomResD data)
{
    room->currentPlayer = data.playerSize;
    if (data.playerSize == 1)
    {
        room->owner = true;
    }
    int index = 0;
    for (int i = 0; i < data.playerSize; i++)
    {
        if (strcmp(data.player[i].name, room->players[0].name) == 0)
        {
            index = i;
            break;
        }
    }
    for (int i = 0; i < data.playerSize; i++)
    {
        room->players[i] = data.player[(index + i) % data.playerSize];
    }
}
void handleChat(CurrentRoom *room, ChatResD data)
{
    for (int i = room->chatMessSize; i > 0; i--)
    {
        room->chatMess[i] = room->chatMess[i - 1];
    }
    strcpy(room->chatMess[0].username, data.username);
    strcpy(room->chatMess[0].message, data.message);
    room->chatMessSize++;
}
void handleNewGame(CurrentRoom *room, NewGameResD data)
{
    room->isPlaying = true;
    room->currentPlayer = data.playerSize;

    int index = 0;
    for (int i = 0; i < data.playerSize; i++)
    {
        if (strcmp(data.player[i].name, room->players[0].name) == 0)
        {
            index = i;
            break;
        }
    }
    room->cardsOnTableSize = 0;
    for (int i = 0; i < data.playerSize; i++)
    {
        room->players[i] = data.player[(index + i) % data.playerSize];
    }
    room->turn = (data.turn + index) % data.playerSize;

    for (int i = 0; i < room->players[0].cardSize; i++)
    {
        room->cardsInHand[i] = data.cardInHand[i];
    }
}
void handleGame(CurrentRoom *room, PlayResD data)
{
    room->cardsOnTableSize = data.cardInTableSize;
    for (int i = 0; i < data.cardInTableSize; i++)
    {
        room->cardsOnTable[i] = data.cardInTable[i];
    }
    int index = 0;
    for (int i = 0; i < data.playerSize; i++)
    {
        if (strcmp(data.player[i].name, room->players[0].name) == 0)
        {
            index = i;
            break;
        }
    }
    room->currentPlayer = data.playerSize;
    for (int i = 0; i < data.playerSize; i++)
    {
        room->players[i] = data.player[(index + i) % data.playerSize];
    }
    room->turn = (data.playerSize - index + data.playerTurn) % data.playerSize;
}
void handleSkip(CurrentRoom *room, SkipResD data)
{
    char username[20];
    strcpy(username, data.username);
    int i;
    for (i = 0; i < room->currentPlayer; i++)
    {
        if (strcmp(room->players[i].name, username) == 0)
        {
            break;
        }
    }
    room->turn = (i + 1) % room->currentPlayer;
    if (strcmp(room->players[room->turn].name, data.lastTurn) == 0)
    {
        room->cardsOnTableSize = 0;
    }
}
bool processLeaveRoom(char *mess)
{
    Req req = createLeaveRoomRequest();
    sendRequest(clientfd, req);
    Res res;
    recvResponse(clientfd, &res);
    if (mess)
    {
        strcpy(mess, res.data.resR.message);
    }
    return res.data.resR.success;
}
bool onOkBtnClick(CurrentRoom *room, char *message)
{
    bool isPlaying = room->isPlaying;
    bool isOwner = room->owner;
    int playerNum = room->currentPlayer;
    bool isTurn = room->turn == 0;
    Req req;
    // Waiting
    if (!isPlaying)
    {
        if (!isOwner)
        {
            strcpy(message, "You are not owner of room");
            return false;
        }
        if (playerNum < 2)
        {
            strcpy(message, "You need at least 2 players to start game");
            return false;
        }
        // Start game
        // TODO: send request to server to start game
        req = createStartGameRequest();
        sendRequest(clientfd, req);
        return true;
    }
    // Playing
    if (!isTurn)
    {
        strcpy(message, "It's not your turn");
        return false;
    }
    // TODO: Send request to server to play
    return processPlayGame(room, message);
}
void onCancelBtnClick(CurrentRoom *room)
{
    Req req = createSkipGameRequest();
    sendRequest(clientfd, req);
}
void processChat(char *mess)
{
    if (strlen(mess) <= 0)
    {
        return;
    }
    Req req = createChatRequest(mess);
    sendRequest(clientfd, req);
    // Nhận để biết là oke rồi, chứ cũng ko cần
    // Res res;
    // recvResponse(clientfd, &res);
    // if (res.data.resR.success)
    // {
    beep();
    strcpy(mess, "");
    // }
}
bool processPlayGame(CurrentRoom *room, char *mess)
{
    InforCards prvCards, curCards;
    bzero(&curCards, sizeof(curCards));
    bzero(&prvCards, sizeof(prvCards));
    for (int i = 0; i < room->players[0].cardSize; i++)
    {
        if (room->cardsChoosed[i])
        {
            curCards.cards[curCards.NumberOfGroupCards] = room->cardsInHand[i];
            curCards.NumberOfGroupCards++;
        }
    }
    if (curCards.NumberOfGroupCards == 0)
    {
        strcpy(mess, "You need to choose at least 1 card");
        return false;
    }
    for (int i = 0; i < room->cardsOnTableSize; i++)
    {
        prvCards.cards[prvCards.NumberOfGroupCards] = room->cardsOnTable[i];
        prvCards.NumberOfGroupCards++;
    }
    curCards = xepBai(curCards);
    curCards.NameOfGroupCards = checkBaiDanhXuong(curCards);
    prvCards = xepBai(prvCards);
    prvCards.NameOfGroupCards = checkBaiDanhXuong(prvCards);
    if (checkValid(prvCards, curCards) == false)
    {
        strcpy(mess, "Invalid card");
        return false;
    }
    // success
    for (int i = 0; i < room->players[0].cardSize; i++)
    {
        if (room->cardsChoosed[i])
        {
            for (int j = i; j < room->players[0].cardSize - 1; j++)
            {
                room->cardsInHand[j] = room->cardsInHand[j + 1];
                room->cardsChoosed[j] = room->cardsChoosed[j + 1];
            }
            room->players[0].cardSize--;
            i--;
        }
    }
    for (int i = 0; i < room->players[0].cardSize; i++)
    {
        room->cardsChoosed[i] = false;
    }
    // endwin();
    // exit(0);

    Req req = createPlayRequest(curCards.cards, curCards.NumberOfGroupCards);
    sendRequest(clientfd, req);
    return true;
}
#endif // ACTIVITY_GAME_H_
