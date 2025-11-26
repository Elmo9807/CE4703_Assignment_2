/**
 * @file main.c
 * @brief Main file for the card game implementation
 * 
 * @author Dylan O'Halloran
 * @author Xinyue Chang
 * @author Hugh Murnane
 * @author Logan Fan
 * @author Finnian Berry
 * @date 26/11/2025
 *
 * Group_1_Assignment_2
 *
 *
 */

#include <stdio.h>
#include <ctype.h>
#include "Game.h"


 /**
  * @brief
  * 
  * Prompts user for number of packs and players with validation
  * Includes play again functionality
  * 
  * @return 0 on success
  */
int main(void)

{
    int players, packs;
    char playAgain;

    printf("Welcome to the game, hope you have fun, pray for no memory leaks!\n");

    /* Input validation loop for packs */
    do {
        printf("Enter number of packs you would like to play with, a pack contains 52 cards per pack.\n");
        if (scanf_s("%d", &packs) != 1) {

            while (getchar() != '\n')
                printf("Error: Please enter a valid number.\n\n");
            packs = 0;
        }
        else if (packs < 1) {
            printf("Error: Must enter at least 1 pack\n\n");
        }
    } while (packs < 1);

    /* Input validation loop for players */
    do {
        printf("Enter number of players (2-%d): ", MAX_PLAYERS);
        if (scanf_s("%d", &players) != 1) {
            /* Clear invalid input */
            while (getchar() != '\n');
            printf("Error: Please enter a valid number.\n\n");
            players = 0;
        }
        else if (players < 2 || players > MAX_PLAYERS) {
            printf("Error: Must enter between 2 and %d players.\n\n", MAX_PLAYERS);
        }
    } while (players < 2 || players > MAX_PLAYERS);

    /* Start game logic with validated input */
    printf("\n");
    startGame(players, packs);

    do {
    /* Play again prompting */
    printf("\n");
    printf("Would you like to play again? (Y/N)");

    /* Clear leftover input */
    while (getchar() != '\n');

    /* Retrieve play again response */
    playAgain = getchar();
    playAgain = toupper(playAgain);

    /* Clear remaining input */
    while (getchar() != '\n');

    } while (playAgain == 'Y');

    printf("\nThank you for playing! Goodbye!\n");

    return 0;
}