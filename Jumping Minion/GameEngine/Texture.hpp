#ifndef Texture_hpp
#define Texture_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <algorithm>
#include "globals.hpp"

class Object;

class GraphicsComponent{
public:
    
    virtual ~GraphicsComponent(){}

    virtual void update(Object& obj, SDL_Renderer* renderer, double interp) = 0;
};

class GeneralGraphicsComponent : public GraphicsComponent{
    
    SDL_Texture *texture;

    SDL_Renderer *renderer;

public:
    
    GeneralGraphicsComponent(SDL_Texture *texture, SDL_Renderer *renderer)
    :texture(texture), renderer(renderer)
    {}

    virtual void update(Object& obj, SDL_Renderer* renderer, double interp);
};

SDL_Texture* loadTexture( char* path ,SDL_Renderer* renderer );

#endif
