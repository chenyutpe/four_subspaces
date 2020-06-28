#include "SP4.h"

Player::Player(const char* texturesheet)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);

    //set destRect position(first at (0, 0)) and size
    destRect.x = 0;
    destRect.y = 0;
	destRect.w = PLAYER_W;
	destRect.h = PLAYER_H;

    //set speed as 0
    vx = 0;
    vy = 0;
}

Player::~Player(){free(this);}

void Player::reset()
{
    destRect.x = 0;
    destRect.y = 0;

    vx = 0;
    vy = 0;
}
void Player::playerEvent( SDL_Event e )
{
    //if a key is pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //adjust the speed
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                vy -= PLAYER_A;
                break;
            case SDLK_DOWN:
                vy += PLAYER_A;
                break;
            case SDLK_LEFT:
                vx -= PLAYER_A;
                break;
            case SDLK_RIGHT:
                vx += PLAYER_A;
                break;
        }
    }
    //if a key is released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //adjust the speed
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            case SDLK_DOWN:
                vy = 0;
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                vx = 0;
                break;
        }
    }
}

void Player::movePlayer()
{
    destRect.x += vx;

    if( ( destRect.x < 0 ) || ( destRect.x + PLAYER_W > WINDOW_W ))
    {
        destRect.x -= vx;
    }

    destRect.y += vy;

    if( ( destRect.y < 0 ) || ( destRect.y + PLAYER_H > WINDOW_H ))
    {
        destRect.y -= vy;
    }
}

void Player::render( )
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

Brick::Brick(const char* texturesheet, const int x, const int y, const int w, const int h)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);

    //set destRect position and size
    destRect.x = x;
    destRect.y = y;
	destRect.w = w;
	destRect.h = h;
}

Brick::~Brick(){free(this);}

bool Brick::collision(Player* player)
{
    if(SDL_HasIntersection(&player->destRect, &destRect) == SDL_TRUE) //collision
    {
        return true;
    }
    return false;
}


void Brick::render( )
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

Goal::Goal(const char* texturesheet)
{
    //Load image as texture
    objTexture = IMG_LoadTexture(Game::renderer, texturesheet);

    //set destRect position and size
    destRect.x = GOAL_X;
    destRect.y = GOAL_Y;
	destRect.w = GOAL_W;
	destRect.h = GOAL_H;
}

Goal::~Goal(){free(this);}

bool Goal::playerCome(Player* player)
{
    if((player->destRect.x >= destRect.x) && (player->destRect.x <= destRect.x + destRect.w) && (player->destRect.y >= destRect.y) && (player->destRect.y <= destRect.y + destRect.h))
    {
        return true;
    }
    return false;
}

void Goal::render( )
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

someGraphs::someGraphs(const char* texturesheet1,const char* texturesheet2,const char* texturesheet3,const char* texturesheet4)
{
    //Load images as textures
    objTexture[0] = IMG_LoadTexture(Game::renderer, texturesheet1);
    objTexture[1] = IMG_LoadTexture(Game::renderer, texturesheet2);
    objTexture[2] = IMG_LoadTexture(Game::renderer, texturesheet3);
    objTexture[3] = IMG_LoadTexture(Game::renderer, texturesheet4);

    start = true; //we need instruction at first
}

someGraphs::~someGraphs(){free(this);}

bool someGraphs::showgraph12(Game* game)
{
    //put to render target
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, objTexture[0], NULL, NULL);
    SDL_RenderPresent(Game::renderer);

    //event control
    SDL_Event e;
    bool quit = false;
    while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RETURN) //Entee key
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                quit = true;
                                start = true;
                                game->load_to(0);
                                return 0;
                            }
                        }
                }
                if(e.type == SDL_QUIT)
                    {
                        game->inSS_StopRunning();
                        return 0;
                    }
            }

    quit = false;

    //put to render target
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, objTexture[1], NULL, NULL);
    SDL_RenderPresent(Game::renderer);

    //event control
    while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RETURN)//Entee key
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                quit = true;
                                start = true;
                                game->load_to(0);
                                return 0;
                            }
                        }
                }
                if(e.type == SDL_QUIT)
                    {
                        game->inSS_StopRunning();
                        return 0;
                    }
            }
    start = false;
    return 0;
}
bool someGraphs::showgraph34(int num, Game* game)
{
    //put to render target
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, objTexture[num], NULL, NULL);
    SDL_RenderPresent(Game::renderer);

    //event control
    SDL_Event e;
    bool quit = false;
    while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RETURN)//Entee key
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                quit = true;
                                start = true;
                                game->load_to(0);
                                return 0;
                            }
                        }
                }
                if(e.type == SDL_QUIT)
                    {
                        game->inSS_StopRunning();
                        return 0;
                    }
            }
    return 0;
}
