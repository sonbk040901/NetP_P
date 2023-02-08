#ifndef REQUEST_H_
#define REQUEST_H_
#include "index.h"
#include "tienlen.h"

/// @brief Request type
/// {Example: Login, signup, active, play, chat, create room, join room, find room}
typedef enum _reqType
{
    LOGIN_REQ,  // Login request from client
    SIGNUP_REQ, // Signup request from client
    ACTIVE_REQ, // Active request from client
    // LOGOUT_REQ,
    PLAY_REQ,        // Play request from client
    SKIP_REQ,        // Skip request from client
    START_GAME_REQ,  // Start game request from client
    CHAT_REQ,        // Chat request from client
    CREATE_ROOM_REQ, // Create room request from client
    FIND_ROOM_REQ,   // Find room request from client
    JOIN_ROOM_REQ,   // Join room request from client
    LEAVE_ROOM_REQ   // Leave room request from client
    // INTERRUPT,
} ReqT;
typedef struct _login
{
    char username[20];
    char password[20];
} LoginReqD;
typedef struct _login SignupReqD;
typedef struct _active
{
    LoginReqD userData;
    char activationCode[20];
} ActiveReqD;
typedef struct _play
{
    Card cards[CARD_SIZE / MAX_PLAYER]; // played card
    int cardSize;                       // = 0;
} PlayReqD;
typedef struct _skipGame
{
    /* data */
} SkipGameReqD;
typedef struct _startGame
{
    /* data */
} StartGameReqD;

typedef struct _chat
{
    char message[100];
} ChatReqD;
typedef struct _createRoom
{
    char roomName[20];
    int maxPlayer; // = MAX_PLAYER;
} CreateRoomReqD;
typedef struct _findRoom
{
    char roomName[20];
} FindRoomReqD;
typedef struct _joinRoom
{
    char roomName[20];
} JoinRoomReqD;
typedef struct _leaveRoom
{
    /*data*/
} LeaveRoomReqD;
// RequestData
typedef union requestData
{
    LoginReqD login;           //
    SignupReqD signup;         //
    ActiveReqD active;         //
    PlayReqD play;             //
    SkipGameReqD skip;         //
    StartGameReqD startGame;   //
    ChatReqD chat;             //
    CreateRoomReqD createRoom; //
    FindRoomReqD findRoom;     //
    JoinRoomReqD joinRoom;     //
    LeaveRoomReqD leaveRoom;   //
} ReqD;
// Request
typedef struct _request
{
    ReqT type;
    ReqD data;
} Req;

Req createRequest(ReqT type, ReqD data)
{
    Req request;
    request.type = type;
    request.data = data;
    return request;
}

Req createLoginRequest(char *username, char *password)
{
    LoginReqD data;
    strcpy(data.username, username);
    strcpy(data.password, password);
    return createRequest(LOGIN_REQ, (ReqD)data);
}

Req createSignupRequest(const char *username, const char *password)
{
    SignupReqD data;
    strcpy(data.username, username);
    strcpy(data.password, password);
    return createRequest(SIGNUP_REQ, (ReqD)data);
}

Req createActiveRequest(const char *username, const char *password, const char *activationCode)
{
    ActiveReqD data;
    strcpy(data.userData.username, username);
    strcpy(data.userData.password, password);
    strcpy(data.activationCode, activationCode);
    return createRequest(ACTIVE_REQ, (ReqD)data);
}

Req createPlayRequest(Card *cards, int cardSize)
{
    PlayReqD data;
    for (int i = 0; i < cardSize; i++)
    {
        data.cards[i] = cards[i];
    }
    data.cardSize = cardSize;
    return createRequest(PLAY_REQ, (ReqD)data);
}
Req createSkipGameRequest()
{
    SkipGameReqD data;
    return createRequest(SKIP_REQ, (ReqD)data);
}
Req createStartGameRequest()
{
    StartGameReqD data;
    return createRequest(START_GAME_REQ, (ReqD)data);
}
Req createChatRequest(char *message)
{
    ChatReqD data;
    strcpy(data.message, message);
    return createRequest(CHAT_REQ, (ReqD)data);
}

Req createCreateRoomRequest(char *roomName, int maxPlayer)
{
    CreateRoomReqD data;
    strcpy(data.roomName, roomName);
    data.maxPlayer = maxPlayer;
    return createRequest(CREATE_ROOM_REQ, (ReqD)data);
}

Req createFindRoomRequest(char *roomName)
{
    FindRoomReqD data;
    strcpy(data.roomName, roomName);
    return createRequest(FIND_ROOM_REQ, (ReqD)data);
}

Req createJoinRoomRequest(char *roomName)
{
    JoinRoomReqD data;
    strcpy(data.roomName, roomName);
    return createRequest(JOIN_ROOM_REQ, (ReqD)data);
}

Req createLeaveRoomRequest()
{
    LeaveRoomReqD data;
    return createRequest(LEAVE_ROOM_REQ, (ReqD)data);
}
/// @brief
/// @param sockfd
/// @param request
/// @return bytes sent, 0 if disconnected, -1 if error
int sendRequest(int sockfd, Req request)
{
    return send(sockfd, &request, sizeof(Req), 0);
}
/// @brief
/// @param sockfd
/// @param request
/// @return bytes received, 0 if disconnected, -1 if error
int recvRequest(int sockfd, Req *request)
{
    sleep(1);
    return recv(sockfd, request, sizeof(Req), 0);
}

void Req2String(Req *req, const char *str) {}
void String2Req(char *str, const Req *req) {}
#endif // REQUEST_H_