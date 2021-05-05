#include "world.hpp"
#include "Objects.hpp"

void World::update() {
    
    player -> update(*this);
    for(int i = 0; i < platforms.size(); i++) {
        platforms[i] -> update(*this);
    }

}

void World::draw(SDL_Renderer* renderer, double interp){
    
    for(int i = 0; i < platforms.size(); i++) {
        platforms[i] -> draw(renderer, interp);
    }

    player -> draw(renderer, interp);
}
