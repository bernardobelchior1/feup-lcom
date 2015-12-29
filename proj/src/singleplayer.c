#include "singleplayer.h"

extern enum singleplayer_controller controller;
extern enum game_state state;

void singleplayer_init() {
	singleplayer_game.score = 0;
	singleplayer_game.reset_ticks = 1;

	if ((singleplayer_game.play = player_init()) == NULL)
		return;

	projectile_list_init();
	alien_list_init();
	shield_list_init();
}

void singleplayer_tick() {
	static unsigned short ticks = 0;
	static unsigned short seconds = 0;

	if (singleplayer_game.reset_ticks == 1) {
		ticks = 0;
		seconds = 0;
		singleplayer_game.reset_ticks = 0;
		return;
	}

	if (controller == mouse)
		player_set_x_pos(singleplayer_game.play, mouse_info.x);

	if (invaders->alien_num == 0 || singleplayer_game.play->num_lives == 0) {
		singleplayer_game_over();
	}

	if (ticks % 60 == 0) {
		seconds++;
		if (seconds >= 5) {
			if (alien_fire(singleplayer_alien_to_fire()) == -1)
				singleplayer_game_over();
		}
	}

	if (((ticks - ( (seconds-1) * 60))) % invaders->movement_frequency == 0) {
		if (aliens_move() == -1)
			singleplayer_game_over();
	}

#ifdef DEBUG
	vg_draw_line(PLACEHOLDER_LEFT_BORDER, 0, PLACEHOLDER_LEFT_BORDER,
			get_v_res(), rgb(0x00FFFFFF));
	vg_draw_line(PLACEHOLDER_RIGHT_BORDER, 0, PLACEHOLDER_RIGHT_BORDER,
			get_v_res(), rgb(0x00FFFFFF));
	vg_draw_line(0, PLACEHOLDER_SHIELD_LINE, get_h_res(),
			PLACEHOLDER_SHIELD_LINE, rgb(0x00FFFFFF));
#endif

	ticks++;

	aliens_draw();
	shields_draw();
	player_draw(singleplayer_game.play);
	singleplayer_check_projectiles_state();
}

void singleplayer_check_projectiles_state() {

	if (projectiles->head == NULL)
		return;

	projectile *iterator = projectiles->head;

	do {
		if (projectile_reached_end(iterator)
				|| singleplayer_projectile_collision(iterator))
			projectile_delete(iterator); //TODO implement on projectile.c
		else {
			projectile_move(iterator);
			projectile_draw(iterator);
		}

		iterator = iterator->next;
	} while (iterator != NULL);
}

int singleplayer_projectile_collision(projectile* proj) {
	return shield_collision_handler(proj) || aliens_collision_handler(proj)
			|| player_collision_handler(singleplayer_game.play, proj);
}

int singleplayer_move(char direction) {
	return player_move(singleplayer_game.play, direction);
}

int singleplayer_fire() {
	return player_fire(singleplayer_game.play);
}

alien *singleplayer_alien_to_fire() {
	alien *iterator;
	int i, randnum;

	if (invaders->head == NULL)
		return NULL;

	do {
		iterator = invaders->head;
		randnum = rand() % (ALIENS_PER_ROW * ALIEN_ROWS); //55;


		for (i = 0; i < randnum; i++) {
			if (iterator->next == NULL)
				iterator = invaders->head;

			else
				iterator = iterator->next;

		}

	} while (!is_on_last_row(iterator));

	return iterator;
}

void singleplayer_game_over(){
	if(is_on_highscores(singleplayer_game.play->score)){
		new_score.points = singleplayer_game.play->score;
		change_state(game_over);
	}
	else
		change_state(main_menu);
}

void singleplayer_destruct() {
	aliens_destruct();
	player_destruct(singleplayer_game.play);
	shields_destruct();
}

