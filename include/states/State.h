#ifndef STATE_H
#define STATE_H

#include "hardware/Display.h"
#include "hardware/LED.h"

class State
{
public:
    virtual void enter() = 0;       // Called when entering the state
    virtual void update() = 0;      // Called in the main loop
    virtual void handleInput() = 0; // Handle button presses
    virtual void exit() = 0;        // Called when leaving the state
    virtual ~State() = default;
};

#endif