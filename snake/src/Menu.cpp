#include "Menu.hpp"
#include "GameHost.hpp"

void handler2() {
    std::cout << "Button2 clicked." << std::endl;
}

Menu::Menu(GameHost* gamehost, int x, int y, int width, int height) {
    this->gamehost = gamehost;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    timer = gamehost->get_timer_ptr();
    display = gamehost->get_display_ptr();
    event_queue = gamehost->get_event_queue_ptr();
    key = gamehost->get_key_array();

    resize_menu_buttons();
    menu_buttons[hovered_item].hovering = true;


    //auto f = std::bind(&GameHost::change_state, gamehost, StateEnum::PLAY);
    //menu_buttons[0].handler = f;
    menu_buttons[1].handler = &handler2;
}

Menu::~Menu() {
    al_destroy_font(font);
}

//TODO: Get even spacing between menu items.
void Menu::resize_menu_buttons() {
    int num_items = menu_buttons.size();
    int lr_padding = 20; //left and right padding
    int vert_padding = 20; //vertical padding from menu border
    int item_height = height / 5; //TODO: Might not want to hardcode this
    int item_width = width - 2 * lr_padding;

    menu_buttons[0].x = x + lr_padding;
    menu_buttons[0].width = item_width;
    menu_buttons[0].y = y + vert_padding;
    menu_buttons[0].height = item_height;

    menu_buttons[num_items - 1].x = x + lr_padding;
    menu_buttons[num_items - 1].width = item_width;
    menu_buttons[num_items - 1].y = y + height - vert_padding - item_height;
    menu_buttons[num_items - 1].height = item_height;

    for (int i = 1; i < num_items - 1; i++) {
        menu_buttons[i].x = x + lr_padding;
        menu_buttons[i].width = item_width;
        menu_buttons[i].y = y + (height / num_items ) * i + vert_padding;
        menu_buttons[i].height = item_height;
    }
}

void Menu::draw() {
    al_draw_filled_rectangle(x, y, width, height, background);

    for (MenuButton button : menu_buttons)
        button.draw();
}

void Menu::tick() {
    if (key[ALLEGRO_KEY_ENTER])
        menu_buttons[hovered_item].select();
    if (key[ALLEGRO_KEY_DOWN]) {
        menu_buttons[hovered_item].hovering = false;
        hovered_item = (hovered_item + 1) % menu_buttons.size();
        menu_buttons[hovered_item].hovering = true;
    }
    if (key[ALLEGRO_KEY_UP]) {
        menu_buttons[hovered_item].hovering = false;
        hovered_item = (hovered_item - 1) % menu_buttons.size();
        menu_buttons[hovered_item].hovering = true;
    }
}