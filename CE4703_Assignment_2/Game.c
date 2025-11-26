/**
 * @file Game.c
 * @brief Creating the game that calls from Card.c and CardDeck.c
 *
 * @author Hugh Murnane
 * @date 25/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "Card.h"
#include "CardDeck.h"

 /**
  * @brief Fill a deck with a full standard set of 52 cards
  */
void fillDeck(Deck* d, int packs)
{
    for (int p = 0; p < packs; p++) {
        for (int i = 0; i < NUM_SUITS; i++) {// creates a loop through the cards
            for (int j = 2; j <= 14; j++) {
                Card c;
                c.suit = i;
                c.rank = j;
                addCardTop(d, c);   // Add card to the deck
            }
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
 * @brief Print a player's current hand
 */
void printPlayerHand(int playerNum, const Deck* hand)
{
    printf("Player %d's hand (%d cards): ", playerNum, hand->size);
    if (hand->size == 0) {
        printf("(empty)");
    }
    else {
        for (int i = 0; i < hand->size; i++) {
            Card_print(&hand->cards[i]);
            if (i < hand->size - 1) {
                printf(", ");
            }
        }
    }
    printf("\n");
}

/**
 * @brief Start and run the card game.
 */
void startGame(int numberPlayers, int numberPacks)
{
    if (numberPlayers < 2 || numberPlayers > MAX_PLAYERS) { // Checking if there is the correct amountn of players
        printf("Invalid number of players.\n");
        return;
    }

    if (numberPacks < 1) {
        printf("Invalid number of packs. Must be at least 1\n");
        return;
    }

    int totalCards = CARDS_PER_PACK * numberPacks;

    srand((unsigned int)time(NULL));   // Seed random number generator
    Deck* hiddenDeck = createDeck(totalCards); // Cards draw from this deck
    Deck* playedDeck = createDeck(totalCards); // Cards that have been played

    Deck* hands[MAX_PLAYERS]; // Creates each players hand for the game
    for (int i = 0; i < numberPlayers; i++) {
        hands[i] = createDeck(CARDS_PER_PLAYER*2);
    }

    fillDeck(hiddenDeck, numberPacks); // Fill the hidden deck 
    shuffleDeck(hiddenDeck); // Shuffles the deck

    Card temp;

    for (int c = 0; c < CARDS_PER_PLAYER; c++) {
        for (int p = 0; p < numberPlayers; p++) {
            removeCardTop(hiddenDeck, &temp);  // Take from hidden deck
            addCardTop(hands[p], temp);        // Give to player's hand
        }
    }

    /* Sort and display each player's initial hand*/
    printf("\nInitial hands:\n");
    for (int i = 0; i < numberPlayers; i++) {
        sortDeck(hands[i]);
        printPlayerHand(i, hands[i]);
    }
    printf("\n");

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

            printPlayerHand(currentPlayer, hands[currentPlayer]);

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

            /* Sort hand after card pickup */
            sortDeck(hands[currentPlayer]);
            printPlayerHand(currentPlayer, hands[currentPlayer]);
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

