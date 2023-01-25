#ifndef ROOM_INFO_H_
#define ROOM_INFO_H_
#include <string.h>
typedef struct _roomInfo
{
    char roomName[20];
    int maxPlayer;
    int currentPlayer;
    int status; // 0: waiting, 1: playing
} RoomInfo;
/// @brief
/// @param roomName
/// @param maxPlayer
/// @param currentPlayer
/// @param status 0: waiting, 1: playing
/// @return
RoomInfo createRoomInfo(char *roomName, int maxPlayer, int currentPlayer, int status)
{
    RoomInfo roomInfo;
    strcpy(roomInfo.roomName, roomName);
    roomInfo.maxPlayer = maxPlayer;
    roomInfo.currentPlayer = currentPlayer;
    roomInfo.status = status;
    return roomInfo;
}
#endif