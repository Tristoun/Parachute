//
// Created by trist on 20/06/2023.
//
#include "player.h"
#include <stdio.h>
#define SPEED 3
#define GRAVITY 7

void init_player (Player *player) {
    player->x = 0;
    player->y = 0;
    player->speed = SPEED;
    player->fall = GRAVITY;
    player->state = 0;
    player->nbanim = 0;
    player->img_anim[0] = al_load_bitmap("../image/perso30.png");
    player->img_anim[1] = al_load_bitmap("../image/perso1_30.png");
    player->img_anim[2] = al_load_bitmap("../image/perso2_30.png");
    player->img_anim[3] = al_load_bitmap("../image/perso3_30.png");
    player->img_anim[4] = al_load_bitmap("../image/perso4_40.png");
    player->img_anim[5] = al_load_bitmap("../image/fail.png");

    for(int i =0; i<NBIMG; i++) {
        assert(player->img_anim[i] != NULL);
        if (player->img_anim[i] == NULL) {
            printf("%d", i);
        }
    }
}

void move_player_right(Player* player) {
    player->x += player->speed;
}

void move_player_left(Player* player) {
    player->x -= player->speed;
}

void player_fall (Player* player) {
    player->y += player->fall;
}

