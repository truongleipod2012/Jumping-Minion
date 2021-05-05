#ifndef engine_hpp
#define engine_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>


class World;

class Game{
    
public:
    
    Game():window(NULL),renderer(NULL),done(false){}
    bool init();
    void loop();
    
    int platformCount = 15;
    int score = 0;
    
    

private:
    
    //textures for main menu
    SDL_Texture* mainMenu;
    SDL_Rect menuRect;
    
    SDL_Texture* playButton;
    SDL_Rect playRect1;
    
    SDL_Texture* playButton_touched;
    SDL_Rect playRect2;

    SDL_Texture* quitButton;
    SDL_Rect quitRect1;
    
    SDL_Texture* quitButton_touched;
    SDL_Rect quitRect2;

    SDL_Texture* settingButton;
    SDL_Rect settingRect1;
    
    SDL_Texture* settingButton_touched;
    SDL_Rect settingRect2;
    
    //textures for game over
    SDL_Texture* gameOverMenu;
    SDL_Rect gameOverRect;
    
    SDL_Texture* replayButton;
    SDL_Rect replayRect1;
    
    SDL_Texture* replayButton_touched;
    SDL_Rect replayRect2;
    
    //musics
    Mix_Music *backSong;
    Mix_Chunk *dieEffect;
    
    //font
    TTF_Font* gFont;
    SDL_Color textColor;
    SDL_Rect textRect;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
  
    //init textures for objects
    SDL_Texture* background;
    SDL_Rect backgroundRect;
    
    SDL_Texture* platform;
    SDL_Texture* player;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool done;

    World* world;
    bool moveleft, moveright;
    bool menu1 = true;

    void handleInput();
    bool askContinue();
    void update();
    void render(double interp);
    void exit();

};

#endif

