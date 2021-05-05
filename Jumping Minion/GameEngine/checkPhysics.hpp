#ifndef checkPhysics_hpp
#define checkPhysics_hpp

#include "engine.hpp"
#include "globals.hpp"
#include <vector>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>


class Object;
class World;

class checkPhysics {
public:
    virtual ~checkPhysics(){}
    virtual void update(Object& obj, World& world)=0;
};

class PhysicsForPlayer : public checkPhysics {
    
bool checkCollisions(Object& player, std::vector<Object*> &platforms);

public:
    virtual void update(Object& obj, World& world);
    Mix_Chunk *jumpSound;
};

class PhysicsForPlatform : public checkPhysics {
    void checkDistances(Object* platform, std::vector<Object*> &platforms);
public:
    int checkSpeed;
    
    virtual void update(Object& obj, World& world);
};

#endif /* physicsComponent_hpp */
