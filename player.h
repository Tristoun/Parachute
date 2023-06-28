//
// Created by trist on 20/06/2023.
//
#include <allegro5/allegro.h>
#define NBIMG 6
#ifndef PARACHUTE2_PLAYER_H
#define PARACHUTE2_PLAYER_H

typedef struct {
    int x, y, speed, fall;
    int state, nbanim;
    ALLEGRO_BITMAP* img_anim[NBIMG];
}Player;

void init_player (Player *player);
void player_fall (Player* player);
void move_player_right(Player* player);
void move_player_left(Player* player);

#endif //PARACHUTE2_PLAYER_H
