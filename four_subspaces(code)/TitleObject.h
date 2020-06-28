#ifndef TITLEOBJECT_H_INCLUDED
#define TITLEOBJECT_H_INCLUDED

#include "Game.h"

class TitleGraph
{
private:
    SDL_Texture* objTexture;
    SDL_Rect destRect;

public:
    TitleGraph(const char* texturesheet);
    ~TitleGraph();

    void render();

    static const int TITLE_W = 480;
    static const int TITLE_H = 240;
    static const int TITLE_Y = 60;
};

class Button
{
private:
    int buttonNum, clipNum;
    SDL_Texture* objTexture;
    SDL_Rect clips[2];
    SDL_Rect destRect;

public:
    Button(const char* texturesheet, int number);
    ~Button();

    void ButtonEvent(SDL_Event event);
    void render();

    bool subWin_opened;

    static const int BUTTON_W = 200;
    static const int BUTTON_H = 60;
    static const int BUTTON_Y_FIRST = 330;
};

//preapare for the SpottyBG
struct Spot
{
    int x;
    int y;
    int r;
    int speed;
    int alpha;
};

const int dotAmount = 500;

class SpottyBG
{
private:
    SDL_Texture* circle;
    SDL_Texture* black;

    Spot spots[dotAmount];
    SDL_Rect rect, rectW;

public:
    SpottyBG(const char* circleTex, const char* blackTex);
    ~SpottyBG();

    void drawSpot(Spot* spot);
    void moveSpot(Spot* spot);

    void render();
};

class subWindow
{
private:
    SDL_Texture* objTexture;
    SDL_Rect destRect;

public:
    subWindow(const char* texturesheet);
    ~subWindow();

    void subWinEvent(SDL_Event event, Button* button);
    void render();

    static const int SUBWIN_W = 700;
    static const int SUBWIN_H = 500;
};

class spaceButton
{
private:
    int buttonNum, clipNum;
    SDL_Texture* objTexture;
    SDL_Rect clips[2];
    SDL_Rect destRect;

public:
    spaceButton(const char* texturesheet, int number);
    ~spaceButton();

    void spaceButtonEvent(SDL_Event event, Game* game);
    void render();

    bool subWin_opened;

    static const int BUTTON_W = 246;
    static const int BUTTON_H = 150;
    static const int BUTTON_X1 = 127;
    static const int BUTTON_X2 = 427;
    static const int BUTTON_Y1 = 155;
    static const int BUTTON_Y2 = 352;
};

class LoadingGraph
{
private:
    int clipNum;
    SDL_Texture* objTexture;
    SDL_Rect clips[3];
    SDL_Rect destRect;

public:
    LoadingGraph(const char* texturesheet);
    ~LoadingGraph();

    int alpha;

    void render();

    static const int timeDelay = 100;
};

#endif // TITLEOBJECT_H_INCLUDED
