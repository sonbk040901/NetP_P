#ifndef REQUEST_H_
#define REQUEST_H_
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tienlen.h"
typedef enum _reqType
{
    LOGIN_REQ,  // Login request from client
    SIGNUP_REQ, // Signup request from client
    ACTIVE_REQ, // Active request from client
    // LOGOUT_REQ,
    PLAY_REQ,        // Play request from client
    CHAT_REQ,        // Chat request from client
    CREATE_ROOM_REQ, // Create room request from client
    FIND_ROOM_REQ,   // Find room request from client
    JOIN_ROOM_REQ,   // Join room request from client
    // INTERRUPT,
} RequestType;
typedef struct _login
{
    char username[20];
    char password[20];
} LoginData;
typedef struct _login SignupData;
typedef struct _active
{
    LoginData userData;
    char activationCode[20];
} ActiveData;
typedef struct _play
{
    Card cards[CARD_SIZE / MAX_PLAYER];
    int cardSize; // = 0;
} PlayData;
typedef struct _chat
{
    char message[100];
} ChatData;
typedef struct _createRoom
{
    char roomName[20];
    int maxPlayer; // = MAX_PLAYER;
} CreateRoomData;
typedef struct _findRoom
{
    char roomName[20];
} FindRoomData;
typedef struct _joinRoom
{
    char roomName[20];
} JoinRoomData;
// RequestData
typedef union requestData
{
    LoginData loginData;
    SignupData signupData;
    ActiveData activeData;
    PlayData playData;
    ChatData chatData;
    CreateRoomData createRoomData;
    FindRoomData findRoomData;
    JoinRoomData joinRoomData;
} RequestData;
// Request
typedef struct _request
{
    RequestType type;
    RequestData data;
} Request;

Request createRequest(RequestType type, RequestData data)
{
    Request request;
    request.type = type;
    request.data = data;
    return request;
}

Request createLoginRequest(char *username, char *password)
{
    LoginData data;
    strcpy(data.username, username);
    strcpy(data.password, password);
    return createRequest(LOGIN_REQ, (RequestData)data);
}

Request createSignupRequest(const char *username, const char *password)
{
    SignupData data;
    strcpy(data.username, username);
    strcpy(data.password, password);
    return createRequest(SIGNUP_REQ, (RequestData)data);
}

Request createActiveRequest(const char *username, const char *password, const char *activationCode)
{
    ActiveData data;
    strcpy(data.userData.username, username);
    strcpy(data.userData.password, password);
    strcpy(data.activationCode, activationCode);
    return createRequest(ACTIVE_REQ, (RequestData)data);
}

Request createPlayRequest(Card *cards, int cardSize)
{
    PlayData data;
    for (int i = 0; i < cardSize; i++)
    {
        data.cards[i] = cards[i];
    }
    data.cardSize = cardSize;
    return createRequest(PLAY_REQ, (RequestData)data);
}

Request createChatRequest(char *message)
{
    ChatData data;
    strcpy(data.message, message);
    return createRequest(CHAT_REQ, (RequestData)data);
}

Request createCreateRoomRequest(char *roomName, int maxPlayer)
{
    CreateRoomData data;
    strcpy(data.roomName, roomName);
    data.maxPlayer = maxPlayer;
    return createRequest(CREATE_ROOM_REQ, (RequestData)data);
}

Request createFindRoomRequest(char *roomName)
{
    FindRoomData data;
    strcpy(data.roomName, roomName);
    return createRequest(FIND_ROOM_REQ, (RequestData)data);
}

Request createJoinRoomRequest(char *roomName)
{
    JoinRoomData data;
    strcpy(data.roomName, roomName);
    return createRequest(JOIN_ROOM_REQ, (RequestData)data);
}
#endif // REQUEST_H_