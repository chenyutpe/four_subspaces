#include "Game.h"
#include "TitleObject.h"
#include "Subspace.h"
#include "SP4.h"

//initialize needed objects
TitleGraph* titlegraph;
Button* button_START;
Button* button_HELP;
Button* button_CREDIT;
SpottyBG* spottyBG;

subWindow* startWindow;
subWindow* helpWindow;
subWindow* creditWindow;

spaceButton* spaceB_1;
spaceButton* spaceB_2;
spaceButton* spaceB_3;
spaceButton* spaceB_4;

LoadingGraph* loadinggraph;

SubSpace* sp1;
SubSpace* sp2;
SubSpace* sp3;

Player* player;
Brick* brick1;
Brick* brick2;
Brick* brick3;
Brick* brick4;
Brick* brick5;
Goal* goal;
someGraphs* somegraphs;

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){}
Game::~Game(){free(this);}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;//SDL_WindowFlags

    //for possible future extension
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {

        window = SDL_CreateWindow(title, x, y, width, height, flags);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        state = 0;//To the title screen
        isRunning = true;   //at first, its running
        isLoading = false;  //at first, its not loading

        //Create Objects/

        titlegraph = new TitleGraph("assets/titlegraph.png");

        button_START = new Button("assets/button_START.png", 1);
        button_HELP = new Button("assets/button_HELP.png", 2);
        button_CREDIT = new Button("assets/button_CREDIT.png", 3);

        spottyBG = new SpottyBG("assets/circle.bmp","assets/black.bmp");

        startWindow = new subWindow("assets/window_start.png");
        helpWindow = new subWindow("assets/window_help.png");
        creditWindow = new subWindow("assets/window_credit.png");

        spaceB_1 = new spaceButton("assets/space_1.png", 1);
        spaceB_2 = new spaceButton("assets/space_2.png", 2);
        spaceB_3 = new spaceButton("assets/space_3.png", 3);
        spaceB_4 = new spaceButton("assets/space_4.png", 4);

        loadinggraph = new LoadingGraph("assets/loading.png");

        player = new Player("assets/white.png");
        brick1 = new Brick("assets/gray.png", 0, 30, 750, 50);
        brick2 = new Brick("assets/gray.png", 25, 110, 775, 50);
        brick3 = new Brick("assets/gray.png", 0, 300, 385, 50);
        brick4 = new Brick("assets/gray.png", 415, 300, 385, 50);
        brick5 = new Brick("assets/gray.png", 25, 450, 750, 50);
        goal = new Goal("assets/space4/goal.png");
        somegraphs = new someGraphs("assets/space4/title.png","assets/space4/instruction.png","assets/space4/failed.png","assets/space4/cleared.png");
        }
    else
    {
        cout << "Something went wrong!\n";
        isRunning = false;
    }
}

void Game::titleEvents()
{
    if(!isLoading)
    {
        if(Mix_PlayingMusic() == 0) //play the main theme music if it's not playing
        {
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
            Mix_Music* maintheme = Mix_LoadMUS("musics/maintheme.wav");
            //Mix_FadeInMusic(maintheme, -1, 500);
            Mix_PlayMusic(maintheme, -1);

        }

        SDL_Event titleEvent;
        SDL_PollEvent(&titleEvent);

        switch(titleEvent.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                //judge subWindow events only when it's opened
                if(button_START->subWin_opened)
                {
                    startWindow->subWinEvent(titleEvent, button_START);
                    //judge spaceButton events only when the start button's subWindow is opened
                    spaceB_1->spaceButtonEvent(titleEvent, this);
                    spaceB_2->spaceButtonEvent(titleEvent, this);
                    spaceB_3->spaceButtonEvent(titleEvent, this);
                    spaceB_4->spaceButtonEvent(titleEvent, this);
                }
                else if(button_HELP->subWin_opened)
                {
                    helpWindow->subWinEvent(titleEvent, button_HELP);
                }
                else if(button_CREDIT->subWin_opened)
                {
                    creditWindow->subWinEvent(titleEvent, button_CREDIT);
                }
                else //don't judge any button event if a subWindow is opened
                {
                    button_START->ButtonEvent(titleEvent);
                    button_HELP->ButtonEvent(titleEvent);
                    button_CREDIT->ButtonEvent(titleEvent);
                }

                break;
            }
    }
}

void Game::titleRender()
{
    if(!isLoading)
    {
        SDL_RenderClear(renderer); //clear the current rendering target

        //put objects to rendering target
        spottyBG->render();

        titlegraph->render();

        button_START->render();
        button_HELP->render();
        button_CREDIT->render();

        //show subWindow only when it's opened
        if(button_START->subWin_opened)
        {
            startWindow->render();
            spaceB_1->render();
            spaceB_2->render();
            spaceB_3->render();
            spaceB_4->render();
        }
        else if(button_HELP->subWin_opened)
        {
            helpWindow->render();
        }
        else if(button_CREDIT->subWin_opened)
        {
            creditWindow->render();
        }

        SDL_RenderPresent(renderer);
    }

}

void Game::load_to(const int number)
{
    isLoading = true; //to avoid other events and rendering
    Mix_FadeOutMusic(1000);
    for(loadinggraph->alpha = 0 ; loadinggraph->alpha <= 255 ; loadinggraph->alpha += 51) //Fade in
    {
        loadinggraph->render();
    }
    for(int i = 0 ; i < 10 ; i++) //stay none-transparent for a while
    {
        loadinggraph->alpha = 255;
        loadinggraph->render();
    }
    for(;  loadinggraph->alpha >= 0 ; loadinggraph->alpha -= 51) //Fade out
    {
        loadinggraph->render();
    }
    state = number;
}

void Game::runSP123()
{
    switch(state)
    {
    case 1:
        sp1 = new SubSpace(1); //create a Subspace 1 object
        sp1->run(this);
        break;
    case 2:
        sp2 = new SubSpace(2); //create a Subspace 2 object
        sp2->run(this);
        break;
    case 3:
        sp3 = new SubSpace(3); //create a Subspace 3 object
        sp3->run(this);
        break;
    default:
        break;
    }

}

void Game::events()//actually only for Subspace 4 because or system design isn't good enough
{
    if(!isLoading)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    this->load_to(0); //load to title screen
                player->playerEvent(event);
                break;
            default:
                if(somegraphs->start == true)
                {
                    somegraphs->showgraph12(this);//instruction
                }
                else
                {
                    player->playerEvent(event);
                    //collision detect
                    if( brick1->collision(player) || brick2->collision(player) || brick3->collision(player) || brick4->collision(player) || brick5->collision(player))
                    {
                        somegraphs->showgraph34(2, this);//failed graph
                        player->reset();
                    }
                    //goaled
                    else if(goal->playerCome(player))
                    {
                        somegraphs->showgraph34(3, this);//cleared graph
                        somegraphs->start = true;
                    }
                }
                break;
        }
    }
}

void Game::update()
{
    player->movePlayer();
}
void Game::render()
{
    SDL_RenderClear(renderer);

    //put objects to rendering target
    brick1->render();
    brick2->render();
    brick3->render();
    brick4->render();
    brick5->render();
    goal->render();
    player->render();

    SDL_RenderPresent(renderer);
}
void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::running()
{
    return isRunning;
}

bool Game::inSS_StopRunning() //for Subspace1~3 to stop the game
{
    isRunning = false;
}
