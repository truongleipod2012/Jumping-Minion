//
//  button.h
//  Jumping Minion
//
//  Created by Truongle on 04/05/2021.
//
/*
#ifndef button_h
#define button_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

SDL_Texture* loadTexture( std::string path ,SDL_Renderer* renderer )
{
    SDL_Surface* tmpsurface = NULL;
    tmpsurface = IMG_Load(path.c_str());
    if (tmpsurface == NULL)
    {
        cout << "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError();
    }
    
    //create texture to load it into
    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, tmpsurface);
    if (texture == NULL)
    {
        cout << "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError();
    }
    
    //free temp surface
    SDL_FreeSurface(tmpsurface);

    //return the loadedtexture
    return texture;
}

struct Button{
    int x, y;
    SDL_Texture* button;
    Button (int _x, int _y, const char* _b, SDL_Renderer* renderer){
        SDL_Rect but;
        button = loadTexture(_b, rend);
        SDL_QueryTexture(button, NULL, NULL, &but.w, &but.h);
        but.x = _x;
        but.y = _y;
    }
};


#endif */
