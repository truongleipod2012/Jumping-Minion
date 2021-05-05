#include <iostream>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "engine.hpp"
#include "Objects.hpp"
#include "globals.hpp"
#include "world.hpp"
#include "button.h"

#include "checkPhysics.hpp"
#include "userInput.hpp"
#include "Texture.hpp"

#define FPS 60


bool Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    } else {
        window = SDL_CreateWindow("Jumping Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }
    
    srand(time(0));
    
    //main menu & buttons
    mainMenu = IMG_LoadTexture(renderer, "Assets/mainMenu.png");
    SDL_QueryTexture(mainMenu, NULL, NULL, &menuRect.w, &menuRect.h);
    menuRect.x = 88;
    menuRect.y = 125;
    menuRect.w /= 2;
    menuRect.h /= 2;
    
    playButton = IMG_LoadTexture(renderer, "Assets/playButton_untouch.png");
    SDL_QueryTexture(playButton, NULL, NULL, &playRect1.w, &playRect1.h);
    playRect1.x = 127;
    playRect1.y = 400;
    playRect1.w /= 2;
    playRect1.h /= 2;
    
    playButton_touched = IMG_LoadTexture(renderer, "Assets/playButton_touched.png");
    SDL_QueryTexture(playButton_touched, NULL, NULL, &playRect2.w, &playRect2.h);
    playRect2.x = 127;
    playRect2.y = 400;
    playRect2.w /= 2;
    playRect2.h /= 2;
    
    quitButton = IMG_LoadTexture(renderer, "Assets/quitButton_untouch.png");
    SDL_QueryTexture(quitButton, NULL, NULL, &quitRect1.w, &quitRect1.h);
    quitRect1.x = 127;
    quitRect1.y = 520;
    quitRect1.w /= 2;
    quitRect1.h /= 2;
    
    quitButton_touched = IMG_LoadTexture(renderer, "Assets/quitButton_touched.png");
    SDL_QueryTexture(quitButton_touched, NULL, NULL, &quitRect2.w, &quitRect2.h);
    quitRect2.x = 127;
    quitRect2.y = 520;
    quitRect2.w /= 2;
    quitRect2.h /= 2;
    
    settingButton = IMG_LoadTexture(renderer, "Assets/settingButton_untouch.png");
    SDL_QueryTexture(settingButton, NULL, NULL, &settingRect1.w, &settingRect1.h);
    settingRect1.x = 270;
    settingRect1.y = 520;
    settingRect1.w /= 2;
    settingRect1.h /= 2;
    
    settingButton_touched = IMG_LoadTexture(renderer, "Assets/settingButton_touched.png");
    SDL_QueryTexture(settingButton_touched, NULL, NULL, &settingRect2.w, &settingRect2.h);
    settingRect2.x = 270;
    settingRect2.y = 520;
    settingRect2.w /= 2;
    settingRect2.h /= 2;
    
    //game over & buttons
    gameOverMenu = IMG_LoadTexture(renderer, "Assets/gameOverMenu.png");
    SDL_QueryTexture(gameOverMenu, NULL, NULL, &gameOverRect.w, &gameOverRect.h);
    gameOverRect.x = 88;
    gameOverRect.y = 125;
    gameOverRect.w /= 2;
    gameOverRect.h /= 2;
    
    replayButton = IMG_LoadTexture(renderer, "Assets/replayButton_untouch.png");
    SDL_QueryTexture(replayButton, NULL, NULL, &replayRect1.w, &replayRect1.h);
    replayRect1.x = 270;
    replayRect1.y = 520;
    replayRect1.w /= 2;
    replayRect1.h /= 2;
    
    replayButton_touched = IMG_LoadTexture(renderer, "Assets/replayButton_touched.png");
    SDL_QueryTexture(replayButton_touched, NULL, NULL, &replayRect2.w, &replayRect2.h);
    replayRect2.x = 270;
    replayRect2.y = 520;
    replayRect2.w /= 2;
    replayRect2.h /= 2;

    //load objects
    background = IMG_LoadTexture(renderer,"Assets/background.png");
    SDL_QueryTexture(background, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
    backgroundRect.x = 0;
    backgroundRect.y = 77;
    backgroundRect.w = SCREEN_WIDTH;
    backgroundRect.h = SCREEN_HEIGHT - 77;
    
    platform = IMG_LoadTexture(renderer,"Assets/platform.png");
    player = IMG_LoadTexture(renderer, "Assets/player1.png");
    
    //sounds
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    backSong = Mix_LoadMUS("Assets/backgroundSong.wav");
    Mix_PlayMusic(backSong, -1);
    dieEffect = Mix_LoadWAV("Assets/marioDie.wav");
    
    //font
    gFont = TTF_OpenFont( "Assets/Minecraft.ttf", 25 );
    textColor = {0, 0, 0, 0};
    std::string yourScore = "Score: " + std::to_string(score);
    textSurface = TTF_RenderText_Solid( gFont, yourScore.c_str(), textColor );
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = 50;
    textRect.y = 30;
    

    //tao ra 1 game world
    World* game_world = new World();
    this -> world = game_world;

    platformCount = 15;

    // xu ly platform
    
    for(unsigned int i = 0; i < platformCount; i++){
        
        
      
        Object* plat = new Object(new GeneralGraphicsComponent(platform, renderer), new inputForPlatform(), new PhysicsForPlatform());
          
        plat -> w = 100;
        plat -> h = 25;
          
        short x;
          
        if (i == 0) x = SCREEN_WIDTH / 2 - plat -> w / 2;
        x = rand() % SCREEN_WIDTH - plat -> w;

        short y = SCREEN_HEIGHT - ( i * 100);
        plat -> x = x;
        plat -> y = y;

        world -> add_platform(plat);
        
    }
    
    // xu ly player
    Object* mario = new Object(new GeneralGraphicsComponent(player, renderer), new inputForMario(&moveright, &moveleft), new PhysicsForPlayer());

    mario -> w = 40;
    mario -> h = 50;

    mario -> y = SCREEN_HEIGHT - 100;
    mario -> x = SCREEN_WIDTH / 2;

    mario -> yspeed = -22;

    world -> change_player(mario);
    
    return true;
}

void Game::handleInput() {

    while(SDL_PollEvent(&event) != 0) {

        switch(event.type) {
            
            case SDL_QUIT:
                done = true;
                break;
                
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_a) moveleft = true;
                if(event.key.keysym.sym == SDLK_d) moveright = true;
                break;
                
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_a) moveleft = false;
                if(event.key.keysym.sym == SDLK_d) moveright = false;
                break;
        }
    }
}


void Game::update() {
    world -> update();
    Object* mario = world -> get_player();
    if( mario -> y + mario -> h >= SCREEN_HEIGHT ) {
        done = true;
    }
}

void Game::render(double interp) {
    
    SDL_RenderClear(renderer);
    
    //render background
    
    SDL_RenderCopy(renderer, background, NULL, &backgroundRect);

    //render tat ca ra window
    world -> draw(renderer, interp);
    
    
    
    //render thanh cong cu tren cung
    SDL_Rect rect = {0 ,0 , SCREEN_WIDTH , 77 };
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_RenderCopy( renderer, textTexture, NULL, &textRect);
    
    

    SDL_RenderPresent(renderer);
}

bool Game::askContinue() {
    bool quit = false;
    while (!quit) {
        SDL_PollEvent(&event);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, gameOverMenu, NULL, &gameOverRect);
        
        
            int x, y;
            Uint8 button = SDL_GetMouseState( &x, &y );

            bool insideReplay = true;
            bool insideExit = true;
            
            if (x < replayRect1.x || x > replayRect1.x + replayRect1.w || y < replayRect1.y || y > replayRect1.y + replayRect1.h) {
                insideReplay = false;
            }
            if (!insideReplay) {
                SDL_RenderCopy(renderer, replayButton, NULL, &replayRect1);
            }
            else {
                SDL_RenderCopy(renderer, replayButton_touched, NULL, &replayRect2);
                if (button) {
                    return true;
                }
            }

            if (x < quitRect1.x || x > quitRect1.x + quitRect1.w || y < quitRect1.y || y > quitRect1.y + quitRect1.h) {
                insideExit = false;
            }
            if (!insideExit) {
                SDL_RenderCopy(renderer, quitButton, NULL, &quitRect1);
            } else {
                SDL_RenderCopy(renderer, quitButton_touched, NULL, &quitRect2);
                if (button){
                    return false;
                }
                
                    
            }
            

        SDL_RenderPresent(renderer);
        
    }
    return true;
}

void Game::loop() {
    
    done = false;
    bool inMenu = true;
    bool playAgain = false;
    
    while (!done && inMenu){
        if (event.type == SDL_QUIT) done = true;
        while (SDL_PollEvent(&event) != 0){
            SDL_RenderCopy(renderer, background, NULL, NULL);
            SDL_RenderCopy(renderer, mainMenu, NULL, &menuRect);
            if (event.type == SDL_QUIT){
                break;
            }
            if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                int x, y;
                SDL_GetMouseState( &x, &y );

                bool insidePlay = true;
                bool insideExit = true;
                bool insideSetting = true;
                
                if (x < playRect1.x || x > playRect1.x + playRect1.w || y < playRect1.y || y > playRect1.y + playRect1.h) {
                    insidePlay = false;
                }
                
                if (!insidePlay){
                    SDL_RenderCopy(renderer, playButton, NULL, &playRect1);
                } else {
                    SDL_RenderCopy(renderer, playButton_touched, NULL, &playRect2);
                    if (event.type == SDL_MOUSEBUTTONDOWN){
                        inMenu = false;
                        break;
                    }
                }
                
                    if (x < settingRect1.x || x > settingRect1.x + settingRect1.w || y < settingRect1.y || y > settingRect1.y + settingRect1.h) {
                        insideSetting = false;
                    }
                
                    if (!insideSetting) {
                        SDL_RenderCopy(renderer, settingButton, NULL, &settingRect1);
                    } else {
                        SDL_RenderCopy(renderer, settingButton_touched, NULL, &settingRect2);
                    }
                
                    if (x < quitRect1.x || x > quitRect1.x + quitRect1.w || y < quitRect1.y || y > quitRect1.y + quitRect1.h) {
                        insideExit = false;
                    }
                    if (!insideExit) {
                        SDL_RenderCopy(renderer, quitButton, NULL, &quitRect1);
                    } else {
                        SDL_RenderCopy(renderer, quitButton_touched, NULL, &quitRect2);
                        if (event.type == SDL_MOUSEBUTTONDOWN){
                            done = true;
                        }
                    }
                    SDL_RenderPresent(renderer);
                }
            }
        }
    
    
    do {
        
        Mix_ResumeMusic();
        init();
        while (!done) {

            
            if (!Mix_PlayingMusic()) {
                Mix_PlayMusic(backSong, -1);
            }
            
            score += PhysicsForPlatform().checkSpeed;
            std::cout << score <<std:: endl;
            
            
            
            handleInput();
            world -> update();
            Object* mario = world -> get_player();
            if( mario -> y + mario -> h >= SCREEN_HEIGHT ) {
                break;
            }
            render(0); 
            
            SDL_Delay(FPS_TO_MS(FPS));
        }
        Mix_PauseMusic();
        Mix_PlayChannel(-1, dieEffect, 0);
        playAgain = askContinue();
        if (playAgain) {
            done = false;
        }
    }while (playAgain);
    
    exit();
}



void Game::exit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(backSong);
    Mix_FreeChunk(dieEffect);
    Mix_CloseAudio();

    window = NULL;
    renderer = NULL;

    SDL_Quit();
}


