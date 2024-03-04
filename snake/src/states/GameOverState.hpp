#include <memory>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../Constants.hpp"
#include "../Platform.hpp"
#include "State.hpp"
#include "../GameData.hpp"
#include "../Button.hpp"
#include "../Label.hpp"

/**
 * @brief Displays the Game Over screen, which includes player's final score.
 * 
 */

class GameOverState : public State {
private:
    //Button button_play_again;
    //Button button_go_to_menu;
    int font_size = 25;
    //TODO: Get font from GameData instead.
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", font_size, 0)};
    Label label {};
    
    Label score_label {DISP_WIDTH / 2 - 50, // For centering along x
                DISP_HEIGHT / 2 + 40 - al_get_font_ascent(font) / 2, // For centering along y
                100, // width
                al_get_font_line_height(font), // height
                "YOUR SCORE: " + std::to_string(game_data->current_score), 
                al_map_rgb(255, 255, 255), 
                font,
                ALLEGRO_ALIGN_CENTRE};
public:
    /**
     * @brief Construct a new GameOverState object
     */
    GameOverState(StateID curr_state, Platform* platform, GameData* game_data);

    /**
     * @brief Checks if the player has pressed Esc to exit.
     * 
     */
    void tick();

    /**
     * @brief Draws the Game Over text as well as the player's score.
     * 
     */
    void draw();
};