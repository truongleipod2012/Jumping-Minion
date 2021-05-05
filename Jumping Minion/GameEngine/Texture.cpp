#include "Texture.hpp"

#include "Objects.hpp"

SDL_Texture* loadTexture( char* path ,SDL_Renderer* renderer )
{
    SDL_Surface* tmpsurface = NULL;
    tmpsurface = IMG_Load(path);
    if (tmpsurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: ", SDL_GetError());
    }
    
    //create texture to load it into
    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, tmpsurface);
    if (texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: ", SDL_GetError());
    }
    
    //free temp surface
    SDL_FreeSurface(tmpsurface);

    //return the loadedtexture
    return texture;
}

void GeneralGraphicsComponent::update(Object& obj, SDL_Renderer* renderer, double interp){
    
    int x_interp = obj.x + (int)(interp * obj.xspeed);

    int y_interp = std::max(obj.y + (int)(interp * obj.yspeed), SCREEN_HEIGHT / 15);

    SDL_Rect rect = {x_interp ,y_interp , obj.w , obj.h };

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
