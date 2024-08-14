#include <memory>
#include "Platform.hpp"
#include "GameData.hpp"
#include "states/State.hpp"
#include "states/StateID.hpp"

class StateFactory;

class StateManager {
private:
    std::unique_ptr<State> curr_state;
    Platform* platform;
    GameData* game_data;
    StateFactory* state_factory;

public:
    StateManager(StateID initial_state, Platform* platform, GameData* game_data, StateFactory* state_factory);

    void set_state(StateID next_state);

    State* get_curr_state();

    void update_state();
};