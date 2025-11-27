/**
 * @file Game.c
 * @brief Creating the game that calls from Card.c and CardDeck.c
 *
 * @author Hugh Murnane
 * @author Dylan O'Halloran
 * @date 26/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "Game.h"
#include "Card.h"
#include "CardDeck.h"

void fillDeck(Deck* d, long long packs)
{
    /* Iterate through each pack */
    for (long long p = 0; p < packs; p++) {
        /* Iterate through all 4 suits */
        for (int i = 0; i < NUM_SUITS; i++) {
            /* Iterate through all 13 ranks (2-14: Two through Ace) */
            for (int j = 2; j <= 14; j++) {
                /* Create a card with current suit and rank */
                Card c;
                c.suit = i;
                c.rank = j;
                /* Add card to top of deck */
                addCardTop(d, c);
            }
        }
    }
}

void reshuffleIntoDeck(Deck* hidden, Deck* played)
{
    printf("\nReshuffling cards back into deck: \n");

    /* If only one or zero cards in played deck, no reshuffle needed */
    if (played->size <= 1) {
        return;
    }

    /* Save the topmost played card (must stay on table per rules) */
    Card topCard;
    removeCardTop(played, &topCard);

    /* Transfer all remaining played cards back to hidden deck */
    transferAll(hidden, played);

    /* Shuffle the replenished hidden deck */
    shuffleDeck(hidden);

    /* Return the saved top card back to played deck */
    addCardTop(played, topCard);
}

void printPlayerHand(int playerNum, const Deck* hand)
{
    printf("Player %d's hand (%zu cards): ", playerNum, hand->size);  /* %zu for size_t */
    if (hand->size == 0) {
        printf("(empty)");
    }
    else {
        for (size_t i = 0; i < hand->size; i++) {  /* size_t loop counter */
            Card_print(&hand->cards[i]);
            if (i < hand->size - 1) {
                printf(", ");
            }
        }
    }
    printf("\n");
}

void startGame(int numberPlayers, long long numberPacks)
{
    /* Validate input parameters */
    if (numberPlayers < 2 || numberPlayers > MAX_PLAYERS) {
        printf("Invalid number of players.\n");
        return;
    }

    if (numberPacks < 1) {
        printf("Invalid number of packs. Must be at least 1\n");
        return;
    }

    /* Overflow check before multiplcation happens */
    if ((size_t)numberPacks > SIZE_MAX / CARDS_PER_PACK) {
        printf("Error: Number of packs too large - would cause overflow.\n");
        printf("Requested: %lld packs\n", numberPacks);
        printf("Maximum safe packs: %zu\n", SIZE_MAX / CARDS_PER_PACK);
        return;
    }

    /* Calculate total cards using size_t to avoid overflow */
    size_t totalCards = (size_t)CARDS_PER_PACK * (size_t)numberPacks;

    /* Initialize random number generator for shuffling */
    srand((unsigned int)time(NULL));

    /* Create decks for game */
    Deck* hiddenDeck = createDeck(totalCards);  /* Draw pile */
    Deck* playedDeck = createDeck(totalCards);  /* Discard pile */

    /* Check if deck creation was successful */
    if (hiddenDeck == NULL || playedDeck == NULL) {
        printf("Error: Unable to allocate memory for game decks.\n");
        printf("Requested %zu cards. Try reducing the number of packs.\n", totalCards);
        if (hiddenDeck) destroyDeck(&hiddenDeck);
        if (playedDeck) destroyDeck(&playedDeck);
        return;
    }

    /* Create individual hands for each player */
    Deck* hands[MAX_PLAYERS];
    for (int i = 0; i < numberPlayers; i++) {
        hands[i] = createDeck(CARDS_PER_PLAYER * 2);  /* Extra capacity for drawn cards */
        if (hands[i] == NULL) {
            printf("Error: Unable to allocate memory for player hands.\n");
            /* Clean up already allocated decks */
            destroyDeck(&hiddenDeck);
            destroyDeck(&playedDeck);
            for (int j = 0; j < i; j++) {
                destroyDeck(&hands[j]);
            }
            return;
        }
    }

    /* Initialize and shuffle the hidden deck */
    fillDeck(hiddenDeck, numberPacks);
    shuffleDeck(hiddenDeck);

    Card temp;

    /* Deal initial cards - round-robin style */
    /* Give each player one card at a time until they have 8 cards */
    for (int c = 0; c < CARDS_PER_PLAYER; c++) {
        for (int p = 0; p < numberPlayers; p++) {
            removeCardTop(hiddenDeck, &temp);
            addCardTop(hands[p], temp);
        }
    }

    /* Sort and display initial hands */
    printf("\nInitial hands:\n");
    for (int i = 0; i < numberPlayers; i++) {
        sortDeck(hands[i]);
        printPlayerHand(i, hands[i]);
    }
    printf("\n");

    /* Flip first card from hidden deck to start the game */
    removeCardTop(hiddenDeck, &temp);
    addCardTop(playedDeck, temp);

    printf("Game starting with %d players\n", numberPlayers);
    printf("First card: ");
    Card_print(&temp);
    printf("\n");

    /* Initialize game state variables */
    unsigned int currentPlayer = 0;
    int winner = -1;  /* -1 indicates no winner yet */

    /* Main game loop - continue until someone wins */
    while (winner == -1) {

        printf("\nPlayer %d's turn.\n", currentPlayer);

        /* Get the current top card that must be matched */
        const Card* topCard = peekTop(playedDeck);

        printf("Top card: ");
        Card_print(topCard);
        printf("\n");

        /* Search player's hand for a matching card */
        int foundIndex = -1;
        for (size_t i = 0; i < hands[currentPlayer]->size; i++) {  /* size_t loop */
            if (i >= hands[currentPlayer]->capacity) {
                printf("ERROR: Hand corruption detected!\n");
                break;
            }
            /* Check if card matches by rank or suit */
            if (Card_matches(&hands[currentPlayer]->cards[i], topCard)) {
                foundIndex = (int)i;  /* Found a playable card */
                break;
            }
        }

        /* Player has a matching card - play it */
        if (foundIndex != -1) {
            Card play = hands[currentPlayer]->cards[foundIndex];

            printf("Player %d plays: ", currentPlayer);
            Card_print(&play);
            printf("\n");

            /* Remove card from hand and add to played pile */
            findAndRemove(hands[currentPlayer], &play);
            addCardTop(playedDeck, play);

            printPlayerHand(currentPlayer, hands[currentPlayer]);

            /* Check for win condition - player has no cards left */
            if (hands[currentPlayer]->size == 0) {
                winner = currentPlayer;
            }
        }
        /* Player cannot play - must draw a card */
        else {
            printf("Player %d cannot play.\n", currentPlayer);

            /* Check if hidden deck is empty - reshuffle if needed */
            if (hiddenDeck->size == 0) {
                reshuffleIntoDeck(hiddenDeck, playedDeck);
            }

            /* Draw a card from hidden deck */
            removeCardTop(hiddenDeck, &temp);
            addCardTop(hands[currentPlayer], temp);

            printf("Drew card: ");
            Card_print(&temp);
            printf("\n");

            /* Re-sort hand after drawing card */
            sortDeck(hands[currentPlayer]);
            printPlayerHand(currentPlayer, hands[currentPlayer]);
        }

        /* Move to next player (wraps around using modulo) */
        currentPlayer = (currentPlayer + 1) % numberPlayers;
    }

    /* Game over - announce winner */
    printf("\n PLAYER %d WINS! \n", winner);

    /* Clean up all dynamically allocated memory */
    destroyDeck(&hiddenDeck);
    destroyDeck(&playedDeck);
    for (int i = 0; i < numberPlayers; i++) {
        destroyDeck(&hands[i]);
    }
}