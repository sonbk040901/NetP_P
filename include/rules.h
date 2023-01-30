#if !defined(_GAME_RULES_H_)
#define _GAME_RULES_H_
#include "tienlen.h"
#include <stdbool.h>
typedef enum bai_danh_xuong
{
    BaiLoi,
    Don,
    Doi,
    BoBa,
    Sanh,
    BaDoiThong,
    TuQuy,
    BonDoiThong

} BaiDanhXuong;
typedef struct _cards
{
    BaiDanhXuong NameOfGroupCards;
    int NumberOfGroupCards;
    Card cards[CARD_SIZE / MAX_PLAYER];
} InforCards;
int valueOfCard(Card card);
InforCards xepBai(InforCards cards);
bool checkDon(InforCards cards);
bool checkDoi(InforCards cards);
bool checkBoBa(InforCards cards);
bool checkSanh(InforCards cards);
bool checkBaDoiThong(InforCards cards);
bool checkTuQuy(InforCards cards);
bool checkBonDoiThong(InforCards cards);
BaiDanhXuong checkBaiDanhXuong(InforCards cards);
bool checkValid(InforCards previous, InforCards present);
// Các hàm kiểm tra bài:
// B1: Xếp bài
// B2: Kiểm tra bài xem bài đó thuộc loại bài nào hay bài lỗi
// B3: Kiểm tra bài đó có hợp lệ hay không

int valueOfCard(Card card)
{
    return card.value * 4 + card.suit;
}
InforCards xepBai(InforCards cards)
{
    int sll = cards.NumberOfGroupCards;
    for (int i = 0; i < sll; i++)
    {
        for (int j = 0; j < sll - 1; j++)
        {
            if (valueOfCard(cards.cards[j]) > valueOfCard(cards.cards[j + 1]))
            {
                Card tmpCard = cards.cards[j];
                cards.cards[j] = cards.cards[j + 1];
                cards.cards[j + 1] = tmpCard;
            }
        }
    }
    return cards;
}
BaiDanhXuong checkBaiDanhXuong(InforCards cards)
{
    if (checkDon(cards))
    {
        return Don;
    }
    if (checkDoi(cards))
    {
        return Doi;
    }
    if (checkBoBa(cards))
    {
        return BoBa;
    }
    if (checkSanh(cards))
    {
        return Sanh;
    }
    if (checkBaDoiThong(cards))
    {
        return BaDoiThong;
    }
    if (checkTuQuy(cards))
    {
        return TuQuy;
    }
    if (checkBonDoiThong(cards))
    {
        return BonDoiThong;
    }
    return BaiLoi;
}
bool checkDon(InforCards cards)
{
    return cards.NumberOfGroupCards == 1;
}
bool checkDoi(InforCards cards)
{
    if (cards.NumberOfGroupCards != 2)
    {
        return false;
    }
    return cards.cards[0].value == cards.cards[1].value;
}
bool checkBoBa(InforCards cards)
{
    if (cards.NumberOfGroupCards != 3)
    {
        return false;
    }
    return cards.cards[0].value == cards.cards[1].value && cards.cards[1].value == cards.cards[2].value;
}
bool checkSanh(InforCards cards)
{
    if (cards.NumberOfGroupCards <= 2)
        return false;

    if (cards.cards[cards.NumberOfGroupCards - 1].value == TWO)
    {
        return false;
    }

    for (int i = 0; i < cards.NumberOfGroupCards - 1; i++)
    {
        if (cards.cards[i].value != cards.cards[i + 1].value - 1)
        {
            return false;
        }
    }
    return true;
}
bool checkBaDoiThong(InforCards cards)
{
    if (cards.NumberOfGroupCards != 6)
    {
        return false;
    }
    if (cards.cards[5].value == TWO)
    {
        return false;
    }

    for (int i = 0; i < 5; i += 2)
    {
        if (cards.cards[i].value != cards.cards[i + 1].value)
        {
            return false;
        }
    }

    if (cards.cards[1].value != cards.cards[2].value - 1 || cards.cards[3].value != cards.cards[4].value - 1)
    {
        return false;
    }
    return true;
}
bool checkTuQuy(InforCards cards)
{
    if (cards.NumberOfGroupCards != 4)
    {
        return false;
    }
    CardValue value = cards.cards[0].value;
    for (int i = 1; i < 4; i++)
    {
        if (cards.cards[i].value != value)
        {
            return false;
        }
    }
    return true;
}
bool checkBonDoiThong(InforCards cards)
{
    if (cards.NumberOfGroupCards != 8)
    {
        return false;
    }
    if (cards.cards[7].value == TWO)
    {
        return false;
    }

    for (int i = 0; i < 7; i += 2)
    {
        if (cards.cards[i].value != cards.cards[i + 1].value)
        {
            return false;
        }
    }
    for (int i = 1; i < 8; i += 2)
    {
        if (cards.cards[i].value != cards.cards[i + 1].value - 1)
        {
            return false;
        }
    }

    return true;
}

bool checkValid(InforCards previous, InforCards present)
{
    if (previous.NameOfGroupCards == BaiLoi || present.NameOfGroupCards == BaiLoi)
    {
        return false;
    }

    // cùng bộ
    if (previous.NameOfGroupCards == present.NameOfGroupCards)
    {
        if (previous.NameOfGroupCards != Sanh)
        {
            // printf("cho nay\n");
            if (valueOfCard(previous.cards[previous.NumberOfGroupCards - 1]) < valueOfCard(present.cards[present.NumberOfGroupCards - 1]))
            {
                return 1;
            }
            else
                return 0;
        }
        else if (previous.NumberOfGroupCards > present.NumberOfGroupCards || valueOfCard(previous.cards[previous.NumberOfGroupCards - 1]) > valueOfCard(present.cards[present.NumberOfGroupCards - 1]) || previous.cards[0].value > present.cards[0].value)
        {
            return 0;
        }
        else
            return 1;
    }
    // khác bộ:
    if (previous.NameOfGroupCards == Don)
    {
        if (previous.cards[0].value == TWO) // neu la cay 2
        {
            if (present.NameOfGroupCards == BaDoiThong || present.NameOfGroupCards == BonDoiThong || present.NameOfGroupCards == TuQuy)
            {
                return 1;
            }
            else
                return 0;
        }
    }
    else if (previous.NameOfGroupCards == Doi)
    {
        if (previous.cards[0].value == TWO)
        {
            if (present.NameOfGroupCards == TuQuy || present.NameOfGroupCards == BonDoiThong)
            {
                return 1;
            }
            else
                return 0;
        }
        else if (previous.cards[0].value != TWO)
        {
            if (present.NameOfGroupCards == BonDoiThong)
            {
                return 1;
            }
            else
                return 0;
        }
    }
    else if (previous.NameOfGroupCards == BaDoiThong)
    {
        if (present.NameOfGroupCards == BonDoiThong)
        {
            return 1;
        }
    }
    return 0;
}
#endif // _GAME_RULES_H_
