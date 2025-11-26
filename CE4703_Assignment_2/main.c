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
#include "Game.h"


 /**
  * @brief
  * main.c -> Game.h -> CardDeck.h -> Card.h
  */
int main(void)

{
    int players, packs;

    printf("Welcome to the game, hope you have fun, pray for no memory leaks!\n");
    printf("Enter number of packs you would like to play with, a pack contains 52 cards per pack.\n");
    scanf_s("%d", &packs);

    printf("Enter number of players: (2-%d):", MAX_PLAYERS);
    scanf_s("%d", &players);

    startGame(players, packs);

    return 0;
}
