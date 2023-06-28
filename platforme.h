//
// Created by trist on 21/06/2023.
//
#include <allegro5/allegro.h>

#ifndef PARACHUTE2_PLATFORME_H
#define PARACHUTE2_PLATFORME_H

typedef struct {
    int x,y;
    ALLEGRO_BITMAP* img;
}Platform;


void init_platform(Platform* drop, int wi, int hei);
#endif //PARACHUTE2_PLATFORME_H
