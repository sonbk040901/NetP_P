#if !defined(REQUEST_HANDLER_H_)
#define REQUEST_HANDLER_H_
#include "user.h"
#include "index.h"
#include "room.h"
#include "roomInfo.h"
#include <sys/types.h>
#include <ctype.h>
#include "session.h"
#include "utils.h"
void loginHandler(int, Req);
void signupHandler(int, Req);
void activeHandler(int, Req);
void createRoomHandler(int sockfd, Req req);
void findRoomHandler(int sockfd, Req req);
void joinRoomHandler(int sockfd, Req req);
void leaveRoomHandler(int sockfd, Req req);
void chatHandler(int sockfd, Req req);
void startGameHandler(int sockfd, Req req);
void playHandler(int sockfd, Req req);
void skipHandler(int sockfd, Req req);

void loginHandler(int sockfd, Req req)
{
    Dllist userList = makeUsersList("users.txt");
    User user = existsUser(userList, req.data.login.username);
    Res res;
    if (!user)
    {
        res = createRResponse(false, "User not found");
        goto done;
    }
    if (user->status == idle)
    {
        res = createRResponse(false, "User is not active");
        goto done;
    }
    if (getSessionByUser(req.data.login.username))
    {
        res = createRResponse(false, "このアカウントは既にログインしています");
        goto done;
    }

    asyncErrCount(user);
    if (user->errCount >= 3)
    {
        res = createRResponse(false, "User was blocked");
        goto done;
    }
    if (!checkPassword(user, req.data.login.password))
    {
        user->errCount++;
        if (user->errCount >= 3)
        {
            res = createRResponse(false, "User is blocked");
            blockUser(user);
        }
        else
            res = createRResponse(false, "Wrong password");
        goto done;
    }
    res = createRResponse(true, "Login successfully");
    initSession(user->username, sockfd);
    user->errCount = 0;
done:
    sendResponse(sockfd, res);
    exportList(userList, "users.txt");
    freeUserList(userList);
}
void signupHandler(int sockfd, Req req)
{
    Dllist userList = makeUsersList("users.txt");
    User user = existsUser(userList, req.data.signup.username);
    Res res;
    if (user)
    {
        res = createRResponse(false, "User already exists");
        goto done;
    }
    user = newUser(req.data.signup.username, req.data.signup.password, idle);
    addUser(userList, user);
    res = createRResponse(true, "Signup successfully, activate code: 20194658");
    // res = (Res){
    //     .type = R_RES,
    //     .data.resR = {
    //         .success = true,
    //         .message = "Signup successfully",
    //     },
    // };
done:
    sendResponse(sockfd, res);
    exportList(userList, "users.txt");
    freeUserList(userList);
}

void activeHandler(int sockfd, Req req)
{
    Dllist userList = makeUsersList("users.txt");
    ActiveReqD data = req.data.active;
    User user = existsUser(userList, data.userData.username);
    Res res;
    if (!user)
    {
        res = createRResponse(false, "User not found");
        goto done;
    }
    if (user->status == active)
    {
        res = createRResponse(false, "User is already active");
        goto done;
    }
    if (!checkPassword(user, req.data.login.password))
    {
        user->errCount++;
        if (user->errCount >= 3)
        {
            res = createRResponse(false, "User is blocked");
            blockUser(user);
        }
        else
            res = createRResponse(false, "Wrong password");
        goto done;
    }
    if (activate(user, data.activationCode))
    {
        res = createRResponse(true, "User is activated");
        activeUser(user);
    }
    else
        res = createRResponse(false, "Wrong activation code");
done:
    sendResponse(sockfd, res);
    exportList(userList, "users.txt");
    freeUserList(userList);
}
void createRoomHandler(int sockfd, Req req)
{
    CreateRoomReqD data = req.data.createRoom;
    Res res;
    printf("Create room: %s, %d", data.roomName, data.maxPlayer);
    if (data.maxPlayer < 2 || data.maxPlayer > 4)
    {
        res = createRResponse(false, "Max player must be in range [2, 4]");
        goto done;
    }
    if (findRoomByName(data.roomName))
    {
        res = createRResponse(false, "Room name already exists");
        goto done;
    }
    Room room = newRoom(data.roomName, data.maxPlayer);
    // first response is confirm that room is created
    res = createRResponse(true, "Room created successfully");
    sendResponse(sockfd, res);
    joinRoom(room, getSessionBySockfd(sockfd));
    Player *player = room->players;
    strcpy(player[0].name, getSessionBySockfd(sockfd)->username);
    player[0].cardSize = 0;
    player[0].point = getPoint(player[0].name);
    // printf("%s: %d points\n", player[0].name, player[0].point);
    // second response is update room
    res = createUpdateRoomResponse(1, player);
done:
    sendResponse(sockfd, res);
}
void findRoomHandler(int sockfd, Req req)
{
    FindRoomReqD data = req.data.findRoom;
    char keyword[100];
    strcpy(keyword, data.roomName);
    Room result[100];
    int num = findRoomsByNamePrefix(keyword, result);
    Res res;
    RoomInfo roomInfo[100];
    if (num == 0)
    {
        int id = atoi(keyword);
        result[0] = findRoom(id);
        if (result[0])
            num = 1;
    }
    for (int i = 0; i < num; i++)
    {
        roomInfo[i] = createRoomInfo(result[i]->id, result[i]->name, result[i]->players[0].name, result[i]->maxUser, result[i]->curUser, result[i]->isPlaying);
    }
    res = createFindRoomResponse(roomInfo, num);
    sendResponse(sockfd, res);
}
void joinRoomHandler(int sockfd, Req req)
{
    JoinRoomReqD data = req.data.joinRoom;
    printf("Joined room %s from %s\n", data.roomName, getSessionBySockfd(sockfd)->username);
    Room room = findRoomByName(data.roomName);

    Res res;
    if (!room)
    {
        res = createRResponse(false, "Room not found");
        goto done;
    }
    if (room->isPlaying)
    {
        res = createRResponse(false, "Room is playing");
        goto done;
    }
    if (room->curUser >= room->maxUser)
    {
        res = createRResponse(false, "Room is full");
        goto done;
    }
    Session session = getSessionBySockfd(sockfd);
    for (int i = 0; i < room->curUser; i++)
    {
        // printf("before: %s: %d point\n", room->players[i].name, room->players[i].point);
    }
    joinRoom(room, session);
    room->players[room->curUser - 1].point = getPoint(session->username);
    // for (int i = 0; i < room->curUser; i++)
    // {
    //     printf("after: %s: %d point\n", room->players[i].name, room->players[i].point);
    // }
    res = createRResponse(true, "Join room successfully");
    sendResponse(sockfd, res);
    int playerSockfd;
    for (int i = 0; i < room->curUser; i++)
    {
        playerSockfd = room->users[i]->sockfd;
        res = createUpdateRoomResponse(room->curUser, room->players);
        sendResponse(playerSockfd, res);
    }
    // for (int i = 0; i < room->curUser; i++)
    // {
    //     printf("finaly: %s: %d point\n", room->players[i].name, room->players[i].point);
    // }
    return;
done:
    sendResponse(sockfd, res);
}
void leaveRoomHandler(int sockfd, Req req)
{
    Session session = getSessionBySockfd(sockfd);
    Room room = findRoomByUser(session->username);
    leaveRoom(room, session);
    Res res = createRResponse(true, "Leave room successfully");
    sendResponse(sockfd, res);
    res = createUpdateRoomResponse(room->curUser, room->players);
    for (int i = 0; i < room->curUser; i++)
    {
        int clsockfd = room->users[i]->sockfd;
        res = createUpdateRoomResponse(room->curUser, room->players);
        sendResponse(clsockfd, res);
    }
}
void chatHandler(int sockfd, Req req)
{
    ChatReqD data = req.data.chat;
    char mess[100];
    Session session = getSessionBySockfd(sockfd);
    Room room = findRoomByUser(session->username);
    strcpy(mess, data.message);
    printf("Chat: %s: %s\n", session->username, mess);
    Res res;
    // res = createRResponse(true, "Chat successfully");
    // send to target user to confirm
    // sendResponse(sockfd, res);
    // send to other users in room
    res = createChatResponse(session->username, mess);
    for (int i = 0; i < room->curUser; i++)
    {
        int clsockfd = room->users[i]->sockfd;
        res = createChatResponse(session->username, mess);
        sendResponse(clsockfd, res);
    }
}
void startGameHandler(int sockfd, Req req)
{
    Session session = getSessionBySockfd(sockfd);
    char owner[20];
    strcpy(owner, session->username);
    Room room = findRoomByUser(session->username);
    int cardValue[CARD_SIZE];
    int cardValueForPlayer[4][CARD_VALUE_SIZE];
    Card card[4][CARD_VALUE_SIZE];
    randArray(0, CARD_SIZE - 1, cardValue, CARD_SIZE);
    Res res;
    int turn = 0;
    room->isPlaying = true;
    for (int i = 0; i < room->curUser; i++)
    {
        for (int j = 0; j < CARD_VALUE_SIZE; j++)
        {
            cardValueForPlayer[i][j] = cardValue[i * CARD_VALUE_SIZE + j];
        }
        room->players[i].cardSize = CARD_VALUE_SIZE;
    }

    for (int i = 0; i < room->curUser; i++)
    {
        if (strcmp(owner, room->players[i].name) == 0)
        {
            turn = i;
            printf("turn: %d %s\n", turn, room->players[i].name);
        }
        sortArray(cardValueForPlayer[i], CARD_VALUE_SIZE);
        for (int j = 0; j < CARD_VALUE_SIZE; j++)
        {
            indexToCard(cardValueForPlayer[i][j], &card[i][j]);
        }

        res = createNewGameResponse(turn, room->curUser, room->players, card[i]);
        sendResponse(room->users[i]->sockfd, res);
    }
}
void playHandler(int sockfd, Req req)
{
    PlayReqD data = req.data.play;
    Session session = getSessionBySockfd(sockfd);
    Room room = findRoomByUser(session->username);
    Res res;
    // Player;
    int i = 0;
    for (i = 0; i < room->curUser; i++)
    {
        if (strcmp(room->players[i].name, session->username) == 0)
        {
            room->players[i].cardSize -= data.cardSize;
            break;
        }
    }
    if (room->players[i].cardSize == 0)
    {
        room->isPlaying = false;
        room->players[i].point++;
        exportPoint(room->players[i].name, room->players[i].point);
    }
    room->lastTurn = i;
    printf("Turn: %s-%d->%s-%d\n", room->players[i].name, i, room->players[(i + 1) % (room->curUser)].name, (i + 1) % (room->curUser));
    res = createPlayResponse((i + 1) % (room->curUser), room->curUser, room->players, data.cardSize, data.cards);
    exportRoom(room);
    for (int j = 0; j < room->curUser; j++)
    {
        sendResponse(room->users[j]->sockfd, res);
    }
}
void skipHandler(int sockfd, Req req)
{
    Session session = getSessionBySockfd(sockfd);
    Room room = findRoomByUser(session->username);
    Res res;
    // Player
    int i = 0;
    for (i = 0; i < room->curUser; i++)
    {
        if (strcmp(room->players[i].name, session->username) == 0)
        {
            break;
        }
    }
    char lastTurn[20];
    strcpy(lastTurn, room->players[room->lastTurn].name);
    printf("skip user: %s, last turn: %s\n", session->username, lastTurn);
    res = createSkipResponse(room->players[i].name, lastTurn);
    for (int j = 0; j < room->curUser; j++)
    {
        sendResponse(room->users[j]->sockfd, res);
    }
}
#endif // REQUEST_HANDLER_H_
