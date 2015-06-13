#ifndef ANIMATION_HPP   
#define ANIMATION_HPP

#include <ctime>
#include <thread>

class Animation;

#include "LedStrip.hpp"

enum refreshMode{
    THREADED_CONTINOUS,
    THREADED_TIMED,
    CONTINOUS,
    TIMED,
};

/**
 * A class used to standardize led animations.
 */
class Animation{
    clock_t lastUpdate;
    clock_t updateDiff;///< the number of ticks between two update.
    std::thread *thread;
    bool stopThread;///< the thread loop will check this atribute to know when stop.


    //Animation(bool threaded, int freq, void (*threadFunction)(Animation*)=autoRefresh);

    protected :
    static void autoRefresh(Animation *);
    LedStrip* leds;

    /**
     * \param threaded indicate if the application update itself
     * \param freq the freqeunce (in Hz) to refresh the Animation
     */
//    Animation(bool threaded, int freq);
    Animation(void (threadFunction)(Animation*));
    //static void autoCall(Animation*);///< a function which can be called by thread to auto refresh animation
    virtual void doAnimationStep() = 0;

    public :
    void compute();
    void setStrip(LedStrip*);






    Animation(bool threaded, int freq, void (*threadFunction)(Animation*)=autoRefresh);
};

#endif
