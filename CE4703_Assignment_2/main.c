/**
 * @file main.c
 * @brief Main file for the card game implementation
 * 
 * @author Dylan O'Halloran
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
  * 
  * @param argc Argument count
  * @param argv Argument vector
  * @return 0 on success
  */
int main(int argc, char *argv[])
{
    int players, packs;

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

    printf("Number of packs selected: %d\n", packs);

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

    printf("Number of players selected: %d\n", players);

    /* Start game */
    printf("\nStarting game...\n");
    startGame(players, packs);

    printf("\nThank you for playing, hope you had fun.\n");

    return 0;
}