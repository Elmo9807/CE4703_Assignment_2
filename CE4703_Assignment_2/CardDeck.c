/**
 * @file CardDeck.c
 * @brief Implementation of CardDeck data type operations
 *
 * @author Finnian Berry [Primary]
 * @author Logan Fan [Secondary]
 * @author Dylan O'Halloran [Debugging, dynamic memory allocations]
 *
 * @date 26/11/2025
 *
 * Group_1_Assignment_2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CardDeck.h"
#include "Card.h"

Deck* createDeck(size_t capacity) 
{
    /* Allocate memory for the Deck structure itself */
    Deck* deck = malloc(sizeof(Deck));

    if (deck == NULL) {
        return NULL;  /* Memory allocation failed */
    }

    /* Initialize deck to empty state */
    deck->size = 0;
    deck->capacity = capacity;

    /* Allocate memory for the dynamic card array */
    deck->cards = malloc(sizeof(Card) * capacity);

    if (deck->cards == NULL) {
        free(deck);  /* Clean up partially allocated memory */
        return NULL;
    }

    return deck;
}

size_t getDeckSize(const Deck* deck) 
{
    if (deck == NULL) {
        return 0;  /* Return 0 for NULL deck */
    }

    return deck->size;
}

void destroyDeck(Deck** deck) 
{
    if (deck == NULL || *deck == NULL) {
        return;
    }
    free((*deck)->cards);  /* Free cards array */
    free(*deck);           /* Free deck structure */
    *deck = NULL;          /* Set pointer to NULL */
}

int addCardTop(Deck* deck, Card card) 
{
    /* Validate deck pointer */
    if (deck == NULL) {
        return 0;
    }

    /* Check if we need to expand capacity */
    if (deck->size >= deck->capacity) {
        /* Double the capacity for efficient amortized growth */
        size_t newCapacity = deck->capacity * 2;
        if (newCapacity < 52) {
            newCapacity = 52;  /* Minimum capacity of one pack */
        }

        /* Attempt to reallocate with larger capacity */
        Card* newCards = deck->cards;
        newCards = (Card*)realloc(deck->cards, newCapacity * sizeof(Card));
        if (newCards == NULL) {
            return 0;  /* Reallocation failed - original deck unchanged */
        }

        /* Update deck to use new larger array */
        deck->cards = newCards;
        deck->capacity = newCapacity;
    }

    /* Add card to the top position (end of array) */
    deck->cards[deck->size] = card;
    deck->size++;
    return 1;
}

int addCardRandom(Deck* deck, Card card) 
{
    if (deck == NULL) {
        return 0;
    }

    /* Expand capacity if needed (same logic as addCardTop) */
    if (deck->size >= deck->capacity) {
        size_t newCapacity = deck->capacity * 2;
        if (newCapacity < 52) {
            newCapacity = 52;
        }

        /* Attempt to reallocate with larger capacity */
        Card* newCards = deck->cards;
        newCards = (Card*)realloc(deck->cards, newCapacity * sizeof(Card));
        if (newCards == NULL) {
            return 0;  /* Reallocation failed */
        }
        deck->cards = newCards;
        deck->capacity = newCapacity;
    }

    /* Generate random position from 0 to size (inclusive) */
    size_t pos = rand() % (deck->size + 1);

    /* Shift all cards from pos onwards one position right */
    for (size_t i = deck->size; i > pos; i--) {
        deck->cards[i] = deck->cards[i - 1];
    }

    /* Insert new card at the random position */
    deck->cards[pos] = card;
    deck->size++;
    return 1;
}

int removeCardTop(Deck* deck, Card* card) 
{
    if (deck == NULL || card == NULL || deck->size <= 0) {
        return 0;  /* Returns 0 if the deck is either NULL or empty */
    }
    *card = deck->cards[deck->size - 1];  /* Removes card from top of the deck */
    deck->size--;  /* Decreases size of the deck */
    return 1;
}

int removeCardRandom(Deck* deck, Card* card) 
{
    if (deck == NULL || card == NULL || deck->size <= 0) {
        return 0;  /* Returns 0 if deck is NULL or empty */
    }

    /* Generate random index within current deck size */
    size_t pos = rand() % deck->size;

    /* Copy the card at random position to output parameter */
    *card = deck->cards[pos];

    /* Shift all cards after pos one position left to fill gap */
    for (size_t i = pos; i < deck->size - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }

    /* Decrease size after shifting (important to do outside loop) */
    deck->size--;
    return 1;
}

int findAndRemove(Deck* deck, const Card* target) 
{
    /* Linear search through deck for matching card */
    for (size_t i = 0; i < deck->size; i++) {
        /* Use Card_compare to check for exact match */
        if (Card_compare(&deck->cards[i], target) == 0) {
            /* Found the target card - now remove it by shifting */
            for (size_t j = i; j < deck->size - 1; j++) {
                deck->cards[j] = deck->cards[j + 1];
            }
            deck->size--;
            return 1;  /* Successfully found and removed */
        }
    }
    return 0;  /* Card not found in deck */
}

const Card* peekTop(const Deck* deck) 
{
    if (deck == NULL || deck->size == 0) {
        return NULL;
    }
    return &deck->cards[deck->size - 1];
}

void shuffleDeck(Deck* deck) 
{
    /* Validate deck and ensure it has cards to shuffle */
    if (deck == NULL || deck->size <= 1) {
        return;
    }

    /* Fisher-Yates shuffle algorithm */
    /* Iterate backwards from last card to second card */
    for (size_t i = deck->size - 1; i > 0; i--) {
        /* Pick random index from 0 to i (inclusive) */
        size_t j = rand() % (i + 1);

        /* Swap cards at positions i and j */
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

void sortDeck(Deck* deck) 
{
    /* Check for invalid or trivially sorted cases */
    if (deck == NULL || deck->size <= 1) {
        return;
    }

    /* Bubble Sort algorithm - sorts by rank (primary) then suit (secondary) */
    /* Outer loop: number of passes through the array */
    for (size_t i = 0; i < deck->size - 1; i++) {
        /* Inner loop: compare adjacent elements, largest bubbles to end */
        for (size_t j = 0; j < deck->size - i - 1; j++) {
            /* Compare adjacent cards using Card_compare */
            if (Card_compare(&deck->cards[j], &deck->cards[j + 1]) > 0) {
                /* Cards are out of order - swap them */
                Card temp = deck->cards[j];
                deck->cards[j] = deck->cards[j + 1];
                deck->cards[j + 1] = temp;
            }
        }
    }
}

int transferAll(Deck* dest, Deck* src) 
{
    if (dest == NULL || src == NULL) {
        return 0;  /* Returns 0 if either deck is NULL */
    }

    /* Check if destination has enough capacity for all cards */
    if (dest->size + src->size > dest->capacity) {
        /* Calculate exact capacity needed */
        size_t newCapacity = dest->size + src->size;

        /* Reallocate destination deck to fit all cards */
        Card* newCards = dest->cards;
        newCards = (Card*)realloc(dest->cards, newCapacity * sizeof(Card));
        if (newCards == NULL) {
            return -1;  /* Reallocation failed */
        }
        dest->cards = newCards;
        dest->capacity = newCapacity;
    }

    /* Copy all cards from source to destination */
    for (size_t i = 0; i < src->size; i++) {
        dest->cards[dest->size + i] = src->cards[i];
    }

    /* Update deck sizes */
    int transferred = (int)src->size;
    dest->size += src->size;
    src->size = 0;  /* Empty the source deck */

    return transferred;
}

void printDeck(const Deck* deck) 
{
    /* If deck is empty then returns */
    if (deck->size == 0) {
        printf("Deck is empty\n");
        return;
    }
    /* Iterates through deck of cards and prints */
    printf("Deck (%zu cards): \n", deck->size);  /* %zu for size_t */
    for (size_t i = 0; i < deck->size; i++) {
        printf(" [%zu] ", i);  /* %zu for size_t */
        Card_print(&deck->cards[i]);
        printf("\n");
    }
}