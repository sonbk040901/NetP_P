#ifndef ROOM_INFO_H_
#define ROOM_INFO_H_
#include <string.h>
typedef struct _roomInfo
{
    int id;
    char roomName[20];
    char owner[20];
    char maxPlayer;
    char currentPlayer;
    char status; // 0: waiting, 1: playing
} RoomInfo;
/// @brief
/// @param roomName
/// @param maxPlayer
/// @param currentPlayer
/// @param status 0: waiting, 1: playing
/// @return
RoomInfo createRoomInfo(int id, char *roomName, char *owner, int maxPlayer, int currentPlayer, int status)
{
    RoomInfo roomInfo;
    roomInfo.id = id;
    strcpy(roomInfo.roomName, roomName);
    strcpy(roomInfo.owner, owner);
    roomInfo.maxPlayer = maxPlayer;
    roomInfo.currentPlayer = currentPlayer;
    roomInfo.status = status;
    return roomInfo;
}
#endif