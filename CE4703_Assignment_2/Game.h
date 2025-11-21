/**
 * @file Game.h
 * @brief
 * 
 * @author 'ADD YOUR NAME HERE'
 * 
 * @date ADD YOUR COMPLETION DATA HERE
 *
 * Group_1_Assignment_2
 */

#ifndef GAME_H
#define GAME_H

#include "CardDeck.h"
#include "Card.h"

/**
 * @brief Initialize the game state
 * Creates the hidden deck, player decks, deals cards, etc
 *
 * @param numberOfPacks How many 52-card packs to use
 */
void Game_init(int numberOfPacks);

/**
 * @brief Run the gameplay loop until one player wins
 */
void Game_play(void);

/**
 * @brief Free memory and clean up all game data structures
 */
void Game_cleanup(void);

#endif

