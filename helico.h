//
// Created by trist on 21/06/2023.
//
#include <allegro5/allegro.h>
#ifndef PARACHUTE2_HELICO_H
#define PARACHUTE2_HELICO_H

typedef struct {
    int x,y,direction, speed;
    ALLEGRO_BITMAP* img;
}Helicopter;

void init_helico(Helicopter* helicopter, int x, int direction);
void start_move(Helicopter *helicopter);

#endif //PARACHUTE2_HELICO_H
