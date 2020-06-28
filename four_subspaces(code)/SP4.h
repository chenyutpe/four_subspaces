#ifndef SP4_H_INCLUDED
#define SP4_H_INCLUDED

#include <stdio.h>
#include <string>
#include <fstream>
#include "Game.h"

class Player
{
private:
    SDL_Texture* objTexture;
    int vx, vy;

public:
    Player(const char* texturesheet);
    ~Player();

    void playerEvent( SDL_Event e );

    SDL_Rect destRect;
    void movePlayer();
    void render();

    void reset();

    static const int PLAYER_W = 20;
    static const int PLAYER_H = 20;
    static const int PLAYER_A = 2;
};

class Brick
{
private:
    SDL_Texture* objTexture;

public:
    Brick(const char* texturesheet, const int x, const int y, const int w, const int h);
    ~Brick();

    SDL_Rect destRect;

    bool collision(Player* player);
    void render();
};

class Goal
{
private:
    SDL_Texture* objTexture;
    SDL_Rect destRect;

public:
    Goal(const char* texturesheet);
    ~Goal();

    bool playerCome(Player* player);
    void render();

    static const int GOAL_X = 385;
    static const int GOAL_Y = 535;
    static const int GOAL_W = 30;
    static const int GOAL_H = 30;
};
class someGraphs
{
private:
    SDL_Texture* objTexture[4];
    int graphNum;
public:
    someGraphs(const char* texturesheet1,const char* texturesheet2,const char* texturesheet3,const char* texturesheet4);
    ~someGraphs();

    bool start;
    bool showgraph12(Game* game);
    bool showgraph34(int num, Game* game);
};

#endif // SP4_H_INCLUDED
