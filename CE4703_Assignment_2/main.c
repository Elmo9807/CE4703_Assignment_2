/**
 * @file main.c
 * @brief Main file for the card game implementation
 * @author Dylan OHalloran
 * @author Xinyue Chang
 * @author 'ADD YOUR NAME HERE'
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
	Game_init(1);
	Game_play();
	Game_cleanup();

	return 0;
}

// repo push test comment, you can remove this whenever you want