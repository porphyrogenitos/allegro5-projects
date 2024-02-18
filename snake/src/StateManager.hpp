#include <memory>
#include "Platform.hpp"
#include "states/State.hpp"

class StateFactory;

//TODO: Did you add to Makefile?

class StateManager {
private:
    std::unique_ptr<State> curr_state;
    Platform* platform;
    StateFactory* state_factory;

public:
    StateManager(StateID initial_state, Platform* platform, StateFactory* state_factory);

    void set_state(StateID next_state);

    State* get_curr_state();

    void update_state();
};