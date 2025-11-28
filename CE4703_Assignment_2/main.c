/**
 * @file main.c
 * @brief Main file for the card game implementation
 *
 * @author Dylan O'Halloran
 * @date 27/11/2025
 *
 * Group_1_Assignment_2
 *
 */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include "Game.h"

 /**
  * @brief Main entry point for the card game
  *
  * Prompts user for number of packs and players with validation.
  * Supports large numbers of packs limited only by available system memory.
  *
  * @param argc Argument count
  * @param argv Argument vector
  * @return 0 on success
  */
int main(int argc, char* argv[])
{
    int players;
    long long packs;

    printf("Welcome to the game, hope you have fun, pray for no memory leaks!\n");

    /* Pack input with validation */
    do {
        printf("\nEnter number of packs, minimum of 1, each pack contains 52 cards:\n ");

        /* Scan in input */
        if (scanf("%lld", &packs) != 1) {
            /* Clear invalid input from buffer */
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Error: Invalid input. Please enter a positive integer.\n");
            packs = 0;
        }
        else if (packs < 1) {
            printf("Error: Number of packs must be at least 1.\n");
        }
    } while (packs < 1);

    printf("Number of packs selected: %lld\n", packs);

    /* Player input with validation */
    do {
        printf("Enter number of players (2-%d): ", MAX_PLAYERS);
        if (scanf("%d", &players) != 1) {
            /* Clear invalid input from buffer */
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Error: Invalid input. Please enter a number.\n");
            players = 0;
        }
        else if (players < 2 || players > MAX_PLAYERS) {
            printf("Error: Number of players must be between 2 and %d.\n", MAX_PLAYERS);
        }
    } while (players < 2 || players > MAX_PLAYERS);

    printf("Number of players selected: %d\n", players);

    /* Start game */
    printf("\nStarting game...\n");
    startGame(players, packs);

    printf("\nThank you for playing, hope you had fun.\n");
    return 0;
}