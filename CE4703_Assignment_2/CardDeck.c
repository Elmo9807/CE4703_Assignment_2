/**
 * @file CardDeck.c
 * @brief Implementation of CardDeck data type operations
 * @author 'ADD YOUR NAME HERE'
 *
 * @date ADD YOUR COMPLETION DATA HERE
 * 
 * Group_1_Assignment_2
 * Remind Team Person 2: CardDeck example
 * //  Card c;
 * //  c.rank = RANK_SEVEN;
 * //  c.suit = HEART;
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CardDeck.h"
#include "Card.h"

Deck* createDeck(int capacity) { /* Function to create deck*/
Deck * deck = malloc(sizeof(Deck)); /*Allocating memory for deck*/

if (deck == NULL) { /*Checking if memory allocation was a success*/
    return NULL;
}
deck->size = 0; /*Initializing size to 0*/
deck->capacity = capacity; /* Setting capacity as input value*/
deck->cards = malloc(sizeof(Card) * capacity); /*Allocating memory for cards array*/
if (deck->cards == NULL) { /*Checking if memory allocation was successful*/
    free(deck);
    return NULL;
}
return deck; /*Returning pointer*/
}

int getDeckSize(const Deck* deck) { /*Function to get size of deck*/
    if (deck == NULL) { /*Checking if deck is NULL*/
        return -1;
    }

    return deck->size; /*Returns deck size*/
}


//test file
