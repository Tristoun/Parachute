//
// Created by trist on 20/03/2024.
//

#include <allegro5/allegro.h>
#include <assert.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "player.h"
#include "background.h"
#include "helico.h"
#include "platforme.h"
#include "constante.h"



int check_collision2(Player player, Platform drop) {
    if ((player.x+al_get_bitmap_width(player.img_anim[player.nbanim]) >= drop.x
         && player.x <= drop.x + al_get_bitmap_width(drop.img)
         && player.y+ al_get_bitmap_height(player.img_anim[player.nbanim]) >= drop.y
         && player.y+ al_get_bitmap_height(player.img_anim[player.nbanim]) <= drop.y+HERBPLAT)
        && player.state == PARACHUTE) {
        return 1;
    }
    else if ((player.x+al_get_bitmap_width(player.img_anim[player.nbanim]) >= drop.x
              && player.x <= drop.x + al_get_bitmap_width(drop.img)
              && player.y+ al_get_bitmap_height(player.img_anim[player.nbanim]) >= drop.y
              && player.y+ al_get_bitmap_height(player.img_anim[player.nbanim]) <= drop.y+HERBPLAT)
             && player.state == TOMBE) {
        return 2;
    }
    else if (player.y+ al_get_bitmap_height(player.img_anim[player.nbanim])>HEIGHT
             || player.x + al_get_bitmap_width(player.img_anim[player.nbanim]) > WIDTH
             || player.x < 0) {
        return 2;
    }
    return 0;
}

void show_collision2(int x, int y, ALLEGRO_BITMAP* img) {
    al_draw_rectangle(x, y, x+ al_get_bitmap_width(img), y+ al_get_bitmap_height(img),
                      al_map_rgb(255,0,0),1);
}

void action2(Player* player, int Keysmove[NBKEY], int collision, int* score) {
    if (player->state == TOMBE || player->state == PARACHUTE) {
        //Le joueur tombe
        player_fall(player);
    }
    if (player->state == PARACHUTE && player->nbanim < NBIMG-2) {
        //Deployement du parachute
        player->nbanim += 1;
        player->fall = 2;
        player->speed = 4;
    }
    if (collision == 1 && (player->state != VIDE)) {
        //Collision entre la plateforme et le joueur
        if (player->state == PARACHUTE) {
            player->state = PLATEFORME;
            player->nbanim = 0;
            player->y += 15;
            *score += 1;
        }
        else if (player->state == TOMBE){
            player->state = VIDE;
        }
    }
    else if (collision == 2 || player->state == VIDE) {
        if (collision == 2) {
            player->state = VIDE;
        }
        player->nbanim = NBIMG-1;
        player->y = HEIGHT-30;
    }
    if (Keysmove[DROITE]==1) {
        move_player_right(player);
    }
    else if (Keysmove[GAUCHE] == 1) {
        move_player_left(player);
    }
}

void draw_all2(Background bg, Helicopter helicopter, Helicopter helicopter2,Platform drop, int score, ALLEGRO_FONT* font) { //Need to add a second score
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(bg.img, 0,0,0);
    al_draw_bitmap(helicopter.img, helicopter.x,helicopter.y,0);
    al_draw_bitmap(helicopter2.img, helicopter2.x,helicopter2.y,0);

    al_draw_bitmap(drop.img, drop.x, drop.y, 0);
    al_draw_textf(font, al_map_rgb(0,0,0), WIDTH/2, FONTSIZE, 0, "SCORE : %d", score);

}

void draw_player(Player player) {
    if (player.state != 0) {
        al_draw_bitmap(player.img_anim[player.nbanim], player.x, player.y, 0);
    }
}

void game2players(ALLEGRO_DISPLAY* display){
    int isEnd=0;
    int collision = 0;
    int score = 0;
    ALLEGRO_EVENT_QUEUE*queue;

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/FPS);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);

    Player player1;
    init_player(&player1);

    Player player2;
    init_player(&player2);

    Background bg;
    init_bg(&bg);

    Helicopter helicopter;
    init_helico(&helicopter, 0, 0);

    Helicopter helicopter2;
    init_helico(&helicopter2, WIDTH, 1);

    Platform drop;
    init_platform(&drop, WIDTH, HEIGHT);

    ALLEGRO_FONT* font = al_load_ttf_font("../Font/fontgame/Minecraft.ttf", FONTSIZE, 0);
    assert(font != NULL);

    //Ajouter tous les types d'événements souhaités
    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    int Keysmove[NBKEY] = {0};
    int Keysmove2[NBKEY] = {0};

    while(!isEnd){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);//on pioche un événement dès qu'il y en a un
        switch(event.type){//en fonction de son type (événement de souris,du clavier...),on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd=1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN://Si on arrive ici, c'est qu'on a pioché un événement du clavier de type touche  enfoncée
                switch(event.keyboard.keycode){//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_ESCAPE://on ne gère quel cas où la touche enfoncée est ECHAP
                        isEnd=1;
                        break;
                    case ALLEGRO_KEY_ENTER :
                        if (player1.state == INACTIF) {
                            player1.x = helicopter.x+ al_get_bitmap_width(helicopter.img)/2;
                            player1.y = helicopter.y;
                            player1.state = TOMBE;
                        }
                        else if (player1.state == TOMBE) {
                            player1.state = PARACHUTE;
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT :
                        if (player1.state == TOMBE || player1.state == PARACHUTE) {
                            Keysmove[DROITE] = 1;
                        }
                        break;
                    case ALLEGRO_KEY_LEFT :
                        if ((player1.state == TOMBE || player1.state == PARACHUTE)) {
                            Keysmove[GAUCHE] = 1;
                        }
                        break;
                }
                switch(event.keyboard.keycode) {//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_SPACE:
                        if (player2.state == INACTIF) {
                            player2.x = helicopter2.x + al_get_bitmap_width(helicopter2.img) / 2;
                            player2.y = helicopter2.y;
                            player2.state = TOMBE;
                        } else if (player2.state == TOMBE) {
                            player2.state = PARACHUTE;
                        }
                        break;
                    case ALLEGRO_KEY_D :
                        if (player2.state == TOMBE || player2.state == PARACHUTE) {
                            Keysmove2[DROITE] = 1;
                        }
                        break;
                    case ALLEGRO_KEY_Q :
                        if ((player2.state == TOMBE || player2.state == PARACHUTE)) {
                            Keysmove2[GAUCHE] = 1;
                        }
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP :
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_RIGHT :
                        Keysmove[DROITE] = 0;
                        break;
                    case ALLEGRO_KEY_LEFT :
                        Keysmove[GAUCHE] = 0;
                        break;
                    case ALLEGRO_KEY_D :
                        Keysmove2[DROITE] = 0;
                        break;
                    case ALLEGRO_KEY_Q :
                        Keysmove2[GAUCHE] = 0;
                        break;
                }
                break;


            case ALLEGRO_EVENT_TIMER :
                draw_all2(bg, helicopter, helicopter2, drop, score, font);
                draw_player(player1);
                draw_player(player2);
                al_flip_display();
                /*show_collision(player1.x, player1.y, player1.img_anim[player1.nbanim]);
                show_collision(drop.x, drop.y, drop.img);
                al_flip_display();*/
                collision = check_collision2(player1, drop);
                if (player1.state != VIDE && player1.state != PLATEFORME) {
                    action2(&player1, Keysmove, collision, &score);
                }
                collision = check_collision2(player2, drop);
                if (player2.state != VIDE && player2.state != PLATEFORME) {
                    action2(&player2, Keysmove2, collision, &score);
                }
                start_move(&helicopter);
                start_move(&helicopter2);
                //printf("etat : %d\n", player1.state);
                break;
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
}




