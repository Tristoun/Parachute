//
// Created by trist on 28/06/2023.
//
#include <allegro5/allegro.h>

#ifndef PARACHUTE2_MENU_H
#define PARACHUTE2_MENU_H

typedef struct {
    int x, y;
    int width, height;
    ALLEGRO_BITMAP* img;
}Object;

void menu();

#endif //PARACHUTE2_MENU_H
