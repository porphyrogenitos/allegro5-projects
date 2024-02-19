CPPFLAGS=-std=c++17 -Wno-return-type -g

all:
	g++ src/GameClass.cpp \
	src/StateManager.cpp \
	src/StateFactory.cpp \
	src/Snake.cpp \
	src/Constants.cpp \
	src/Direction.cpp \
	src/states/State.cpp \
	src/states/PlayState.cpp \
	src/states/MenuState.cpp \
	src/states/GameOverState.cpp \
	src/GameHost.cpp \
	src/Menu.cpp \
	src/MenuButton.cpp \
	src/Label.cpp \
	src/KeyboardManager.cpp \
	src/Main.cpp -g -o game -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro -Wno-return-type

test:
	./game

game: Main.c
	g++ $(CPPFLAGS) -o game Main.c

Main.o: GameHost.o
	g++ $(CPPFLAGS) -c GameHost.o -o Main.o

GameHost.o:
	g++ $(CPPFLAGS) -c 