/**
 * @file main.c
 * @brief Main file for the card game implementation
 * 
 * @author Dylan O'Halloran
 * @author Xinyue Chang
 * @author Hugh Murnane
 * @author 'ADD YOUR NAME HERE'
 * @author 'ADD YOUR NAME HERE'
 * @date ADD YOUR COMPLETION DATA HERE
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
    int players;

    printf("Welcome to our simple Card Game!\n");
    printf("Enter number of players: ");
    scanf_s("%d", &players);

    startGame(players);

    return 0;
}
