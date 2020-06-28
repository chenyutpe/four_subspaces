#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.h"
#include "TitleObject.h"
using namespace std;

Game* game = nullptr;

int main(int argc, char* argv[])
{
    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("Four_Subspaces", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, false);

    while(game->running())
    {
        frameStart = SDL_GetTicks();

        switch(game->state)
        {
            case 0://Title screen
                {
                    game->isLoading = false;
                    game->titleEvents();
                    game->titleRender();
                    break;
                }
            case 1://Subspace 1
            case 2://Subspace 2
            case 3://Subspace 3
                {
                    game->isLoading = false;
                    game->runSP123();
                    break;
                }
            case 4://Subspace 4
                {
                    game->isLoading = false;
                    game->events();
                    game->update();
                    game->render();
                }
            default:
                    break;
        }

        frameTime = SDL_GetTicks() - frameStart;

        //Capping frame rate
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

    }
    game->cleanup();
    return 0;
}
