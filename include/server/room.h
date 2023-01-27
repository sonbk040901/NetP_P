#if !defined(ROOM_H_)
#define ROOM_H_
#include "session.h"
typedef struct _Room
{
    char name[127];
    int id;
    int maxUser;
    int curUser;
    Session users[4];
} *Room;
Dllist rooms = NULL;
Room newRoom(char *name, int maxUser);
void addRoom(Room room);
void freeRoom(Room room);
void freeRoomList();
Room findRoom(int id);
Room findRoomByName(char *name);
Room findRoomByUser(char *username);
bool joinRoom(Room room, Session session);
bool leaveRoom(Room room, Session session);
bool isRoomFull(Room room);
int getRoomCount();
int randRoomId();

int randRoomId()
{
    int id = 0;
    while (true)
    {
        id = rand() % 10000;
        if (findRoom(id) == NULL)
        {
            break;
        }
    }
    return id;
}
Room newRoom(char *name, int maxUser)
{
    if (!rooms)
    {
        rooms = new_dllist();
    }

    if (maxUser > 4 || maxUser < 1)
    {
        return NULL;
    }

    int id = randRoomId();
    Room room = (Room)malloc(sizeof(struct _Room));
    *room = (struct _Room){
        .name = {0},
        .id = id,
        .maxUser = maxUser,
        .curUser = 0,
        .users = {0}};
    strcpy(room->name, name);
    return room;
}
void addRoom(Room room)
{
    dll_append(rooms, new_jval_v(room));
}
void freeRoom(Room room)
{
    free(room);
}
void freeRoomList()
{
    Dllist ptr;
    dll_traverse(ptr, rooms)
    {
        freeRoom((Room)jval_v(ptr->val));
    }
    free_dllist(rooms);
}

Room findRoom(int id)
{
    Dllist ptr;
    dll_traverse(ptr, rooms)
    {
        Room room = (Room)jval_v(ptr->val);
        if (room->id == id)
        {
            return room;
        }
    }
    return NULL;
}

Room findRoomByName(char *name)
{
    Dllist ptr;
    dll_traverse(ptr, rooms)
    {
        Room room = (Room)jval_v(ptr->val);
        if (strcmp(room->name, name) == 0)
        {
            return room;
        }
    }
    return NULL;
}

Room findRoomByUser(char *username)
{
    Dllist ptr;
    dll_traverse(ptr, rooms)
    {
        Room room = (Room)jval_v(ptr->val);
        for (int i = 0; i < room->curUser; i++)
        {
            if (strcmp(room->users[i]->username, username) == 0)
            {
                return room;
            }
        }
    }
    return NULL;
}

bool joinRoom(Room room, Session session)
{
    if (room->curUser >= room->maxUser)
    {
        return false;
    }
    room->users[room->curUser++] = session;
    return true;
}

bool leaveRoom(Room room, Session session)
{
    for (int i = 0; i < room->curUser; i++)
    {
        if (room->users[i] == session)
        {
            for (int j = i; j < room->curUser - 1; j++)
            {
                room->users[j] = room->users[j + 1];
            }
            room->curUser--;
            return true;
        }
    }
    return false;
}

bool isRoomFull(Room room)
{
    return room->curUser >= room->maxUser ? true : false;
}

int getRoomCount()
{
    int count = 0;
    Dllist ptr;
    dll_traverse(ptr, rooms)
    {
        count++;
    }
    return count;
}

#endif // ROOM_H_
