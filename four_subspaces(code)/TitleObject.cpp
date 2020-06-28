#include "Game.h"
#include "TitleObject.h"

//TitleGraph
TitleGraph::TitleGraph(const char* texturesheet)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);

    //set destRect position and size
    destRect.x = (WINDOW_W - TITLE_W) / 2;
    destRect.y = TITLE_Y;
    destRect.w = TITLE_W;
    destRect.h = TITLE_H;
}

TitleGraph::~TitleGraph(){free(this);}

void TitleGraph::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

//Button
Button::Button(const char* texturesheet, int number)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);
    buttonNum = number;

    //set 2 clips (mouse on it or not)
    for(int i = 0 ; i < 2 ; i++)
    {
        clips[i].x = 0;
        clips[i].y = i * 150;
        clips[i].w = 500;
        clips[i].h = 150;
    }
    clipNum = 0; //first clip

    //set destRect position(according to its number) and size
    destRect.x = (WINDOW_W - BUTTON_W) / 2;
    destRect.y = BUTTON_Y_FIRST + (BUTTON_H + 20) * (number - 1);
    destRect.w = BUTTON_W;
    destRect.h = BUTTON_H;

    subWin_opened = false;
}

Button::~Button(){free(this);}

int mouse_x, mouse_y;
void Button::ButtonEvent(SDL_Event event)
{
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if((mouse_x >= destRect.x) && (mouse_x <= destRect.x + destRect.w) && (mouse_y >= destRect.y) && (mouse_y <= destRect.y + destRect.h)) //mouse on the button
    {
        clipNum = 1; //second clip

        switch(event.type)
			{
            case SDL_MOUSEBUTTONUP:
                this->subWin_opened = true;
                        break;
            default:
                    break;
			}
    }
    else
    {
        clipNum = 0; //first clip
    }
}

void Button::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &clips[clipNum], &destRect);
}


//Background Animation
SpottyBG::SpottyBG(const char* circleTex, const char* blackTex)
{
    //Load images as textures
    circle = IMG_LoadTexture(Game::renderer, circleTex);
    black = IMG_LoadTexture(Game::renderer, blackTex); //well, actually we don't use this for this project, but may be used in other projects

    //let the texture can be transparent
    SDL_SetTextureBlendMode(black, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(black, 0); //add transparency to the texture "black"

    //the range to put spots is the whole window
    rectW.x = 0;
    rectW.y = 0;
    rectW.h = WINDOW_H;
    rectW.w = WINDOW_W;

    //set the needed data for all spots with random number
    for(int i = 0 ; i < dotAmount ; i++)
    {
        spots[i].x = rand() % WINDOW_W;
        spots[i].y = rand() % WINDOW_H;
        spots[i].r = rand() % 5 + 1;
        spots[i].speed = rand() % 3 + 1;
        spots[i].alpha = rand() % 255;
    }
}

SpottyBG::~SpottyBG(){free(this);}

void SpottyBG::drawSpot(Spot* spot)
{
    //use a rectangle to record the spot's data
    rect.x = spot->x;
    rect.y = spot->y;
    rect.w = spot->r;
    rect.h = spot->r;
    SDL_SetTextureAlphaMod(circle, spot->alpha); //add transparency
    SDL_RenderCopy(Game::renderer, circle, NULL, &rect);
}

void SpottyBG::moveSpot(Spot* spot)
{
    spot->y = spot->y + spot->speed;
    //drop again from the top of the screen if it touched the bottom
    if(spot->y >= WINDOW_H)
        spot->y = 0;
}

void SpottyBG::render()
{
    for(int i = 0 ; i < dotAmount ; i++)
    {
            drawSpot(&spots[i]);
            moveSpot(&spots[i]);
    }
}

//SubWindow
subWindow::subWindow(const char* texturesheet)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);

    //set destRect position and size
    destRect.x = (WINDOW_W - SUBWIN_W)/2;
    destRect.y = (WINDOW_H - SUBWIN_H)/2;
    destRect.w = SUBWIN_W;
    destRect.h = SUBWIN_H;
}
subWindow::~subWindow(){free(this);}

void subWindow::subWinEvent(SDL_Event event, Button* button)
{
    switch(event.type)
			{
            case SDL_MOUSEBUTTONUP:
                button->subWin_opened = false; //click anywhere to close this subWindow
                break;

            default:
                    break;
			}
}

void subWindow::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

//spaceButton
spaceButton::spaceButton(const char* texturesheet, int number)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);
    buttonNum = number;

    //set 2 clips (mouse on it or not)
    for(int i = 0 ; i < 2 ; i++)
    {
        clips[i].x = 0;
        clips[i].y = i * 450;
        clips[i].w = 738;
        clips[i].h = 450;
    }
    clipNum = 0; //first clip

    //set destRect position according to its number
    switch(number)
    {
    case 1:
        destRect.x = BUTTON_X1;
        destRect.y = BUTTON_Y1;
        break;
    case 2:
        destRect.x = BUTTON_X2;
        destRect.y = BUTTON_Y1;
        break;
    case 3:
        destRect.x = BUTTON_X1;
        destRect.y = BUTTON_Y2;
        break;
    case 4:
        destRect.x = BUTTON_X2;
        destRect.y = BUTTON_Y2;
        break;
    default:
        break;
    }
    //set destRect size
    destRect.w = BUTTON_W;
    destRect.h = BUTTON_H;

    subWin_opened = false; //at first, it isn't opened
}

spaceButton::~spaceButton(){free(this);}

void spaceButton::spaceButtonEvent(SDL_Event event, Game* game)
{
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if((mouse_x >= destRect.x) && (mouse_x <= destRect.x + destRect.w) && (mouse_y >= destRect.y) && (mouse_y <= destRect.y + destRect.h))//mouse on the button
    {
        clipNum = 1; //second clip

        switch(event.type)
			{
            case SDL_MOUSEBUTTONUP:
                game->load_to(buttonNum); //load to the wanted subspace
                        break;
            default:
                    break;
			}
    }
    else
    {
        clipNum = 0; // first clip

    }
}

void spaceButton::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &clips[clipNum], &destRect);
}

//Loading
LoadingGraph::LoadingGraph(const char* texturesheet)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);
    alpha = 255;
    //add transparency to the texture
    SDL_SetTextureBlendMode(objTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(objTexture, alpha);

    //set 3 clips(for animation)
    for(int i = 0 ; i < 3 ; i++)
    {
        clips[i].x = 0;
        clips[i].y = i * 600;
        clips[i].w = 800;
        clips[i].h = 600;
    }
    clipNum = 0; //first clip
}

LoadingGraph::~LoadingGraph(){free(this);}

void LoadingGraph::render()
{
    Uint32 timeStart;
    int timeTotal;

    SDL_SetTextureAlphaMod(objTexture, alpha);

    timeStart = SDL_GetTicks();

    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, objTexture, &clips[clipNum], NULL);

    SDL_RenderPresent(Game::renderer);

    timeTotal = SDL_GetTicks() - timeStart;

    //stay at the third clip for a longer time(to make wanted animation style)
    if(clipNum == 2)
        SDL_Delay(100);

    //Capping frame rate
    if(timeDelay > timeTotal)
        SDL_Delay(timeDelay - timeTotal);

    //clip change in a loop
    clipNum++;
    if(clipNum == 3)
        clipNum = 0;
}

