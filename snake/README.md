# Overview
I created a basic Snake game in C++ using the Allegro5 library. Developing the game involved coming up with some requirements and then programming a game that satisfied those requirements in C++.

# Learning Purposes
* Writing a game from scratch using the Allegro graphics library.
* Laying out requirements for a programming project.
* Discovering principles of software architecture.
* Writing a project in C++.
* Refactoring code.

# Gaming Experience
When the user runs the program, the first screen they see is the menu, which contains 4 buttons. Buttons can be hovered using the up and down keyboard keys. A hovered button can be selected with the enter button. The "PLAY" button starts the game.
<p align="center">
<img src="https://github.com/user-attachments/assets/4ba604f4-c8c8-4a92-81a1-2acda9f3474c" width="300">
</p>



The game consists of a grid, which contains a snake and a piece of food. Above the grid is the score display. The snake moves at regular intervals and its direction can be controlled with the arrow keys of the keyboard. If the snake eats food, it lengthens by one segment. If the snake collides with the grid boundaries or with its own body, it dies.
<p align="center">
<img src="https://github.com/user-attachments/assets/08c28f42-106a-47d6-98c4-a8d877271751" width="300">
</p>
<p align="center">
<img src="https://github.com/user-attachments/assets/cafb2e01-d442-4111-8353-6567c8e33f33" width="300">
</p>

# Technical Details

## Game Engine
The main engine in which the application runs is GameHost -- it hosts the game.

GameHost holds and initializes Allegro event-related components: a timer, an event queue, and the display. It also instantiates state-related objects (StateFactory, StateManager, current State).

After initializing the necessary Allegro structs and variables, and after instantiating game-related data (state stuff, Platform, and GameData), GameHost starts the Allegro timer and enters the event loop. The loop does the following:
	• If a key is pressed or lifted, this key data is passed on to the KeyboardManager in Platform.
	• If the Allegro timer ticks, tick() is called to update the current state and game data and tick the state. Then redrawing is performed (the state's draw() function is called).
	• If the user clicks the window X button, GameHost deinitializes everything, breaks out of the event loop, and the init() function ends.

    while (true) {
        al_wait_for_event(event_queue, &event);
        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                tick();
                redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                platform->keyboard_man.key_pressed(event.keyboard.keycode);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                platform->keyboard_man.key_released(event.keyboard.keycode);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                platform->exit = true;
        }
        if (platform->exit) {
            deinit();
            break;
        }
        if (redraw && al_event_queue_is_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw();
            al_flip_display();
            redraw = false;
        }
    }

## Tracking State with State Manager
All States conform to the State abstract class. A State defines a tick() and draw() function, which are called by the event loop of GameHost. A State could more appropriately be called a Scene, if you think about it. A State is identified by its StateID enum. States are created by StateFactory, and the current state is run by StateManager. During the tick() of the event loop, StateManager calls tick() on the current State. During the State tick(), the State updates its data and determines its next state (StateID). If the current State determines it needs to go to a new state, the StateManager detects this change and swaps out the current state with the new state. (The StateFactory takes care of instantiating and returning a new State (i.e. dependency injection) -- ownership of a State is held by StateManager.)

## The Play State
Actual gameplay occurs when the StateManager current state is PlayState.
