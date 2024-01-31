#include "GameHost.hpp"
#include "GameClass.hpp"
//#include "Menu.hpp"
#include "StateFactory.hpp"
#include "states/State.hpp"

GameHost::GameHost() {
    init();
}

void GameHost::init() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    state_factory = std::make_shared<StateFactory>();
    play_state = state_factory->create(StateEnum::PLAY, this);
    //menu_state = state_factory->create(StateEnum::MENU);
    curr_state = play_state;

    timer = al_create_timer(ALLEGRO_BPS_TO_SECS(8.0));
    event_queue = al_create_event_queue();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    display = al_create_display(DISP_WIDTH, DISP_HEIGHT);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    memset(key, 0, sizeof(key));

    bool redraw = false;

    al_start_timer(timer);

    while (true) {
        al_wait_for_event(event_queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                tick();
                redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
        }

        if (redraw && al_event_queue_is_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw();
            al_flip_display();
            redraw = false;
        }
    }
}

void GameHost::deinit() {
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

ALLEGRO_EVENT* GameHost::get_event_ptr() {
    return &event;
}

ALLEGRO_DISPLAY* GameHost::get_display_ptr() {
    return display;
}

ALLEGRO_TIMER* GameHost::get_timer_ptr() {
    return timer;
}

ALLEGRO_EVENT_QUEUE* GameHost::get_event_queue_ptr() {
    return event_queue;
}

unsigned char* GameHost::get_key_array() {
    return key;
}

void GameHost::run() {

}

void GameHost::tick() {
    curr_state->tick();
}

void GameHost::draw() {
    curr_state->draw();
}