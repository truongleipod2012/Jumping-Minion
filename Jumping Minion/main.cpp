#include "engine.hpp"

#include <iostream>

int main(){
    
    Game game;

    if(game.init()) {
        std::cout << "Game started successfully\n";
        game.loop();
        std::cout << "Game exited successfully\n";
        return 0;
    }
    std::cout << "There was a problem starting the game\n";
    return 1;
}
