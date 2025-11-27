/**
 * @file Card.c
 * @brief Implementation of Card data type operations
 * 
 * @author Xinyue Chang
 * @author Dylan O'Halloran
 *
 * @date 27/11/2025
 *
 * Group_1_Assignment_2
 * 
 * This file implements the operations for the Card data type.
 */

#include <stdio.h>
#include <string.h>
#include "Card.h"

void Card_toString(const Card* c, char* buf, size_t buf_size)
{
    /* Local arrays for names, encapsulated in function scope, map enum values to readable names */
    const char* const SUIT_NAMES[] =
    {
        "Club", "Spade", "Heart", "Diamond"
    };
    const char* const RANK_NAMES[] =
    {
        /* 0~1 unused so index == numeric rank */
        "", "", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
    };

    /* Validate input */
    if (c == NULL || buf == NULL || buf_size == 0) {
        return;
    }

    /* Default names as fallback for invalid rank or suit */
    const char* sname = "?";
    const char* rname = "?";

    /* Validate suit index */
    if ((int)c->suit >= CLUB && (int)c->suit <= DIAMOND) {
        sname = SUIT_NAMES[(int)c->suit];
    }

    /* Validate rank index */
    if ((int)c->rank >= RANK_TWO && (int)c->rank <= RANK_ACE) {
        rname = RANK_NAMES[(int)c->rank];
    }

    /* safe formatting, no buf overflow */
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
    /* Null pointer handling, consider Null less than non Null*/
    if (a == NULL || b == NULL) {
        if (a == b) {
            return 0;
        }
        return (a == NULL) ? -1 : 1;
    }

    /* Cmp rank, lower rank < higher rank */
    if (a->rank < b->rank) {
        return -1;
    }
    else if (a->rank > b->rank) {
        return 1;
    }

    /* ranks equal -> compare suit order, CLUB < SPADE < HEART < DIAMOND */
    if (a->suit < b->suit) {
        return -1;
    }
    else if (a->suit > b->suit) {
        return 1;
    }
    return 0;
}


