#pragma once

#include <iostream>
#include <string>

//Constants
const double CELL_SIZE = 600;//in metres
const std::string VERSION = "alpha 0.1.1";
const std::string DEBUG_FONT = "myriad-pro.ttf";

//Defaults
const int DEFAULT_WIDTH = 1024;
const int DEFAULT_HEIGHT = 768;
const double DEFAULT_WORLD_SCALE = 30.0f;
const double DEFAULT_IMAGE_SCALE = 1 / 30.0f; //we want the image scale to be a unit value for the initial world scale
const double DEFAULT_LINE_WIDTH = 3.0f / DEFAULT_WORLD_SCALE;
#define DEFAULT_GRAVITY 0.0f,-60.0f//-9.81f
#define DEFAULT_CLEAR_COLOUR 0,0,0//255,255,255
#define DEFAULT_PLAYER_START CELL_SIZE / 2,CELL_SIZE / 2,0,0

const double PLAYER_JUMP_STRENGTH = 20.0f;
const double PLAYER_MAX_VELOCITY = 10.0f;
const double PLAYER_ACCELERATION = 5.0f;

//Timing
const double FPS = 60.0;
const double SECONDS_PER_FRAME = 1.0 / FPS;

//Window
const std::string TITLE = "Survive";

//Paths
const int MAX_PATH = 1024;
const std::string RESOURCE_PATH = "/../../res/";
const std::string IMAGE_FOLDER = "images/";
const std::string DATA_FOLDER = "data/";
const std::string WORLD_FOLDER = "world/";
const std::string FONT_FOLDER = "fonts/";
const std::string DATA_FILE = "game.dat";
const std::string WORLD_FILE = "world_debug_10.dat";


//Libraries
#ifdef _DEBUG
#pragma comment(lib, "allegro-5.0.9-monolith-mt-debug.lib")
#pragma comment(lib, "Box2D-debug.lib")
#else
#pragma comment(lib, "allegro-5.0.9-monolith-mt.lib" )
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")//hide console
#pragma comment(lib, "Box2D.lib")
#endif
