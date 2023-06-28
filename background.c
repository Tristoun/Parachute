//
// Created by trist on 21/06/2023.
//

#include "background.h"

void init_bg (Background* bg) {
    bg->img = al_load_bitmap("../image/bgsky1200.png");
    assert(bg->img != NULL);
}