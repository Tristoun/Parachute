//
// Created by trist on 21/06/2023.
//

#include "platforme.h"
#include <stdlib.h>

void init_platform(Platform* drop, int wi, int hei) {

    drop->img = al_load_bitmap("../image/platform9858.png");
    assert(drop->img != NULL);
    do {
        drop->x = rand()%wi;
    }while(drop->x < al_get_bitmap_width(drop->img) || drop->x>wi- al_get_bitmap_width(drop->img));
    drop->y = hei - al_get_bitmap_height(drop->img)/1.5;
}