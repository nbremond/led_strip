#include "Animation.hpp"



//private

//protected

Animation::Animation(bool threaded, int freq, void (*threadFunction)(Animation*)):
    lastUpdate(0),
    thread(NULL),
    leds(NULL){
        if (freq > 0){
            updateDiff = CLOCKS_PER_SEC/freq;
        }else{
            updateDiff = 0;
        }

        if (threaded){
            //threadFunction = autoCall;
            thread = new std::thread(threadFunction, this);
            stopThread = false;
        }else{
            thread = NULL;
        }
    }

void Animation::autoRefresh(Animation* a){
    while (!a->stopThread){
        a->compute();
        struct timespec t;
        t.tv_sec=0;
        t.tv_nsec = (a->lastUpdate + a->updateDiff - clock())*((1000000000/CLOCKS_PER_SEC));
        //printf("now:%ld\tlast:%ld\tudif;%ld\tsleep_clk%ld\tsleep_ns%ld\tcps:%ld\n",
        //        clock(),
        //        a->lastUpdate,
        //        a->updateDiff,
        //        (a->lastUpdate + a->updateDiff - clock()),
        //        t.tv_nsec,
        //        CLOCKS_PER_SEC);
        struct timespec rem;
        while (nanosleep(&t,&rem)==-1 && errno == EINTR){
            t=rem;
            printf("try again!\n");
        }
       
    }
}

//public

void Animation::compute(){
    clock_t now = clock();

    if (leds == NULL){
        lastUpdate = now;//add something?
        return;
    }

    if (updateDiff == 0){
        doAnimationStep();
        lastUpdate = now;
    }

    if (now > lastUpdate+updateDiff){
        doAnimationStep();
        lastUpdate += updateDiff;
    }
}

void Animation::setStrip(LedStrip *l){
    leds = l;
}
