#include "GameHost.hpp"
#include "GameClass.hpp"
#include "Menu.hpp"

GameHost::GameHost() {
    init();
}

void GameHost::init() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    timer = al_create_timer(ALLEGRO_BPS_TO_SECS(8.0));
    event_queue = al_create_event_queue();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    display = al_create_display(DISP_WIDTH, DISP_HEIGHT);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    memset(key, 0, sizeof(key));

    state = State::MENU;
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
    GameClass game {this};
    Menu menu {this, 0, 0, DISP_WIDTH, DISP_HEIGHT};

    // TODO: This isn't working properly.
    while (true) {
        switch(state) {
            case State::GAME_OVER:
                // TODO
                break;
            case State::LEVEL:
                game.run();
                break;
            case State::MENU:
                menu.run();
                break;
        }
    }
}

//TODO: This is being called, but it isn't updating to the screen for some reason.
void GameHost::change_state(State next_state) {
    std::cout << "Change state to " << state_to_string(next_state) << "!" << std::endl;

    // TODO: Probably put a switch block in here to stop anything currently running.

    state = next_state;
}

void GameHost::state_ended() {
    switch (state)
    {
    case State::GAME_OVER:
        /* code */
        break;

    case State::LEVEL:
        std::cout << "Level ended." << std::endl;
        break;

    case State::MENU:
        break;
    
    default:
        break;
    }
}