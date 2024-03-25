//
// Created by trist on 28/06/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "menu.h"
#include "game.h"
#include "game2.h"
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
    assert(al_install_mouse());
    al_init_font_addon();
    al_init_ttf_addon();
    //Initialiser avec assert le reste
    al_set_window_title(display,"Parachute");
    al_set_window_position(display,50,50);
    al_flip_display();
    return display;

}

void initialize_object (Object* object, int x, int y, ALLEGRO_BITMAP* img) {
    object->x = x;
    object->y = y;
    object->img = img;
    assert(object->img != NULL);
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
    al_register_event_source(queue, al_get_mouse_event_source());

    Background bg;
    init_bg(&bg);
    Object button;
    Object button2;
    initialize_object(&button, 500,250, al_load_bitmap("../image/button1.png"));
    initialize_object(&button2, 500, 320, al_load_bitmap("../image/button2.png"));
    ALLEGRO_FONT* font = al_load_ttf_font("../Font/fontgame/Minecraft.ttf", FONTSIZE*1.5, 0);
    ALLEGRO_FONT* font2 = al_load_ttf_font("../Font/fontgame/Minecraft.ttf", FONTSIZE*1.3, 0);


    al_draw_bitmap(bg.img, 0,0,0);
    al_draw_bitmap(button.img, button.x, button.y, 0);
    al_draw_bitmap(button2.img, button2.x, button2.y, 0);
    al_draw_text(font, al_map_rgb(255,255,255), 517, 262, 0, "1 PLAYER");
    al_draw_text(font2, al_map_rgb(255,255,255), 517, 334, 0, "2 PLAYERS");

    al_flip_display();

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
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN :
                if(event.mouse.x >= button.x && event.mouse.x <= button.x + al_get_bitmap_width(button.img)
                && event.mouse.y >= button.y && event.mouse.y <= button.y + al_get_bitmap_height(button.img))  {
                    game(display);
                }

                else if (event.mouse.x >= button2.x && event.mouse.x <= button2.x + al_get_bitmap_width(button.img)
                && event.mouse.y >= button2.y && event.mouse.y <= button2.y + al_get_bitmap_height(button.img))  {
                    game2players(display);
                }
        }
    }
    al_destroy_event_queue(queue);
    al_destroy_display(display);
}
