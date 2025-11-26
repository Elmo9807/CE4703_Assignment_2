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
    char playAgain = 'N';

    printf("Welcome to the game, hope you have fun, pray for no memory leaks!\n");

    /* Pack input with validation */
    do {
        printf("\nEnter number of packs, minimum of 1, each pack contains 52 cards:\n ");
        if (scanf_s("%d", &packs) != 1) {
            /* Clear */
            while (getchar() != '\n');
            printf("Error: Invalid input.\n");
            packs = 0;
        }
    } while (packs < 1);

    /* Player input with validation */
    do {
        printf("Enter number of players (2-%d): ", MAX_PLAYERS);
        if (scanf_s("%d", &players) != 1) {
            /* Clear invalid input */
            while (getchar() != '\n');
            printf("Error: Invalid input.\n");
            players = 0;
        }
    } while (players < 2 || players > MAX_PLAYERS);

    /* Start game */
    printf("\nStarting game...\n");
    startGame(players, packs);

    printf("\nThank you for playing, hope you had fun.\n");
    return 0;
}