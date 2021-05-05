#include "userInput.hpp"
#include "Objects.hpp"
#include "world.hpp"

void inputForMario::update(Object& obj, World& world){
    
    if (*moveright) obj.xspeed += speed;

    else if (*moveleft) obj.xspeed -= speed;
    
}

void inputForPlatform::update(Object& obj, World& world){
}
