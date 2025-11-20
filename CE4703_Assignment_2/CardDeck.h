/**
 * @file CardDeck.h
 * @brief Header file for CardDeck data type
 * @author 'ADD YOUR NAME HERE'
 *
 * @date ADD YOUR COMPLETION DATA HERE
 *
 * Group_1_Assignment_2
 * 
 * This file defines the CardDeck data type, which represents a dynamic
 * collection of cards. The CardDeck uses dynamic memory allocation to
 * support any number of cards from 0 to multiple complete packs
 * If can not use dynamic array, use linked list 
 *
 * The CardDeck data structure consists of:
 * 1.
 * 2.
 * 3.
 *
 * Operations supported include:
 * 1.Adding and removing cards
 * 2.
 * 3.
 */


 /** Remind Team Person 3:
 *Rank increases from TWO to ACE
 * Suit enumeration order : CLUB < SPADE < HEART < DIAMOND
 * Should pay attention to the consistent order
 * when writing Card_compare() or sorting
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <stddef.h>

typedef struct {
    Card* cards;        /* Pointer to dynamic array of cards */
    int size;           /* Current number of cards in the deck */
    int capacity;       /* Maximum capacity of the deck */
} Deck;

Deck* createDeck(int capacity);

int getDeckSize(const Deck* deck);

void destroyDeck(Deck** deck);

int addCardTop(Deck* deck, Card card);

int addCardRandom(Deck* deck, Card card);

int removeCardTop(Deck* deck, Card* card);

int removeCardRandom(Deck* deck, Card* card);


/* Logan's */
const Card* peekTop(const Deck* deck);

int transferAll(Deck* dest, Deck* src);

int findAndRemove(Deck* deck, const Card* target);

void shuffleDeck(Deck* deck);

void sortDeck(Deck* deck);

void printDeck(const Deck* deck);

#endif /* DECK_H */