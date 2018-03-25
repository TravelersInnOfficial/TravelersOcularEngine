#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "TOcularEngine/IODriver.h"

class EventHandler : public IODriver{
public:
    EventHandler();
    ~EventHandler();

	bool OnEvent(const TEvent& event);

    void Update();

    float screenCenterX;
    float screenCenterY;

    static bool m_close;
    static int shaderType;
    
    static float xdist;
    static float ydist;
    static float zdist;

    static float xlight;
    static float ylight;
    static float zlight;
    
    static float xdistGiro;
    static float ydistGiro;
    static float zdistGiro;

    bool Key_A_Pressed;
    bool Key_D_Pressed;
    bool Key_S_Pressed;
    bool Key_W_Pressed;

    bool Key_Y_Pressed;
    bool Key_U_Pressed;
    bool Key_I_Pressed;
    bool Key_K_Pressed;
    bool Key_O_Pressed;
    bool Key_L_Pressed;
};

#endif