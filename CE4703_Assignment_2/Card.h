/**
 * @file Card.h
 * @brief Header file for Card data type
 * @author Xinyue Chang
 *
 * @date 17/11/2025
 *
 * Group_1_Assignment_2
 * 
 * This file defines the Card data type for a standard deck of playing cards
 * A Card consists of a Suit (Club, Spade, Heart, Diamond) 
 * and a Rank (Two through Ace)
 */

#ifndef CARD_H
#define CARD_H

#include <stddef.h> /* size_t */

 /**
  * @brief Enumeration for card ranks
  * Represents ranks from Two (2) to Ace (14) using numeric values
  */
typedef enum 
{
    RANK_TWO = 2,
    RANK_THREE,
    RANK_FOUR,
    RANK_FIVE,
    RANK_SIX,
    RANK_SEVEN,
    RANK_EIGHT,
    RANK_NINE,
    RANK_TEN,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE
} Rank;

/**
 * @brief Enumeration for card suits
 * Represents the four suits in a standard deck of cards
 */
typedef enum 
{
    CLUB = 0, 
    SPADE = 1,  
    HEART = 2,  
    DIAMOND = 3 
} Suit;

/**
 * @brief Structure representing a playing card
 * A Card contains a Suit and a Rank, representing one card from a standard 52-card deck
 */
typedef struct 
{
    Suit suit;   
    Rank rank;   
} Card;

/**
 * @brief Convert a Card to a string
 * @param c Pointer to the card (must not be NULL)
 * @param buf Buffer to receive the string
 * @param buf_size Size of buf (bytes), recommend >= 16
 */
void Card_toString(const Card* c, char* buf, size_t buf_size);

/**
 * @brief Print a card to the console (convenience wrapper)
 * @param c Pointer to the card (must not be NULL)
 */
void Card_print(const Card* c);

/**
  * @brief Print a card to the console (test function)
  * @param c Pointer to the card (must not be NULL)
  */
void printCard(const Card* c);

/**
 * @brief Check if two cards match (same suit or same rank)
 * @param a Pointer to first card
 * @param b Pointer to second card
 * @return 1 if cards match, 0 otherwise
 */
int Card_matches(const Card* a, const Card* b);

/**
 * @brief Check if two cards are exactly equal (same rank and suit)
 * @param a Pointer to first card
 * @param b Pointer to second card
 * @return 1 if equal, 0 otherwise
 */
int Card_equal(const Card* a, const Card* b);

/**
 * @brief Compare two cards for sorting (rank primary, suit secondary)
 * @param a Pointer to first card
 * @param b Pointer to second card
 * @return negative if a < b, 0 if equal, positive if a > b
 */
int Card_compare(const Card* a, const Card* b);

#endif



