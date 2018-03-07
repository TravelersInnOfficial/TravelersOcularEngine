#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "TOcularEngine/IODriver.h"

class EventHandler : public IODriver{
public:
    EventHandler();
    ~EventHandler();

	bool OnEvent(const TEvent& event);

    static bool m_close;
    static float xdist;
    static float ydist;
    static float zdist;
    static float xdistGiro;
    static float ydistGiro;
    static float zdistGiro;
};

#endif