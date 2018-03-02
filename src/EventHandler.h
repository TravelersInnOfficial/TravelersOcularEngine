#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "TOcularEngine/IODriver.h"

class EventHandler : public IODriver{
public:
    EventHandler();
    ~EventHandler();

	bool OnEvent(const TEvent& event);

    static float zdist;
    static float xdist;
};

#endif