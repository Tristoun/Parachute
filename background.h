//
// Created by trist on 21/06/2023.
//

#ifndef PARACHUTE2_BACKGROUND_H
#define PARACHUTE2_BACKGROUND_H
#include <allegro5/allegro.h>

typedef struct {
    ALLEGRO_BITMAP* img;
}Background;

void init_bg (Background* bg);

#endif //PARACHUTE2_BACKGROUND_H
