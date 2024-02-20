#include <memory>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../Constants.hpp"
#include "../Platform.hpp"
#include "State.hpp"
#include "../Platform.hpp"
#include "../Button.hpp"
#include "../Label.hpp"

class GameOverState : public State {
private:
    //Button button_play_again;
    //Button button_go_to_menu;
    int font_size = 25;
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", font_size, 0)};
    Label label {DISP_WIDTH / 2 - 20, // For centering along x (note, 20 = 40 / 2, i.e. half the specified width)
                DISP_HEIGHT / 2 - al_get_font_ascent(font) / 2, // For centering along y
                40, // width
                al_get_font_line_height(font), // height
                "GAME OVER", 
                al_map_rgb(255, 255, 255), 
                font};
public:
    GameOverState(StateID curr_state, Platform* platform);
    void tick();
    void draw();
};