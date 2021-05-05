//
//  inputComponent.hpp
//  Jumping Minion
//
//  Created by Truongle on 19/04/2021.
//

#ifndef userInput_hpp
#define userInput_hpp

#include <SDL2/SDL.h>

class Object;

class World;

class userInput{
public:
    
    virtual ~userInput(){}
    virtual void update(Object& obj, World& world) = 0;
    
};

class inputForMario : public userInput{
    
    bool *moveright, *moveleft;
    const double speed;
    
public:
    
    inputForMario(bool *moveright, bool *moveleft)
    :moveright(moveright),moveleft(moveleft),speed(0.7)
    {}
    virtual void update(Object& obj, World& world);
};

class inputForPlatform : public userInput{
public:
    
    virtual void update(Object& obj, World& world);
    
};

#endif /* inputComponent_hpp */
