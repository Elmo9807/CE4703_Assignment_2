/**
 * @file Game.h
 * @brief Header file for game logic and gameplay functions
 * 
 * @author Hugh Murnane
 * @author Dylan O'Halloran
 * 
 * @date 25/11/2025
 *
 * Group_1_Assignment_2
 */

#ifndef GAME_H
#define GAME_H

#include "CardDeck.h"
#include "Card.h"

/* Game constants */
#define CARDS_PER_PACK 52
#define NUM_SUITS 4
#define MAX_PLAYERS 4
#define CARDS_PER_PLAYER 8


/**
 * @brief Initialize the game state
 * Creates the hidden deck, player decks, deals cards, etc
 *
 * @param numberOfPlayers How many players participating in the game
 * @param numberPacks Number of 52-card packs to use
 */
void startGame(int numberPlayers, int numberPacks);

/**
 * @brief Fill a deck with standard 52-card pack(s)
 * @param d Pointer to the deck to fill
 * @param packs Number of 52-card packs to add
 */
void fillDeck(Deck* d, int packs);

/**
 * @brief Reshuffle played cards back into hidden deck, keeping top card
 * @param hidden Pointer to the hidden deck
 * @param played Pointer to the played deck
 */
void reshuffleIntoDeck(Deck* hidden, Deck* played);

/**
 * @brief Print a player's current hand
 * @param playerNum The player number
 * @param hand Pointer to the player's deck
 */
void printPlayerHand(int playerNum, const Deck* hand);

#endif

