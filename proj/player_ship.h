#ifndef __PLAYER_SHIP_H
#define __PLAYER_SHIP_H

#include "keyboard.h"
#include "timer.h"

typedef struct{
	int num_lifes = 3;
	int ypos, cannonxpos;
	int velocity;
	char *mem_pos;
} player;

int player_init(); //allocates the struct
int move_player(); //Keyboard interrupt handler for left and right arrow keys
int player_fire(); //Keyboard handler for Spacebar (in singleplayer)
int draw_player(); //Places the ship on the screen
int player_hit(); //Animation for the player destruction


#endif /*__PLAYER_SHIP_H*/