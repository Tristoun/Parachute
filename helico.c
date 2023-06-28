//
// Created by trist on 21/06/2023.
//
#include <allegro5/allegro.h>
#include "helico.h"
#include "constante.h"

void init_helico(Helicopter* helicopter) {
    helicopter->x = 0;
    helicopter->y = FONTSIZE;
    helicopter->direction = 0;
    helicopter->speed = 5;
    helicopter->img = al_load_bitmap("../image/helico96.png");
    assert(helicopter->img != NULL);
}

void start_move(Helicopter *helicopter) {
    switch (helicopter->direction) {
        case 0 :
            helicopter->x += helicopter->speed;
            break;
        case 1 :
            helicopter->x -= helicopter->speed;
            break;
    }
}