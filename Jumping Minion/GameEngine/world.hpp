#ifndef world_hpp
#define world_hpp

#include <vector>
#include <SDL2/SDL.h>

class Object;

struct World{
private:
    
    Object* player;

    std::vector<Object*> platforms;
    
public:
    
    World()
    :player(NULL)
    {}

    Object* get_player()const {
        return this -> player;
    }

    void change_player(Object* new_player) {
        this -> player = new_player;
    }

    std::vector<Object*> &get_platforms() {
        return this -> platforms;
    }

    void add_platform(Object* new_platform) {
        platforms.push_back(new_platform);
    }

    void update();

    void draw(SDL_Renderer* renderer, double interp);
};

#endif /* world_hpp */
