#ifndef RESPONSE_H_
#define RESPONSE_H_
#include "index.h"
#include "roomInfo.h"
#include "tienlen.h"
#include "server/session.h"
typedef struct _resRD
{
    bool success;
    char message[100];
} ResRD;
typedef struct _findRoomResD
{
    RoomInfo room[10];
    int roomSize;
} FindRoomResD;
typedef struct _updateRoomResD
{
    int playerSize; // number of players in room
    Player player[MAX_PLAYER];
} UpdateRoomResD;
typedef struct _chatResD
{
    char username[20];
    char message[100];
} ChatResD;
typedef struct _newGameResD
{
    int turn;                         // true if first turn is your turn
    int playerSize;                   // playerSize = 2 -> 4
    Player player[MAX_PLAYER];        // player[0] is you
    Card cardInHand[CARD_VALUE_SIZE]; // 13 cards in hand
} NewGameResD;
typedef struct _playResD
{
    int playerTurn;                    // next turn (0 - 3)
    int playerSize;                    // number of players in room (2 -> 4)
    Player player[MAX_PLAYER];         // player[0] is you
    int cardInTableSize;               // number of card in table
    Card cardInTable[CARD_VALUE_SIZE]; // card in table
} PlayResD;
typedef struct _skipResD
{
    char username[20]; // username of player skip turn
    char lastTurn[20]; // username of player last turn
} SkipResD;
typedef enum _ResT
{
    FIND_ROOM_RES,   // find room response from server
    UPDATE_ROOM_RES, // update room properties from server
    NEW_GAME_RES,    // new game properties from server
    GAME_RES,        // update game properties from server
    SKIP_RES,        // skip turn from server
    CHAT_RES,        // update chat properties from server
    R_RES            // Response for request from client
} ResT;
typedef union _resD
{
    FindRoomResD findRoom;
    UpdateRoomResD updateRoom;
    NewGameResD newGame;
    PlayResD play;
    SkipResD skip;
    ChatResD chat;
    ResRD resR;
} ResD;

typedef struct _response
{
    ResT type;
    ResD data;
} Res;

Res createResponse(ResT type, ResD data)
{
    Res res;
    res.type = type;
    res.data = data;
    return res;
}
Res createFindRoomResponse(RoomInfo room[10], int roomSize)
{
    FindRoomResD data;
    data.roomSize = roomSize;
    for (int i = 0; i < roomSize; i++)
    {
        data.room[i] = room[i];
    }
    return createResponse(FIND_ROOM_RES, (ResD)data);
}
Res createUpdateRoomResponse(int playerSize, Player player[MAX_PLAYER])
{
    UpdateRoomResD data;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    return createResponse(UPDATE_ROOM_RES, (ResD)data);
}
Res createNewGameResponse(int turn, int playerSize, Player player[MAX_PLAYER], Card cardInHand[CARD_VALUE_SIZE])
{
    NewGameResD data;
    data.turn = turn;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    for (int i = 0; i < CARD_VALUE_SIZE; i++)
    {
        data.cardInHand[i] = cardInHand[i];
    }
    return createResponse(NEW_GAME_RES, (ResD)data);
}

Res createPlayResponse(int playerTurn, int playerSize, Player player[MAX_PLAYER], int cardInTableSize, Card cardInTable[CARD_VALUE_SIZE])
{
    PlayResD data;
    data.playerTurn = playerTurn;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    data.cardInTableSize = cardInTableSize;
    for (int i = 0; i < cardInTableSize; i++)
    {
        data.cardInTable[i] = cardInTable[i];
    }
    return createResponse(GAME_RES, (ResD)data);
}
Res createSkipResponse(char username[20], char lastTurn[20])
{
    SkipResD data;
    strcpy(data.username, username);
    strcpy(data.lastTurn, lastTurn);
    return createResponse(SKIP_RES, (ResD)data);
}
Res createChatResponse(char username[20], char message[100])
{
    ChatResD data;
    strcpy(data.username, username);
    strcpy(data.message, message);
    return createResponse(CHAT_RES, (ResD)data);
}

Res createRResponse(bool success, char message[100])
{
    ResRD data;
    data.success = success;
    strcpy(data.message, message);
    return createResponse(R_RES, (ResD)data);
}

/// @brief
/// @param sockfd
/// @param res
/// @return bytes sent, 0 if disconnected, -1 if error
int sendResponse(int sockfd, Res res)
{
    switch (res.type)
    {
    case UPDATE_ROOM_RES:
    {
        UpdateRoomResD updateRoom = res.data.updateRoom;
        printf("Server send UPDATE_ROOM_RES: %s\n", getSessionBySockfd(sockfd)->username);
        // for (int i = 0; i < updateRoom.playerSize; i++)
        // {
        //     /* code */
        // }
        break;
    }
    case R_RES:
    {
        ResRD resR = res.data.resR;
        printf("Server send R_RES: %s: %s-%s\n", getSessionBySockfd(sockfd)->username, resR.success ? "success" : "fail", resR.message);
        break;
    }
    default:
        break;
    };
    int size;
    switch (res.type)
    {
    case FIND_ROOM_RES:
        size = sizeof(FindRoomResD);
        break;
    case UPDATE_ROOM_RES:
        size = sizeof(UpdateRoomResD);
        break;
    case NEW_GAME_RES:
        size = sizeof(NewGameResD);
        break;
    case GAME_RES:
        size = sizeof(PlayResD);
        break;
    case SKIP_RES:
        size = sizeof(SkipResD);
        break;
    case CHAT_RES:
        size = sizeof(ChatResD);
        break;
    case R_RES:
        size = sizeof(ResRD);
        break;
    default:
        break;
    }
    return send(sockfd, &res, size + sizeof(ResT), 0);
}
/// @brief
/// @param sockfd
/// @param res
/// @return bytes received, 0 if disconnected, -1 if error
int recvResponse(int sockfd, Res *res)
{
    return recv(sockfd, res, sizeof(Res), 0);
}

void Res2String(Res *res, const char *str)
{
    sizeof(Res);
    sizeof(ResD);
    sizeof(ResT);
}
void String2Res(char *str, const Res *res) {}
#endif // RESPONSE_H_