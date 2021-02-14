#ifndef __TIMERZERO__
#define __TIMERZERO__

#include "Arduino.h"

class timerZero {
    public:
        static timerZero *getInstance();
        /* 
         * Initializes the timer so as to use the CTC (Clear Timer on Compare match) timer mode, stop the timer from
         * counting CPU clock cycles and reset its counter to zero.
         * It must be called one time before using the timer, otherwise it can bring to unpredictable results.
         */
        void init(void);

        void setPeriod(unsigned long int period);
        /* 
         * Sets the function called when the interrupt is fired and enables the firing of interrupts for the timer.
         * If this method is not called, the function is a routine which does nothing.
         */
        void attachInterrupt(void (*isr)(void));
        /* 
         * Disables the firing of interrupts, and set the function called when an interrupt is fired to a one that does nothing.
         */
        void detachInterrupt(void);
        /* 
         * Starts the timer.
         */
        void start(void);
        /* 
         * Stops the timer. It doesn't reset the value of the counter. That means that calling the start function after this one,
         * without calling the reset function, will cause the first interrupt to be called after the residual time period.
         */
        void stop(void);
        /*
         * Sets the timer counter to zero. It doesn't stop the timer from counting.
         */
        void reset(void);
        /*
         * Returns the callback routine currently called when the interrupt is fired.
         */
        void (*getCallback(void))(void);
    private:
        static timerZero *SINGLETON;

        timerZero(void);

        void (*_isrCallback)(void);
        char _clockSelectBits;
        int count; 
};

//Global variable accessible from the Arduino code for facilitating the use of this timer library
extern timerZero timer0;

#endif
