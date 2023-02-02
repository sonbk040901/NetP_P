#if !defined(ACTIVITY_GAME_H_)
#define ACTIVITY_GAME_H_
#include "index.h"
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
    ChatMess chatMess[20];                     // chat message
    int chatMessSize;                          // number of chat message
} CurrentRoom;
void handleUpdateRoom(CurrentRoom *room, UpdateRoomResD data);
void handleChat(CurrentRoom *room, ChatResD data);
bool processLeaveRoom(char *mess);
bool onOkBtnClick(CurrentRoom, char *message);
void processChat(char *mess);
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
bool onOkBtnClick(CurrentRoom room, char *message)
{
    bool isPlaying = room.isPlaying;
    bool isOwner = room.owner;
    int playerNum = room.currentPlayer;
    bool isTurn = room.turn == 0;
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
        return true;
    }
    // Playing
    if (!isTurn)
    {
        strcpy(message, "It's not your turn");
        return false;
    }
    // TODO: Send request to server to play
    return true;
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
#endif // ACTIVITY_GAME_H_
