#include "Objects.hpp"
#include "world.hpp"
#include "userInput.hpp"
#include "checkPhysics.hpp"
#include "Texture.hpp"

void Object::update(World& world){
    input_ -> update (*this, world);
    physics_ -> update (*this, world);
}


void Object::draw(SDL_Renderer* renderer, double interp){
    graphics_ -> update (*this, renderer, interp);
    
}

