CPPFLAGS=-std=c++17 -Wno-return-type -g

all:
	g++ src/Frame.cpp \
	src/StateManager.cpp \
	src/StateFactory.cpp \
	src/Snake.cpp \
	src/Constants.cpp \
	src/Direction.cpp \
	src/states/State.cpp \
	src/states/PlayState.cpp \
	src/states/MenuState.cpp \
	src/states/GameOverState.cpp \
	src/states/ControlsState.cpp \
	src/GameHost.cpp \
	src/ButtonGroup.cpp \
	src/Button.cpp \
	src/Label.cpp \
	src/KeyboardManager.cpp \
	src/Main.cpp -g -o game -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro -Wno-return-type

test:
	./game
