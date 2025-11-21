/**
 * @file Card.c
 * @brief Implementation of Card data type operations
 * 
 * @author Xinyue Chang
 *
 * @date 17/11/2025
 *
 * Group_1_Assignment_2
 * 
 * This file implements the operations for the Card data type.
 */

 /**
 * Remind Team Person Tester:
 * When you test use
 * printCard(&card);
 */

#include <stdio.h>
#include <string.h>
#include "Card.h"

  /* Local arrays for names */
static const char* const SUIT_NAMES[] = 
{ 
    "Club", "Spade", "Heart", "Diamond" 
};
static const char* const RANK_NAMES[] = 
{
    /* 0~1 unused so index == numeric rank */
    "", "", "Two", "Three", "Four", "Five", "Six", "Seven",
    "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
};

void Card_toString(const Card* c, char* buf, size_t buf_size){
    if (c == NULL || buf == NULL || buf_size == 0) {
        return;
    }

    const char* sname = "?";
    const char* rname = "?";

    if ((int)c->suit >= 0 && (int)c->suit <= 3) {
        sname = SUIT_NAMES[(int)c->suit];
    }

    if ((int)c->rank >= 2 && (int)c->rank <= 14) {
        rname = RANK_NAMES[(int)c->rank];
    }

    /* safe formatting */
    snprintf(buf, buf_size, "%s-%s", sname, rname);
}

void Card_print(const Card* c) 
{
    char buf[32];
    Card_toString(c, buf, sizeof(buf));
    printf("%s", buf);
}

    /* for test */
void printCard(const Card* c)
{
    Card_print(c);
}

int Card_matches(const Card* a, const Card* b) 
{
    if (a == NULL || b == NULL) {
        return 0;
    }
    return (a->rank == b->rank) || (a->suit == b->suit);
}

int Card_equal(const Card* a, const Card* b)
{
    if (a == NULL || b == NULL) {
        return 0;
    }
    return (a->rank == b->rank) && (a->suit == b->suit);
}

int Card_compare(const Card* a, const Card* b)
{
    if (a == NULL || b == NULL) {
        if (a == b) {
            return 0;
        }
        return (a == NULL) ? -1 : 1;
    }

    if (a->rank < b->rank) {
        return -1;
    }
    else if (a->rank > b->rank) {
        return 1;
    }

    /* ranks equal -> compare suit order */
    if (a->suit < b->suit) {
        return -1;
    }
    else if (a->suit > b->suit) {
        return 1;
    }
    return 0;
}


