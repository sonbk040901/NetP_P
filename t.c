#include <stdio.h>
// #include "tienlen.h"
// #include "connect.h"
#include <signal.h>
#include <ctype.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <utils.h>
// struct test
// {
//     int a;
//     int b;
// };
// struct test f()
// {
//     struct test t;
//     t.a = 1;
//     t.b = 2;
//     return t;
// }
// const char *f1()
// {
//     return "Hello World!";
// }
void *test(void *data);
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// int i = 0;
void *test(void *data)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    for (int i = 0; i < 15; i++)
    {
        printf("%d test%d\n", i, (int)data);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *test2(void *data)
{
    for (int i = 0; i < 15; i)
    {
        pthread_mutex_lock(&mutex);
        if (i == 5)
        {
            pthread_cond_signal(&cond);
            puts("signal");
            // sleep(1);
            i++;
        }
        else
        {
            printf("%d test2\n", i++);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int generateID()
{
    static int s_id = 0;
    auto int b = 0;
    return ++s_id;
}
void print()
{
    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        printf("%s\n", "Hello World!");
    }
}
int main(int argc, char const *argv[])
{
    // Card card1 = createCard(DIAMOND, TEN);
    // Card card2 = createCard(HEART, KING);
    // Card card3 = createCard(SPADE, TWO);
    // Card cards[] = {card1, card2, card3};
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

    // Req req = createPlayRequest(cards, 3);
    // ReqD data = req.data;
    // PlayReqD playData = data.play;
    // for (int i = 0; i < playData.cardSize; i++)
    // {
    //     printf("Card %d: %d %d - %s\n", i + 1, playData.cards[i].suit, playData.cards[i].value, cardToString(playData.cards[i]));
    // }
    // return 0;
    // printf("%d\n", atoi(argv[1]));
    // pthread_t tid, tid1;
    // pthread_create(&tid, NULL, &print, NULL);
    // pthread_create(&tid1, NULL, test2, (void *)2);
    // pthread_cond_signal(&cond);
    // pthread_join(tid1, NULL);
    // pthread_join(tid, NULL);
    // pthread_detach(tid);
    // pthread_detach(tid1);
    // printf("Hello World 1!\n");
    // printf("Hello World 2!\n");
    // sleep(6);
    // pthread_cancel(tid);
    int result[52];
    randArray(0, 51, result, 52);
    for (int i = 0; i < 52; i++)
    {
        printf("%d ", result[i]);
    }
    puts("");
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