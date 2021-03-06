#ifndef PROJECTILE_H
#define PROJECTILE_H

#define END_AT_TOP 50
#define END_AT_BOTTOM 700
#define PROJECTILE_WIDTH 13
#define PROJECTILE_HEIGHT 22

#include "player.h"
#include "bitmap.h"

/** @defgroup projectile projectile
 * @{
 * projectile
 */

struct _player;

typedef struct _projectile{
	unsigned short x ,y, width, height;
	int velocity;
	struct _player* shooter;
	struct _projectile *next;
	struct _projectile *prev;
} projectile;

bitmap* projectile_img;

typedef struct{
	projectile *head;
} projectile_list;

projectile_list *projectiles;

/**
 * @brief Initializes the projectile linked list.
 */
void projectile_list_init();

/**
 * @brief initializes the projectile struct and adds it to the list
 * @param x x position of the projectile
 * @param y y position of the projectile
 * @param velocity velocity of the projectile
 */
int projectile_init(struct _player* p, unsigned short x, unsigned short y, int velocity);

/**
 * @brief draws the projectile
 * @param proj projectile to draw
 */
int projectile_draw(projectile *proj);

/**
 * @brief deletes a projectile
 */
int projectile_delete(projectile *proj);

/**
 * @brief updates the position of a projectile
 */
int projectile_move(projectile *proj);

/**
 * @brief checks what kind of target was hit and throws the appropriate destruction event
 */
int collision(projectile* proj, unsigned char color, unsigned short x, unsigned short y);

/**
 * @brief returns 1 if the projectile has reached the end of the screen
 */
int projectile_reached_end(projectile *proj);

/**
 * @brief deletes the projectile list
 */
void projectile_list_destruct();

#endif
