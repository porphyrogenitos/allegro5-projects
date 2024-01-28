#include "State.hpp"

//TODO: Did you add to Makefile?

class StateManager {
private:
    State state;

public:
    StateManager(State initial_state);

    void next_state(State next_state);

    void update_state();

    void draw_state();
};