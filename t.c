#include <stdio.h>
#include "tienlen.h"
#include "connect.h"
#include <signal.h>
struct test
{
    int a;
    int b;
};
struct test f()
{
    struct test t;
    t.a = 1;
    t.b = 2;
    return t;
}
const char *f1()
{
    return "Hello World!";
}
int main(int argc, char const *argv[])
{
    Card card1 = createCard(DIAMOND, TEN);
    Card card2 = createCard(HEART, KING);
    Card card3 = createCard(SPADE, TWO);
    Card cards[] = {card1, card2, card3};
    // char str[100];
    // cardsToString(cards, 3, str);
    // printf("%s\n", str);
    // Card cards1[10];
    // int size;
    // stringToCards(str, cards1, &size);
    // printf("%d\n", size);
    // for (int i = 0; i < size; i++)
    // {
    //     printf("Card %d: %d %d\n", i + 1, cards[i].suit, cards[i].value);
    // }

    Req req = createPlayRequest(cards, 3);
    ReqD data = req.data;
    PlayReqD playData = data.play;
    for (int i = 0; i < playData.cardSize; i++)
    {
        printf("Card %d: %d %d - %s\n", i + 1, playData.cards[i].suit, playData.cards[i].value, cardToString(playData.cards[i]));
    }
    return 0;
}
// void f()
// {
//     puts("Hello World!");
// }
// int main()
// {
//     signal(SIGQUIT, (void *)f);
//     sleep(10000);
//     return (0);
// }