#ifndef RESPONSE_H_
#define RESPONSE_H_
#include <stdbool.h>
#include "index.h"
typedef struct _resData
{
    bool success;
    char message[100];
} ResData;
typedef struct _chatGData
{
    char username[20];
    char message[100];
} ChatGData;
typedef struct _newGameData
{
    bool isTurn;                      // true if first turn is your turn
    int playerSize;                   // playerSize = 2 -> 4
    Player player[MAX_PLAYER];        // player[0] is you
    Card cardInHand[CARD_VALUE_SIZE]; // 13 cards in hand
} NewGameData;
typedef struct _gameData
{
    int playerTurn;                    // next turn (0 - 3)
    int playerSize;                    // number of players in room (2 -> 4)
    Player player[MAX_PLAYER];         // player[0] is you
    int cardInTableSize;               // number of card in table
    Card cardInTable[CARD_VALUE_SIZE]; // card in table
} GameData;

typedef enum _responseType
{
    N_GAME_RES, // new game properties from server
    U_GAME_RES, // update game properties from server
    U_CHAT_RES, // update chat properties from server
    RES         // Response for request from client
} ResponseType;
typedef union _ResponseData
{
    NewGameData newGameData;
    GameData gameData;
    ChatGData chatData;
    ResData resData;
} ResponseData;

typedef struct _response
{
    ResponseType type;
    ResponseData data;
} Response;

Response createResponse(ResponseType type, ResponseData data)
{
    Response res;
    res.type = type;
    res.data = data;
    return res;
}

Response createNGameResponse(bool isTurn, int playerSize, Player player[MAX_PLAYER], Card cardInHand[CARD_VALUE_SIZE])
{
    NewGameData data;
    data.isTurn = isTurn;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    for (int i = 0; i < CARD_VALUE_SIZE; i++)
    {
        data.cardInHand[i] = cardInHand[i];
    }
    return createResponse(N_GAME_RES, (ResponseData)data);
}

Response createUGameResponse(int playerTurn, int playerSize, Player player[MAX_PLAYER], int cardInTableSize, Card cardInTable[CARD_VALUE_SIZE])
{
    GameData data;
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
    return createResponse(U_GAME_RES, (ResponseData)data);
}

Response createUChatResponse(char username[20], char message[100])
{
    ChatGData data;
    strcpy(data.username, username);
    strcpy(data.message, message);
    return createResponse(U_CHAT_RES, (ResponseData)data);
}

Response createResResponse(bool success, char message[100])
{
    ResData data;
    data.success = success;
    strcpy(data.message, message);
    return createResponse(RES, (ResponseData)data);
}

#endif // RESPONSE_H_