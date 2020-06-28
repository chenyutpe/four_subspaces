#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

const int WINDOW_W = 800;
const int WINDOW_H = 600;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

class Game
{
private:
    bool isRunning;

public:
    Game();
    ~Game();

    SDL_Window* window;
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);

    int state;

    void titleEvents();
    void titleRender();

    void load_to(const int number);

    void runSP123();

    void events();
    void update();
    void render();
    void cleanup();

    bool isLoading;
    bool running();

    bool inSS_StopRunning();

    static SDL_Renderer* renderer;

};

#endif // GAME_H_INCLUDED
