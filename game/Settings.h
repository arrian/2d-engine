#pragma once

#include <iostream>


//Constants
#define CELL_SIZE 600 //in metres

//Defaults
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768
#define DEFAULT_WORLD_SCALE 30.0f
#define DEFAULT_IMAGE_SCALE 1 / 30.0f //we want the image scale to be a unit value for the initial world scale
#define DEFAULT_GRAVITY 0.0f,-60.0f//-9.81f
#define DEFAULT_CLEAR_COLOUR 0,0,0//255,255,255
#define DEFAULT_LINE_WIDTH 3.0f / DEFAULT_WORLD_SCALE
#define DEFAULT_PLAYER_START CELL_SIZE / 2,CELL_SIZE / 2,0,0

#define PLAYER_JUMP_STRENGTH 20.0f
#define PLAYER_MAX_VELOCITY 10.0f
#define PLAYER_ACCELERATION 5.0f

//Timing
#define FPS 60.0
#define SECONDS_PER_FRAME 1.0 / FPS

//Window
#define TITLE "Survive"

//Paths
#define RESOURCE_PATH "c:/Dev/Survive/Survive/"
#define DATA_PATH "c:/Dev/Survive/Survive/game.dat"
#define WORLD_PATH "c:/Dev/Survive/Survive/world_debug_10.dat"


//Libraries
#ifdef _DEBUG
#pragma comment(lib, "allegro-5.0.9-monolith-mt-debug.lib")
#pragma comment(lib, "Box2D-debug.lib")
#else
#pragma comment(lib, "allegro-5.0.9-monolith-mt.lib" )
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")//hide console
#pragma comment(lib, "Box2D.lib")
#endif
