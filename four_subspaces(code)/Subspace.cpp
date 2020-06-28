#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Subspace.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define stopNum 400

SubSpace::SubSpace(const int num)
{
    spaceNum = num;
}
SubSpace::~SubSpace(){}

void SubSpace::apply_surface(int x, int y,  SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source,NULL,destination, &offset);
}


int SubSpace::run(Game* game)
{
    switch(spaceNum)
    {
    case 1:
        {
            // stone = 1, paper = 0, scissor = 2
            int man_x_position = 0;
            int man_y_position = 0;
            int p1 = 0;
            int p2 = 0;

            // this is used to calculate the amount of blood of each characters in challenge mode
            int blood_player = 3;
            int blood_computer = 5;

            bool quit = false;

            //initialize the surfaces(to load images)
            SDL_Surface* rule = NULL;
            SDL_Surface* decision = NULL;
            SDL_Surface* decision2 = NULL;
            SDL_Surface* title = NULL;
            SDL_Surface* choose = NULL;
            SDL_Surface* stage = NULL;
            SDL_Surface* heart = NULL;
            SDL_Surface* gameover = NULL;

            // initialize the event variable
            SDL_Event e;

            // using surfaces to load images
            SDL_Surface* tryagain;
            tryagain = IMG_Load("assets/space1&2/tryAgain.png");
            SDL_Surface* win;
            win = IMG_Load("assets/space1&2/win.png");
            SDL_Surface* lose;
            lose = IMG_Load("assets/space1&2/lose.png");
            SDL_Surface* mode;
            mode = IMG_Load("assets/space1&2/mode.png");
            stage = IMG_Load("assets/space1&2/stage.png");
            heart = IMG_Load("assets/space1&2/heart.png");
            gameover = IMG_Load("assets/space1&2/gameover.png");

            // selecy mode
            int modeSelect = 0;
            screen = SDL_GetWindowSurface(game->window);

            title = IMG_Load("assets/space1&2/title.png");
            apply_surface(man_x_position,man_y_position,title,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);

            // if the event is pressing the key of right, use another image to update the window
            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RIGHT)
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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

            rule = IMG_Load("assets/space1&2/rule.png");
            apply_surface(man_x_position,man_y_position,rule,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);

            // using the same way to change image
            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RIGHT)
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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
        restart:
            blood_player = 3;
            blood_computer = 5;
            quit = false;
            apply_surface(man_x_position,man_y_position,mode,screen);
            SDL_UpdateWindowSurface(game->window);

            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_UP)
                            {
                                modeSelect = 1;
                                quit = true;
                            }
                            if(e.key.keysym.sym == SDLK_DOWN)
                            {
                                modeSelect = 2;
                                quit = true;
                            }
                            if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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

        // practice mode
        // using randow number to make it possible for computer to seclect randomly
            if(modeSelect == 1)
            {
                image = IMG_Load("assets/space1&2/pss.png"); // loads image
                apply_surface(man_x_position,man_y_position,image,screen);
                SDL_UpdateWindowSurface(game->window);
                SDL_Delay(100);

                apply_surface(man_x_position,man_y_position,image,screen);

                while(quit == false)
                {
                    srand( time(NULL));
                    int y = rand();
                    int x = rand() % 3;
                    x = (x+y) % 3;

                    SDL_UpdateWindowSurface(game->window);
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_QUIT)
                        {
                            game->inSS_StopRunning();
                            return 0;
                        }
                        if(e.type == SDL_KEYDOWN)
                        {
                            //Select surfaces based on key press
                                    switch( e.key.keysym.sym )
                                    {
                                        case SDLK_UP:
                                        choose = IMG_Load("assets/space1&2/pss_s2.png");
                                        apply_surface(0,0,choose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(500);
                                        decision = IMG_Load("assets/space1&2/scissor.png");
                                        apply_surface(0,300,decision,screen);
                                        p1 = 1;
                                        if(x == 0)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/paper_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        apply_surface(0,0,win,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 1)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/scissor_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 1;
                                        apply_surface(0,0,tryagain,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 2)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/stone_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 2;
                                        apply_surface(0,0,lose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        break;

                                        case SDLK_DOWN:

                                        goto restart;

                                        break;

                                        case SDLK_LEFT:
                                        choose = IMG_Load("assets/space1&2/pss_1.png");
                                        apply_surface(0,0,choose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(500);
                                        decision = IMG_Load("assets/space1&2/paper.png");
                                        apply_surface(0,300,decision,screen);
                                        p1 = 0;
                                        if(x == 0)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/paper_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        apply_surface(0,0,tryagain,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 1)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/scissor_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 1;
                                        apply_surface(0,0,lose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 2)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/stone_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 2;
                                        apply_surface(0,0,win,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        break;

                                        case SDLK_RIGHT:
                                        choose = IMG_Load("assets/space1&2/pss_s3.png");
                                        apply_surface(0,0,choose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(500);
                                        decision = IMG_Load("assets/space1&2/stone.png");
                                        apply_surface(0,300,decision,screen);
                                        p1 = 2;
                                        if(x == 0)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/paper_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        apply_surface(0,0,lose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 1)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/scissor_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 1;
                                        apply_surface(0,0,win,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 2)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/stone_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        p2 = 2;
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,tryagain,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        break;

                                        case SDLK_ESCAPE:
                                            SDL_FreeSurface(image);
                                            game->load_to(0);
                                            return 0;
                                            break;

                                        default:

                                        break;
                                    }
                        }
                    }

                }
            }
            // practice mode

            //challenge mode
            if(modeSelect == 2)
            {
                apply_surface(man_x_position,man_y_position,stage,screen);
                SDL_UpdateWindowSurface(game->window);

                while(quit == false)
                {
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_KEYDOWN)
                            {
                                if(e.key.keysym.sym == SDLK_RIGHT)
                                {
                                    quit = true;
                                }
                                if(e.key.keysym.sym == SDLK_ESCAPE)
                                {
                                    SDL_FreeSurface(image);
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

                image = IMG_Load("assets/space1&2/challenge.png"); // loads image
                apply_surface(man_x_position,man_y_position,image,screen);
                SDL_UpdateWindowSurface(game->window);
                SDL_Delay(100);
                apply_surface(man_x_position,man_y_position,image,screen);

                while(quit == false)
                {
                    srand( time(NULL));
                    int y = rand();
                    int x = rand() % 3;
                    x = (x+y) % 3;

                    if(blood_player == 0)
                    {
                        apply_surface(0,0,gameover,screen);
                        SDL_UpdateWindowSurface(game->window);
                        SDL_Delay(500);
                        goto restart;
                    }
                    if(blood_computer == 0)
                    {
                        apply_surface(0,0,win,screen);
                        SDL_UpdateWindowSurface(game->window);
                        SDL_Delay(500);
                        goto restart;
                    }
                    for(int t = 0;t < blood_player;t++)
                    {
                        apply_surface(100*t,500,heart,screen);
                    }
                    for (int i = 0; i < blood_computer; ++i)
                    {
                        apply_surface(700-100*i,0,heart,screen);
                    }
                    SDL_UpdateWindowSurface(game->window);
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_QUIT)
                        {
                            game->inSS_StopRunning();
                            return 0;
                        }
                        if(e.type == SDL_KEYDOWN)
                        {
                            //Select surfaces based on key press
                                    switch( e.key.keysym.sym )
                                    {
                                        case SDLK_UP:
                                        decision = IMG_Load("assets/space1&2/scissor.png");
                                        apply_surface(0,300,decision,screen);
                                        p1 = 1;
                                        if(x == 0)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/paper_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        blood_computer--;
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 1)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/scissor_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 1;
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 2)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/stone_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        blood_player--;
                                        p2 = 2;
                                        apply_surface(0,0,image,screen);
                                        }
                                        break;

                                        case SDLK_DOWN:

                                        break;

                                        case SDLK_LEFT:
                                        decision = IMG_Load("assets/space1&2/paper.png");
                                        apply_surface(0,300,decision,screen);
                                        p1 = 0;
                                        if(x == 0)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/paper_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 1)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/scissor_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 1;
                                        blood_player--;
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 2)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/stone_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 2;
                                        blood_computer--;
                                        apply_surface(0,0,image,screen);
                                        }
                                        break;

                                        case SDLK_RIGHT:
                                        decision = IMG_Load("assets/space1&2/stone.png");
                                        apply_surface(0,300,decision,screen);
                                        p1 = 2;
                                        if(x == 0)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/paper_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        blood_player--;
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 1)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/scissor_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 1;
                                        blood_computer--;
                                        apply_surface(0,0,image,screen);
                                        }
                                        if(x == 2)
                                        {
                                        decision2 = IMG_Load("assets/space1&2/stone_p2.png");
                                        apply_surface(0,0,decision2,screen);
                                        p2 = 2;
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,image,screen);
                                        }
                                        break;

                                        case SDLK_ESCAPE:
                                            SDL_FreeSurface(image);
                                            game->load_to(0);
                                            return 0;
                                            break;

                                        default:

                                        break;
                                    }
                        }
                    }

                }
            }
            break;
        }
    case 2:
        {
            int man_x_position = 0;
            int man_y_position = 0;
            int p1 = 0;
            int p2 = 0;
            bool quit = false;

            // initialize surfaces
            SDL_Surface* instruction = NULL;
            SDL_Surface* man = NULL;
            SDL_Surface* decision = NULL;
            SDL_Surface* decision2 = NULL;
            SDL_Surface* title = NULL;
            SDL_Surface* choose = NULL;

            SDL_Event e;
            SDL_Surface* tryagain;
            tryagain = IMG_Load("assets/space1&2/tryAgain.png");
            SDL_Surface* win;
            win = IMG_Load("assets/space1&2/win.png");
            SDL_Surface* lose;
            lose = IMG_Load("assets/space1&2/lose.png");
            SDL_Surface* waiting1;
            SDL_Surface* waiting2;
            waiting1 = IMG_Load("assets/space1&2/waiting1.png");
            waiting2 = IMG_Load("assets/space1&2/waiting2.png");

            screen = SDL_GetWindowSurface(game->window);

            // using the same way to run this game as the previous game
            title = IMG_Load("assets/space1&2/kelp.png");
            apply_surface(man_x_position,man_y_position,title,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);

            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RIGHT)
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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

            instruction = IMG_Load("assets/space1&2/instruction.png");
            apply_surface(man_x_position,man_y_position,instruction,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);

            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RIGHT)
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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

            man = IMG_Load("assets/space1&2/man.png");
            apply_surface(man_x_position,man_y_position,man,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);

            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RIGHT)
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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

            int c = 1;
            image = IMG_Load("assets/space1&2/waiting1.png"); // loads image
            apply_surface(man_x_position,man_y_position,image,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);



            while(quit == false)
            {
                srand( time(NULL));
                int y = rand();
                int x = rand() % 3;

                SDL_UpdateWindowSurface(game->window);
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                    {
                        game->inSS_StopRunning();
                        return 0;
                    }
                    if(e.type == SDL_KEYDOWN)
                    {
                        //Select surfaces based on key press
                                switch( e.key.keysym.sym )
                                {
                                    case SDLK_UP:
                                    c++;
                                    decision = IMG_Load("assets/space1&2/up.png");
                                    apply_surface(0,0,decision,screen);
                                    p1 = 1;
                                    if(x == 0)
                                    {
                                        decision2 = IMG_Load("assets/space1&2/up_p2.png");
                                        apply_surface(400,0,decision2,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        p2 = 0;
                                        if(c-1 % 2 == 1)
                                        {
                                            apply_surface(0,0,win,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(1000);
                                            apply_surface(0,0,waiting1,screen);
                                            c = 1;
                                        }
                                        else
                                        {
                                            apply_surface(0,0,lose,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(1000);
                                            apply_surface(0,0,waiting1,screen);
                                            c = 1;
                                         }
                                    }
                                    if(x == 1)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/down_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);

                                        if(c % 2 == 1)
                                        {
                                            apply_surface(0,0,waiting1,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                        }
                                        else
                                        {
                                            apply_surface(0,0,waiting2,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                        }
                                    }
                                    if(x == 2)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/left_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                    p2 = 2;
                                        if(c % 2 == 1)
                                            {
                                                apply_surface(0,0,waiting1,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                            else
                                            {
                                                apply_surface(0,0,waiting2,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                    }
                                    break;

                                    case SDLK_DOWN:
                                    c++;
                                    decision = IMG_Load("assets/space1&2/down.png");
                                    apply_surface(0,0,decision,screen);
                                    p1 = 1;
                                    if(x == 0)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/up_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                     if(c % 2 == 1)
                                        {
                                            apply_surface(0,0,waiting1,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                        }
                                        else
                                        {
                                            apply_surface(0,0,waiting2,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                        }
                                    p2 = 0;
                                    }
                                    if(x == 1)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/down_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                        if(c-1 % 2 == 1)
                                        {
                                            apply_surface(0,0,win,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(1000);
                                            apply_surface(0,0,waiting1,screen);
                                            c = 1;
                                        }
                                        else
                                        {
                                            apply_surface(0,0,lose,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(1000);
                                            apply_surface(0,0,waiting1,screen);
                                            c = 1;
                                        }
                                    }
                                    if(x == 2)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/left_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                             if(c % 2 == 1)
                                            {
                                                apply_surface(0,0,waiting1,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                            else
                                            {
                                                apply_surface(0,0,waiting2,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                    }
                                    break;

                                    case SDLK_LEFT:
                                    c++;
                                    decision = IMG_Load("assets/space1&2/left.png");
                                    apply_surface(0,0,decision,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    p1 = 1;
                                    if(x == 0)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/up_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                     if(c % 2 == 1)
                                            {
                                                apply_surface(0,0,waiting1,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                            else
                                            {
                                                apply_surface(0,0,waiting2,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                    p2 = 0;
                                    }
                                    if(x == 1)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/down_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                     if(c % 2 == 1)
                                            {
                                                apply_surface(0,0,waiting1,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                            else
                                            {
                                                apply_surface(0,0,waiting2,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                    }
                                    if(x == 2)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/left_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                        if(c-1 % 2 == 1)
                                        {
                                            apply_surface(0,0,win,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(1000);
                                            apply_surface(0,0,waiting1,screen);
                                            c = 1;
                                        }
                                        else
                                        {
                                            apply_surface(0,0,lose,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(1000);
                                            apply_surface(0,0,waiting1,screen);
                                            c = 1;
                                        }
                                    }
                                    break;

                                    case SDLK_RIGHT:
                                        c++;
                                    decision = IMG_Load("assets/space1&2/left.png");
                                    apply_surface(0,0,decision,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    p1 = 1;
                                    if(x == 0)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/up_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                     if(c % 2 == 1)
                                            {
                                                apply_surface(0,0,waiting1,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                            else
                                            {
                                                apply_surface(0,0,waiting2,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                    p2 = 0;
                                    }
                                    if(x == 1)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/down_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                     if(c % 2 == 1)
                                            {
                                                apply_surface(0,0,waiting1,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                            else
                                            {
                                                apply_surface(0,0,waiting2,screen);
                                                SDL_UpdateWindowSurface(game->window);
                                            }
                                    }
                                    if(x == 2)
                                    {
                                    decision2 = IMG_Load("assets/space1&2/left_p2.png");
                                    apply_surface(400,0,decision2,screen);
                                    SDL_UpdateWindowSurface(game->window);
                                    SDL_Delay(1000);
                                    if(c-1 % 2 == 1)
                                    {
                                        apply_surface(0,0,win,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,waiting1,screen);
                                        c = 1;
                                    }
                                    else
                                    {
                                        apply_surface(0,0,lose,screen);
                                        SDL_UpdateWindowSurface(game->window);
                                        SDL_Delay(1000);
                                        apply_surface(0,0,waiting1,screen);
                                        c = 1;
                                    }
                                    }
                                    break;

                                    case SDLK_ESCAPE:
                                        SDL_FreeSurface(image);
                                        game->load_to(0);
                                        return 0;
                                        break;
                                    default:
                                        break;
                                }

                    }

                }

            }
            break;
        }
    case 3:
        {
            int man_x_position = 0;
            int man_y_position = 0;
            int p1 = 0;
            int p2 = 0;
            bool quit = false;
			//load images
            SDL_Surface* rules = NULL;
            SDL_Surface* p1turn = NULL;
            SDL_Surface* p2turn = NULL;
            SDL_Surface* f0 = NULL;
            SDL_Surface* f1 = NULL;
            SDL_Surface* f2 = NULL;
            SDL_Surface* f3 = NULL;
            SDL_Surface* f4 = NULL;
            SDL_Surface* rf0 = NULL;
            SDL_Surface* rf1 = NULL;
            SDL_Surface* rf2 = NULL;
            SDL_Surface* rf3 = NULL;
            SDL_Surface* rf4 = NULL;
            SDL_Surface* f02 = NULL;
            SDL_Surface* f12 = NULL;
            SDL_Surface* f22 = NULL;
            SDL_Surface* f32 = NULL;
            SDL_Surface* f42 = NULL;
            SDL_Surface* rf02 = NULL;
            SDL_Surface* rf12 = NULL;
            SDL_Surface* rf22 = NULL;
            SDL_Surface* rf32 = NULL;
            SDL_Surface* rf42 = NULL;
            f0 = IMG_Load("assets/space3/0.png");
            f1 = IMG_Load("assets/space3/1.png");
            f2 = IMG_Load("assets/space3/2.png");
            f3 = IMG_Load("assets/space3/3.png");
            f4 = IMG_Load("assets/space3/4.png");
            rf0 = IMG_Load("assets/space3/r0.png");
            rf1 = IMG_Load("assets/space3/r1.png");
            rf2 = IMG_Load("assets/space3/r2.png");
            rf3 = IMG_Load("assets/space3/r3.png");
            rf4 = IMG_Load("assets/space3/r4.png");
            rf02 = IMG_Load("assets/space3/rp20.png");
            rf12 = IMG_Load("assets/space3/rp21.png");
            rf22 = IMG_Load("assets/space3/rp22.png");
            rf32 = IMG_Load("assets/space3/rp23.png");
            rf42 = IMG_Load("assets/space3/rp24.png");
            f02 = IMG_Load("assets/space3/p20.png");
            f12 = IMG_Load("assets/space3/p21.png");
            f22 = IMG_Load("assets/space3/p22.png");
            f32 = IMG_Load("assets/space3/p23.png");
            f42 = IMG_Load("assets/space3/p24.png");
            p1turn = IMG_Load("assets/space3/111.png");
            p2turn= IMG_Load("assets/space3/222.png");


            SDL_Event e;
            SDL_Surface* p1win;
            p1win = IMG_Load("assets/space3/p1win.png");
            SDL_Surface* p2win;
            p2win = IMG_Load("assets/space3/p2win.png");

            screen = SDL_GetWindowSurface(game->window);

            image = IMG_Load("assets/space3/fin.png");
            apply_surface(man_x_position,man_y_position,image,screen);

            SDL_UpdateWindowSurface(game->window);

            SDL_Delay(1000);
			//show rules
            rules = IMG_Load("assets/space3/rules.png");
            apply_surface(man_x_position,man_y_position,rules,screen);
            SDL_UpdateWindowSurface(game->window);
            SDL_Delay(100);

            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_RETURN)
                            {
                                quit = true;
                            }
                            else if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(image);
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
			//initial screen
            apply_surface(0,250,p1turn,screen);
            apply_surface(man_x_position,man_y_position,f12,screen);
            apply_surface(man_x_position,300,f1,screen);
            apply_surface(400,300,rf1,screen);
            apply_surface(400,0,rf12,screen);
            apply_surface(0,234,p1turn,screen);
            SDL_UpdateWindowSurface(game->window);
			//player's data
                int x = 1;
                int y = 1;
                int z = 0;
                int p1l = 1;
                int p1r = 1;
                int p2l = 1;
                int p2r = 1;
                int now = 0;
                int rorl = 0;
            //game loop
            while(quit == false)
            {
                SDL_UpdateWindowSurface(game->window);
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                    {
                        game->inSS_StopRunning();
                        return 0;
                    }
                    if(e.type == SDL_KEYDOWN)
                    {
                                switch( e.key.keysym.sym )//determine events
                                {
                                    case SDLK_UP:
                                    if(z==0)
                                    {
                                        z = 1;
                                        break;
                                    }
                                    if(z==1)
                                    {
                                        if(y%2!=0)
                                        {
                                            if(rorl==1)
                                            {
                                               p1l -= 1;
                                               p1r += 1;
                                            }
                                            else if(rorl==2)
                                            {
                                               p1r -= 1;
                                               p1l += 1;
                                            }

                                        }
                                        else if(y%2==0)
                                        {
                                            if(rorl==1)
                                            {
                                               p2l -= 1;
                                               p2r += 1;
                                            }
                                            else if(rorl==2)
                                            {
                                               p2r -= 1;
                                               p2l += 1;
                                            }
                                        }
                                        z=0;
                                    }

                                    break;

                                    case SDLK_DOWN:
                                    if(z==0)
                                    {
                                        z = 1;
                                        break;

                                    }
                                    if(z==1)
                                    {
                                        if(y%2!=0)
                                        {
                                            if(rorl==1)
                                            {
                                               p1l -= 2;
                                               p1r += 2;
                                            }
                                            else if(rorl==2)
                                            {
                                               p1r -= 2;
                                               p1l += 2;
                                            }

                                        }
                                        else if(y%2==0)
                                        {
                                            if(rorl==1)
                                            {
                                               p2l -= 2;
                                               p2r += 2;
                                            }
                                            else if(rorl==2)
                                            {
                                               p2r -= 2;
                                               p2l += 2;
                                            }
                                        }
                                        z=0;
                                    }

                                    break;

                                    case SDLK_LEFT:
                                    if(x%2!=0 and z==0)
                                    {
                                        rorl = 1;
                                        if(y%2!=0)
                                        {
                                            now = p1l;
                                        }
                                        if(y%2==0)
                                        {
                                            now = p2l;
                                        }
                                    }
                                    else if(x%2==0 and z==0)
                                    {
                                        rorl = 1;
                                        if(y%2!=0)
                                        {
                                            p2l +=now;
                                            if(p2l>=5)
                                                p2l = 0;
                                        }
                                        else if(y%2==0)
                                        {
                                            p1l +=now;
                                            if(p1l>=5)
                                                p1l = 0;
                                        }
                                    }
                                    else if(z==1)

                                    {
                                        if(y%2!=0)
                                        {
                                            if(rorl==1)
                                            {
                                               p1l -= 3;
                                               p1r += 3;
                                            }
                                            else if(rorl==2)
                                            {
                                               p1r -= 3;
                                               p1l += 3;
                                            }

                                        }
                                        else if(y%2==0)
                                        {
                                            if(rorl==1)
                                            {
                                               p2l -= 3;
                                               p2r += 3;
                                            }
                                            else if(rorl==2)
                                            {
                                               p2r -= 3;
                                               p2l += 3;
                                            }
                                        }
                                        z=0;
                                    }
                                    break;
                                    case SDLK_RIGHT:
                                    if(x%2!=0 and z==0)
                                    {
                                        rorl = 2;
                                        if(y%2!=0)
                                        {
                                            now = p1r;
                                        }
                                        else if(y%2==0)
                                        {
                                            now = p2r;
                                        }
                                    }
                                    else if(x%2==0 and z==0)
                                    {
                                        if(y%2!=0)
                                        {
                                            p2r +=now;
                                            if(p2r>=5)
                                                p2r = 0;
                                        }
                                        else if(y%2==0)
                                        {
                                            p1r +=now;
                                            if(p1r>=5)
                                                p1r = 0;
                                        }
                                    }
                                    else if(z==1)
                                    {
                                        if(y%2!=0)
                                        {
                                            if(rorl==1)
                                            {
                                               p1l -= 4;
                                               p1r += 4;
                                            }
                                            else if(rorl==2)
                                            {
                                               p1r -= 4;
                                               p1l += 4;
                                            }

                                        }
                                        else if(y%2==0)
                                        {
                                            if(rorl==1)
                                            {
                                               p2l -= 4;
                                               p2r += 4;
                                            }
                                            else if(rorl==2)
                                            {
                                               p2r -= 4;
                                               p2l += 4;
                                            }
                                        }
                                        z=0;
                                    }

                                    break;

                                    case SDLK_ESCAPE:
                                        SDL_FreeSurface(image);
                                        game->load_to(0);
                                        return 0;
                                        break;
                                    default:
                                        break;
                                }
                                //if one hand has more than four fingers,it becomes zero
                                if(p1l<=0 or p1l >=5)
                                    p1l = 0;
                                if(p1r<=0 or p1r >=5)
                                    p1r = 0;
                                if(p2l<=0 or p2l >=5)
                                    p2l = 0;
                                if(p2r<=0 or p2r >=5)
                                    p2r = 0;

                                if(z==0)
                                {
                                    if(x%2==0)//turn ends
                                    {
                                        x+=1;
                                        y+=1;
                                        if(p1r==0)
                                            apply_surface(400,300,rf0,screen);
                                        else if(p1r==1)
                                            apply_surface(400,300,rf1,screen);
                                        else if(p1r==2)
                                            apply_surface(400,300,rf2,screen);
                                        else if(p1r==3)
                                            apply_surface(400,300,rf3,screen);
                                        else if(p1r==4)
                                            apply_surface(400,300,rf4,screen);
                                        if(p1l==0)
                                            apply_surface(man_x_position,300,f0,screen);
                                        else if(p1l==1)
                                            apply_surface(man_x_position,300,f1,screen);
                                        else if(p1l==2)
                                            apply_surface(man_x_position,300,f2,screen);
                                        else if(p1l==3)
                                            apply_surface(man_x_position,300,f3,screen);
                                        else if(p1l==4)
                                            apply_surface(man_x_position,300,f4,screen);
                                        if(p2l==0)
                                            apply_surface(0,0,f02,screen);
                                        else if(p2l==1)
                                            apply_surface(0,0,f12,screen);
                                        else if(p2l==2)
                                            apply_surface(0,0,f22,screen);
                                        else if(p2l==3)
                                            apply_surface(0,0,f32,screen);
                                        else if(p2l==4)
                                            apply_surface(0,0,f42,screen);
                                        if(p2r==0)
                                            apply_surface(400,0,rf02,screen);
                                        else if(p2r==1)
                                            apply_surface(400,0,rf12,screen);
                                        else if(p2r==2)
                                            apply_surface(400,0,rf22,screen);
                                        else if(p2r==3)
                                            apply_surface(400,0,rf32,screen);
                                        else if(p2r==4)
                                            apply_surface(400,0,rf42,screen);
                                        if(y%2!=0)
                                            apply_surface(0,234,p1turn,screen);
                                        else if(y%2==0)
                                            apply_surface(0,234,p2turn,screen);


                                        if(p1r ==0 and p1l==0)//p1 loses
                                        {
                                            apply_surface(0,0,p2win,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(3000);
                                            p1r = 1;
                                            p1l = 1;
                                            p2r = 1;
                                            p2l = 1;
                                            apply_surface(man_x_position,man_y_position,f12,screen);
                                            apply_surface(man_x_position,300,f1,screen);
                                            apply_surface(400,300,rf1,screen);
                                            apply_surface(400,0,rf12,screen);
                                            apply_surface(0,234,p1turn,screen);
                                            x =1 ;
                                            y = 1;
                                            z = 0;

                                        }
                                        else if(p2r ==0 and p2l==0)//p2 loses
                                        {
                                            apply_surface(0,0,p1win,screen);
                                            SDL_UpdateWindowSurface(game->window);
                                            SDL_Delay(3000);
                                            p1r = 1;
                                            p1l = 1;
                                            p2r = 1;
                                            p2l = 1;
                                            apply_surface(man_x_position,man_y_position,f12,screen);
                                            apply_surface(man_x_position,300,f1,screen);
                                            apply_surface(400,300,rf1,screen);
                                            apply_surface(400,0,rf12,screen);
                                            apply_surface(0,234,p1turn,screen);
                                            x = 1;
                                            y = 1;
                                            z = 0;
                                        }

                                    }
                                    else if(x%2!=0)//turn continues
                                    {
                                        x +=1;
                                    }
                                }

                    }
                }

            }
            break;
        }
    default:
        break;

    }
}
