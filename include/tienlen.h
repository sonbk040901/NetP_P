#ifndef TIENLEN_H_
#define TIENLEN_H_
#include <string.h>
#include <stdlib.h>
#define CARD_SUIT_SIZE 4
#define CARD_VALUE_SIZE 13
#define CARD_SIZE 52
#define MAX_PLAYER 4
typedef enum _cardSuit
{
    SPADE = 0,
    CLUB,
    DIAMOND,
    HEART
} CardSuit;
typedef enum _cardValue
{
    THREE = 0,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    TWO,
} CardValue;
typedef struct _card
{
    CardSuit suit;
    CardValue value;
} Card;
const char CARD_SUIT[][4] = {"♠", "♣", "♦", "♥"};
const char CARD_VALUE[][3] = {"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2"};
const char CARD_TEMPLATE[][10] = {"3♠", "3♣", "3♦", "3♥", "4♠", "4♣", "4♦", "4♥", "5♠", "5♣", "5♦", "5♥", "6♠", "6♣", "6♦", "6♥", "7♠", "7♣", "7♦", "7♥", "8♠", "8♣", "8♦", "8♥", "9♠", "9♣", "9♦", "9♥", "10♠", "10♣", "10♦", "10♥", "J♠", "J♣", "J♦", "J♥", "Q♠", "Q♣", "Q♦", "Q♥", "K♠", "K♣", "K♦", "K♥", "A♠", "A♣", "A♦", "A♥", "2♠", "2♣", "2♦", "2♥"};
/* @brief create a card with suit and value
 * @param suit CardSuit
 * @param value CardValue
 * @return Card
 */
Card createCard(CardSuit, CardValue);
/// @brief get suit of a card
/// @param card Card
/// @return CardSuit
CardSuit getCardSuit(Card);
/// @brief get value of a card
/// @param card Card
/// @return CardValue
CardValue getCardValue(Card);
/// @brief get string representation of a card
/// @param card Card
/// @return const char *
const char *cardToString(Card);
/// @brief get string representation of a card array
/// @param card Card
/// @param size int
/// @param str char * (output)
/// @deprecated
void cardsToString(Card *, int, char *);
/// @brief convert string to card array
/// @param str char *
/// @param cards Card * (output)
/// @param cardSize int * (output)
void stringToCards(char *, Card *, int *);
void indexToCard(int index, Card *card);

Card createCard(CardSuit suit, CardValue value)
{
    Card card;
    card.suit = suit;
    card.value = value;
    return card;
}
CardSuit getCardSuit(Card card)
{
    return card.suit;
}
CardValue getCardValue(Card card)
{
    return card.value;
}
const char *cardToString(Card card)
{
    return CARD_TEMPLATE[(card.suit) + (card.value) * CARD_SUIT_SIZE];
}
void cardsToString(Card *cards, int size, char *str)
{
    for (int i = 0; i < size; i++)
    {
        if (cards[i].value != -1)
        {
            strcat(str, cardToString(cards[i]));
            strcat(str, "&");
        }
    }
}

void stringToCards(char *str, Card *cards, int *cardSize)
{
    char *token = strtok(str, "&");
    *cardSize = 0;
    while (token != NULL)
    {
        for (int j = 0; j < CARD_SIZE; j++)
        {
            if (strcmp(token, CARD_TEMPLATE[j]) == 0)
            {
                cards[*cardSize] = createCard(j / CARD_SUIT_SIZE, j % CARD_SUIT_SIZE);
                (*cardSize)++;
                break;
            }
        }
        token = strtok(NULL, "&");
    }
}
void indexToCard(int index, Card *card)
{
    card->suit = index % CARD_SUIT_SIZE;
    card->value = index / CARD_SUIT_SIZE;
}
#endif // TIENLEN_H_