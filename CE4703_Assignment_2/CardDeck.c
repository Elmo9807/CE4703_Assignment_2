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
/**
* @brie Find and remove specific card 
*/

int findAndRemove(Deck* deck, const Card* target) {
    /* Search for the target */
    for (int i = 0; i < deck->size; i++) {
        if (Card_compare(&deck->cards[i], target) == 0) {
            /* Found card then shifts cards down */
            for (int j = i; j < deck->size - 1; j++) {
                deck->cards[j] = deck->cards[j + 1];
            }
            deck->size--;
            return 1;
        }
    }
    /* Returns 0 if card not found */
    return 0;
}


/**
* @brief Peeks at top card
*/
const Card* peekTop(const Deck* deck) {
    return &deck->cards[deck->size - 1];
}

/**
* @brief Shuffles deck randomly 
*/
void shuffleDeck(Deck* deck) {  
    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        /* swaps cards at position i and j */
        Card temp = deck->cards[i]; 
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp; 
    }
}

/**
* @brief Sorts deck in order using bubble sort 
* Card_Compare for (rank first then suit secondary)
*/
void sortDeck(Deck* deck) {
    /* Checks if deck is null or no of cards is 1 */
    if (deck == NULL || deck->size <= 1) { 
        return; 
    }
    /* Bubble Sort */
    for (int i = 0; i < deck->size - 1; i++) {
        for (int j = 0; j < deck->size - i - 1; j++) {
            /* Compares card rank and suit */
            if (Card_compare(&deck->cards[j], &deck->cards[j + 1]) > 0) {
                /* Uses temp to swap */
                Card temp = deck->cards[j];
                deck->cards[j] = deck->cards[j + 1];
                deck->cards[j + 1] = temp;
            }
        }
    }
}

/**
* @brief Prints all in deck 
*/
void printDeck(const Deck* deck) { 
    /* If deck == 0 then returns empty */
    if (deck->size == 0) {
        printf("Deck is empty\n");
        return;
    }
    /* Iterates through deck of cards and prints */
    printf(("Deck (%d cards): \n"), deck->size);
    for (int i = 0; i < deck->size; i++) {
        printf(" [%d] ", i);
        Card_print(&deck->cards[i]);
        printf("\n");
    }
}

//test file 
