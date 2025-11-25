/**
 * @file Game.c
 * @brief Creating the game that calls from Card.c and CardDeck.c
 *
 * @author Hugh Murnane
 * @date 25/11/2025
 */

 /**
 * Remind Team Person 4:
 * To check whether a card can be played, must use cardsMatch()
 * example
 * if (cardsMatch(&a, &b)) {  }
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Card.h"
#include "CardDeck.h"

#define TOTAL_CARDS 52
#define NUM_SUITS 4
#define MAX_PLAYERS 4
#define MAX_HAND 52

 /**
  * @brief Fill a deck with a full standard set of 52 cards
  */
void fillDeck(Deck* d)
{
    for (int i = 0; i < NUM_SUITS; i++) { // creates a loop through the cards
        for (int j = 2; j <= 14; j++) {
            Card c;
            c.suit = i;
            c.rank = j;
            addCardTop(d, c);   // Add card to the deck
        }
    }
}

/**
 * @brief Reshuffle the played cards back into the hidden deck
 * except for the top played card as this card must remain on
 * the table as per the rules
 * 
 */
void reshuffleIntoDeck(Deck* hidden, Deck* played)
{
    printf("\nReshuffling cards back into deck: \n");
    if (played->size <= 1) { // Does not reshuffle if only one card is played
        return;
    }

    Card topCard;
    removeCardTop(played, &topCard); // Saves the most recently played card 
    transferAll(hidden, played); // Moves all older played cards into the hidden deck 
    shuffleDeck(hidden); // Shuffles the new hidden deck 
    addCardTop(played, topCard); // Put the last played card back on the table 
}

/**
 * @brief Start and run the card game.
 */
void startGame(int numberPlayers)
{
    if (numberPlayers < 2 || numberPlayers > MAX_PLAYERS) { // Checking if there is the correct amountn of players
        printf("Invalid number of players.\n");
        return;
    }

    srand((unsigned int)time(NULL));   // Seed random number generator
    Deck* hiddenDeck = createDeck(TOTAL_CARDS); // Cards draw from this deck
    Deck* playedDeck = createDeck(TOTAL_CARDS); // Cards that have been played

    Deck* hands[MAX_PLAYERS]; //  Creates each players hand for the game
    for (int i = 0; i < numberPlayers; i++) {
        hands[i] = createDeck(MAX_HAND);
    }

    fillDeck(hiddenDeck); // Fill the hidden deck 
    shuffleDeck(hiddenDeck); // Shuffles the deck

    int cardsPerPlayer = TOTAL_CARDS / numberPlayers; // Distributes cards evenly
    Card temp;

    for (int c = 0; c < cardsPerPlayer; c++) {
        for (int p = 0; p < numberPlayers; p++) {
            removeCardTop(hiddenDeck, &temp);  // Take from hidden deck
            addCardTop(hands[p], temp);        // Give to player's hand
        }
    }

    removeCardTop(hiddenDeck, &temp); // Flips the first card to start the game 
    addCardTop(playedDeck, temp);

    printf("Game starting with %d players\n", numberPlayers);
    printf("First card: ");
    Card_print(&temp);
    printf("\n");

    int currentPlayer = 0; 
    int winner = -1;       // -1 means no winner yet

    while (winner == -1) {

        printf("\nPlayer %d's turn.\n", currentPlayer);
        const Card* topCard = peekTop(playedDeck); // Shows the current top played card 

        printf("Top card: ");
        Card_print(topCard);
        printf("\n");
        int foundIndex = -1;

        for (int i = 0; i < hands[currentPlayer]->size; i++) {
            if (Card_matches(&hands[currentPlayer]->cards[i], topCard)) {
                foundIndex = i;  // Finds a card that matches the suit or rank
                break;
            }
        }

        if (foundIndex != -1) {  //Allows player to play a card

            Card play = hands[currentPlayer]->cards[foundIndex];

            printf("Player %d plays: ", currentPlayer);
            Card_print(&play);
            printf("\n");

            findAndRemove(hands[currentPlayer], &play); //Remove card from hand 
            addCardTop(playedDeck, play); // Adds it to the played deck 

            if (hands[currentPlayer]->size == 0) { // Check if the player has run out of cards
                winner = currentPlayer;
            }
        }
        else {
            printf("Player %d cannot play.\n", currentPlayer); // Prints if the player cannot play a card 

            if (hiddenDeck->size == 0) { // If hidden deck is empty 
                reshuffleIntoDeck(hiddenDeck, playedDeck); // Reshuffle the played cards 
            }

            removeCardTop(hiddenDeck, &temp);
            addCardTop(hands[currentPlayer], temp);

            printf("Drew card: "); // Draws a card 
            Card_print(&temp);
            printf("\n");
        }
        currentPlayer = (currentPlayer + 1) % numberPlayers; // Starts the next players turn 
    }

    printf("\n PLAYER %d WINS! \n", winner); // prints if there is a winner

    destroyDeck(&hiddenDeck);
    destroyDeck(&playedDeck);

    for (int i = 0; i < numberPlayers; i++) {
        destroyDeck(&hands[i]);
    }
}

