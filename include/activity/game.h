#if !defined(ACTIVITY_GAME_H_)
#define ACTIVITY_GAME_H_
#include "index.h"
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
    int owner;                                 // Owner of room
    int turn;                                  // Turn of player
    Player players[4];                         // players[0] is you
    Card cardsInHand[CARD_SIZE / MAX_PLAYER];  // cards in hand
    int cardsOnTableSize;                      // number of cards on table
    Card cardsOnTable[CARD_SIZE];              // cards on table
    bool cardsChoosed[CARD_SIZE / MAX_PLAYER]; // true: card is choosed
    bool isPlaying;                            // false: waiting, true: playing
    ChatMess chatMess[20];                     // chat message
} CurrentRoom;
void handleUpdateRoom(CurrentRoom *room, UpdateRoomResD data);
void handleUpdateRoom(CurrentRoom *room, UpdateRoomResD data)
{
    room->currentPlayer = data.playerSize;
    if (data.playerSize == 1)
    {
        room->owner = 0;
    }
    else
    {
        room->owner = -1;
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
#endif // ACTIVITY_GAME_H_
