#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "TOcularEngine/IODriver.h"

class EventHandler : public IODriver{
public:
    EventHandler();
    ~EventHandler();

	bool OnEvent(const TEvent& event);

    void Update();

    void CheckPressedKeys();

    float screenCenterX;
    float screenCenterY;

    static bool m_close;
    static int shaderType;
    
    static float xdist;
    static float ydist;
    static float zdist;

    static int PlayerX;
    static int PlayerZ;

    static float xlight;
    static float ylight;
    static float zlight;
    static bool  ChangeMain;
    static bool KP_ENTER;
    
    static float xdistGiro;
    static float ydistGiro;
    static float zdistGiro;
};

#endif