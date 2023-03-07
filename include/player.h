#ifndef PLAYER_H_
#define PLAYER_H_
typedef struct _player
{
    char name[20];
    int cardSize; // 0-13 number of cards in player's hand
    char point;
} Player;
#endif // PLAYER_H_