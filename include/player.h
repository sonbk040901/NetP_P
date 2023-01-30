#ifndef PLAYER_H_
#define PLAYER_H_
typedef struct _player
{
    char name[127];
    int cardSize; // 0-13 number of cards in player's hand
} Player;
#endif // PLAYER_H_