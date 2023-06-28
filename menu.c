//
// Created by trist on 28/06/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game.h"
#include "background.h"
#include "constante.h"

ALLEGRO_DISPLAY*setting( ){
    assert(al_init());
    srand(time(NULL));
    ALLEGRO_DISPLAY*display=NULL;
    display=al_create_display(WIDTH, HEIGHT);
    assert(display!=NULL);
    assert(al_init_image_addon());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());
    al_init_font_addon();
    al_init_ttf_addon();
    //Initialiser avec assert le reste
    al_set_window_title(display,"Parachute");
    al_set_window_position(display,50,50);
    al_flip_display();
    return display;

}

void menu(){
    ALLEGRO_DISPLAY* display=setting();
    int isEnd=0;
    ALLEGRO_EVENT_QUEUE*queue;

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/FPS);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);


    //Ajouter tous les types d'événements souhaités
    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    Background bg;
    init_bg(&bg);


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
                        game(display);
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                al_draw_bitmap(bg.img, 0,0,0);
                al_flip_display();
                break;
        }
    }
    al_destroy_event_queue(queue);
    al_destroy_display(display);
}
