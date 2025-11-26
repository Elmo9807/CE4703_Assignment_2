/**
 * @file CardDeck.h
 * @brief Header file for CardDeck data type
 *
 * @author Finnian Berry
 * @author Logan Fan
 * @author Dylan O'Halloran
 *
 * @date 21/11/2025
 *
 * Group_1_Assignment_2
 * 
 * This file defines the CardDeck data type, which represents a dynamic
 * collection of cards. The CardDeck uses dynamic memory allocation to
 * support any number of cards from 0 to multiple complete packs
 * If can not use dynamic array, use linked list 
 *
 * The CardDeck data structure consists of:
 * 1. Dynamic array of Card structures
 * 2. Current size (number of cards in the deck)
 * 3. Maximum capacity (can be expanded dynamically)
 *
 * Operations supported include:
 * 1. Adding and removing cards from either top or random position
 * 2. Shuffling and sorting
 * 3. Transferring cards between decks
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

/**
*@brief Creates a new empty deck with a specified capacity.
* @param capacity The max number of cards the deck can hold.
* @return Pointer to the newly created deck, or NULL on failure.
*/
Deck* createDeck(int capacity);


/**
*@brief Gets the current number of cards in the deck.
* @param Pointer to the deck.
* @return The number of cards in the deck, or -1 if the deck is NULL.
*/
int getDeckSize(const Deck* deck);

/**
*@brief Destroys the deck and frees all associated memory.
*@param deck Double pointer to the deck to be destroyed.
* @return void.
*/
void destroyDeck(Deck** deck);


/**
*@brief Adds a card to the top of the deck.
* @param deck Pointer to the deck cards will be added to.
* @param card The card that will be added.
* @return 1 if the card was added successfully, 0 otherwise.
*/
int addCardTop(Deck* deck, Card card);


/**
*@brief Adds a card to a random position in the deck.
* @param deck Pointer to the deck cards will be randomly added to.
* @param card The card that will be added.
* @return 1 if the card was added successfully, 0 otherwise.
*/
int addCardRandom(Deck* deck, Card card);


/**
*@brief Removes a card from the top of the deck.
*@param deck Pointer to the deck cards will be removed from.
* @param card Pointer to the card that will be removed.
* @return 1 if the card was removed successfully, 0 otherwise.
*/
int removeCardTop(Deck* deck, Card* card);

/**
*@brief Removes a card from a random position in the deck.
* @param deck Pointer to the deck cards will be randomly removed from.
* @param card Pointer to the cardd that will be removed.
* @return 1 if the card was removed successfully, 0 otherwise.
*/
int removeCardRandom(Deck* deck, Card* card);


/**
 * @brief Peek at the top card without removing it
 * @param deck Pointer to the deck
 * @return Pointer to the top card, or NULL if deck is empty
 */
const Card* peekTop(const Deck* deck);

/**
*@brief Transfers all cards from source deck to destination deck and clears source deck.
* @param dest Pointer to the destination deck.
* @param src Pointer to the source deck.
* @return 1 if the transfer was successful, 0 otherwise.
*/
int transferAll(Deck* dest, Deck* src);

/**
 * @brief Find and remove a specific card from the deck
 * @param deck Pointer to the deck
 * @param target Pointer to the card to find and remove
 * @return 1 if card was found and removed, 0 otherwise
 */
int findAndRemove(Deck* deck, const Card* target);

/**
 * @brief Shuffle the deck randomly using Fisher-Yates algorithm
 * @param deck Pointer to the deck to shuffle
 */
void shuffleDeck(Deck* deck);

/**
 * @brief Sort the deck using Bubble Sort (rank primary, suit secondary)
 * @param deck Pointer to the deck to sort
 */
void sortDeck(Deck* deck);

/**
 * @brief Print all cards in the deck to console
 * @param deck Pointer to the deck to print
 */
void printDeck(const Deck* deck);

#endif