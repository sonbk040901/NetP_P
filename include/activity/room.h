#if !defined(ACTIVITY_ROOM_H_)
#define ACTIVITY_ROOM_H_
#include "index.h"
#include "utils.h"
extern int clientfd;
/**
 * @brief process find room
 *
 * @param key
 * @param roomSize output room size
 * @param room  output room
 * @return true (if find room success)
 * @return false (if find room failed)
 */
bool processFindRoom(char *key, int *roomSize, RoomInfo room[100]);
bool processCreateRoom(char *roomName, int maxPlay, char *message);
bool processJoinRoom();

//
bool processFindRoom(char *key, int *roomSize, RoomInfo room[100])
{
    Req req = createFindRoomRequest(key);
    int bytes = sendRequest(clientfd, req);
    if (bytes < 0)
    {
        return false;
    }
    if (bytes == 0)
    {
        return false;
    }
    Res res;
    bytes = recvResponse(clientfd, &res);
    if (bytes < 0)
    {
        return false;
    }
    if (bytes == 0)
    {
        return false;
    }
    *roomSize = res.data.findRoom.roomSize;
    for (int i = 0; i < *roomSize; i++)
    {
        room[i] = res.data.findRoom.room[i];
    }
    return true;
}
bool processCreateRoom(char *roomName, int maxPlayer, char *message)
{
    if (!validateRoomName(roomName, message))
    {
        return false;
    }
    if (validateMaxPlayer(maxPlayer, message))
    {
        return false;
    }
    Req req = createCreateRoomRequest(roomName, maxPlayer);
    int bytes = sendRequest(clientfd, req);
    if (bytes < 0)
    {
        strcpy(message, "Error sending request");
        return false;
    }
    if (bytes == 0)
    {
        strcpy(message, "Connection closed");
        return false;
    }
    Res res;
    bytes = recvResponse(clientfd, &res);
    if (bytes < 0)
    {
        strcpy(message, "Error receiving response");
        return false;
    }
    if (bytes == 0)
    {
        strcpy(message, "Connection closed");
        return false;
    }
    bool isSuccess = res.data.resR.success;
    strcpy(message, res.data.resR.message);
    return isSuccess;
}
bool processJoinRoom() {}
#endif // ACTIVITY_ROOM_H_
