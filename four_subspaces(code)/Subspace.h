#ifndef SUBSPACE_H_INCLUDED
#define SUBSPACE_H_INCLUDED

#include "Game.h"

class SubSpace
{
private:
    SDL_Surface *image = NULL;
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;

    int spaceNum;

public:
    SubSpace(const int num);
    ~SubSpace();

    void apply_surface(int x, int y,  SDL_Surface* source, SDL_Surface* destination);
    int run(Game* game);
};

#endif // SUBSPACE_H_INCLUDED
