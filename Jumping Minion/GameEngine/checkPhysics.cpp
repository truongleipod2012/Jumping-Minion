#include "checkPhysics.hpp"
#include "Objects.hpp"
#include "world.hpp"
#include <iostream>

//hàm kiểm tra va chạm giữa mario và platform
bool PhysicsForPlayer::checkCollisions(Object& player, std::vector<Object*> &platforms){
    
    for(unsigned int i = 0; i < platforms.size(); i++){
        
        if(player.yspeed > 0) {
            
            if(player.x < platforms[i] -> x + platforms[i] -> w && player.x + player.w > platforms[i]->x && player.y + 5 * player.h / 6 < platforms[i] -> y + platforms[i] -> h && player.y + player.h > platforms[i] -> y) {
                    player.y = platforms[i] -> y - player.h;
                    return true;
          }
        }
    }
    return false;
}


void PhysicsForPlayer::update(Object& obj, World& world){
    //trong luc
    obj.yspeed += 0.5;
    
    obj.yspeed *= 0.99;
    
    jumpSound = Mix_LoadWAV("Assets/jumpSound.wav");

    //kiểm tra nếu mario đi quá rìa bên trái hoặc phải window, đưa mario sang bên kia
    if(obj.x + obj.w + obj.xspeed > SCREEN_WIDTH) {
        obj.x = 0;
    } else if (obj.x + obj.xspeed < 0) {
        obj.x = SCREEN_WIDTH - obj.w;
    }

    //nếu mario va chạm platform, mario sẽ nhảy lên trên với yspeed
    if(checkCollisions(obj, world.get_platforms())) {
        Mix_PlayChannel(-1, jumpSound, 0);
        obj.yspeed = -20;
    }

    obj.xspeed *= 0.9;
    obj.x += obj.xspeed;

    //kiểm tra nếu mario nhảy đến giữa chiều cao màn hình, kéo platform sẽ true và tốc độ kéo platforms xuống bằng tốc độ của mario khi vẫn nhảy lên
    if(obj.y + obj.yspeed >= SCREEN_HEIGHT / 2) {
        obj.y += obj.yspeed;
        scroll = false;
    } else {
        obj.y = SCREEN_HEIGHT / 2;
        scroll = true;
    }
}

/*void PhysicsForPlatform::checkDistances(Object* platform, std::vector<Object*> &platforms){
    Minimum distance between platforms
    for(unsigned int i = 1; i < platforms.size(); i++) {
        if(platform != platforms[i]) {
            while(abs(platform -> y - platforms[i] -> y) <= 50) {
                    platform -> y--;
            }
        }
    }
}*/

void PhysicsForPlatform::update(Object& obj, World& world){
    // checkDistances(&obj, world.get_platforms());

    Object* player = world.get_player();
    

    //scroll thanh platform
    if (scroll && player -> yspeed < 0) {
        obj.yspeed = -player -> yspeed;
        
        checkSpeed = -player -> yspeed;
        //std::cout << checkSpeed << std::endl;
        
        
    }

    if(obj.y + obj.yspeed > SCREEN_HEIGHT) {
        obj.y = -obj.h - rand() % 100;
        obj.x = rand() % SCREEN_WIDTH;
    }

    if (obj.x + obj.w + obj.xspeed > SCREEN_WIDTH) {
        obj.x = SCREEN_WIDTH - obj.w;
    } else if (obj.x + obj.w + obj.xspeed < 0) {
        obj.x = 0;
    }
    
    obj.x += obj.xspeed;
    obj.y += obj.yspeed;
}
