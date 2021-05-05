#ifndef Objects_hpp
#define Objects_hpp

#include <SDL2/SDL.h>

class World;
class userInput;
class checkPhysics;
class GraphicsComponent;

class Object{

    GraphicsComponent* graphics_;
    userInput* input_;
    checkPhysics* physics_;
  
  
public:
    
    int x, y, w, h;
    double xspeed, yspeed;

    Object( GraphicsComponent* graphics, userInput* input, checkPhysics* physics ) : graphics_(graphics), input_(input), physics_(physics){}

    void update(World& world);
    void draw(SDL_Renderer* renderer, double interp);
  
};

#endif
