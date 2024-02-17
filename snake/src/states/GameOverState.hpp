#include "State.hpp"
#include "../Platform.hpp"

class GameOverState : public State {
public:
    GameOverState(StateEnum curr_state, Platform* platform);
    void tick();
    void draw();
};