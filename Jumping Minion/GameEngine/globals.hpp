#ifndef globals_hpp
#define globals_hpp

#include <time.h>

#define SCREEN_WIDTH 540
#define SCREEN_HEIGHT 800

inline double FPS_TO_MS(int fps) {return (double)1000 / fps;}

inline double getCurrentTime() {
    
    return ((double)clock() / CLOCKS_PER_SEC) * 1000;
    
}

extern bool scroll;

#endif /* globals_hpp */

