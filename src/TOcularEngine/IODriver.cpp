#include "IODriver.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <GLFW/glfw3.h> //SIEMPRE DESPUES DE INCLUIR GLEW

TEvent::TEvent(){}

TEvent::~TEvent(){}

IODriver::IODriver(){
    m_close = false;
}

IODriver::~IODriver(){}

bool IODriver::UpdateKeyboard(int key, int action){
    std::cout<<"key: "<<key<<"\n";
    std::cout<<"action: "<<action<<"\n";
    TEvent glfwEvent;
    glfwEvent.m_type = Type_Unknow;

    //GLFW_PRESS or GLFW_RELEASE.
    switch(action){
        case GLFW_PRESS:{
            glfwEvent.m_type = Type_KeyPressed;
            // Key Data
            glfwEvent.m_key.code     = ConvertKeyGLFW(key);
            glfwEvent.m_key.alt      = false;
            glfwEvent.m_key.control  = false;
            glfwEvent.m_key.shift    = false;
            glfwEvent.m_key.system   = false;
            break;
        }
        case GLFW_RELEASE:{
            glfwEvent.m_type = Type_KeyReleased;
            // Key Data
            glfwEvent.m_key.code     = ConvertKeyGLFW(key);
            glfwEvent.m_key.alt      = false;
            glfwEvent.m_key.control  = false;
            glfwEvent.m_key.shift    = false;
            glfwEvent.m_key.system   = false;
            break;
        }
    }

    const TEvent* pointer = &glfwEvent;
    return OnEvent(*pointer);
}

bool IODriver::UpdateMousePosition(int xpos, int ypos){
    std::cout<<"mouse x pos: "<<xpos<<"\n";
    std::cout<<"mouse y pos: "<<ypos<<"\n";
    TEvent glfwEvent;
    glfwEvent.m_type = Type_MouseMoved;

    glfwEvent.m_mouseMove.x = xpos;
    glfwEvent.m_mouseMove.y = ypos;

    const TEvent* pointer = &glfwEvent;
    return OnEvent(*pointer);
}

bool IODriver::UpdateMouseButtons(int button, int action){
    std::cout<<"button: "<<button<<"\n";
    std::cout<<"action: "<<action<<"\n";
    TEvent glfwEvent;
    glfwEvent.m_type = Type_Unknow;

    switch(button){
        case GLFW_PRESS:{
            glfwEvent.m_type = Type_MouseButtonPressed;
            // Mouse Button
            glfwEvent.m_mouseButton.button   = ConvertKeyGLFW(button);
            glfwEvent.m_mouseButton.x        = 0;
            glfwEvent.m_mouseButton.y        = 0;
            break;
        }
        case GLFW_RELEASE:{
            glfwEvent.m_type = Type_MouseButtonReleased;
            // Mouse Button
            glfwEvent.m_mouseButton.button   = ConvertKeyGLFW(button);
            glfwEvent.m_mouseButton.x        = 0;
            glfwEvent.m_mouseButton.y        = 0;
            break;
        }
    }

    const TEvent* pointer = &glfwEvent;
    return OnEvent(*pointer);
}

bool IODriver::UpdateMouseWheel(int xoffset, int yoffset){
    std::cout<<"xoffset: "<<xoffset<<"\n";
	std::cout<<"yoffset: "<<yoffset<<"\n";
    TEvent glfwEvent;
    glfwEvent.m_type = Type_MouseWheelScrolled;

    //TODO:: EDIT
    glfwEvent.m_mouseWheel.delta = 0;
    glfwEvent.m_mouseWheel.x     = xoffset;
    glfwEvent.m_mouseWheel.y     = yoffset;
    

    const TEvent* pointer = &glfwEvent;
    return OnEvent(*pointer);
}

bool IODriver::Update(sf::Event* event){

    TEvent sfEvent;

    sfEvent.m_type = Type_Unknow;
    switch(event->type){
        case sf::Event::Closed:{
            sfEvent.m_type = Type_Closed;
            // No Data
            break;
        }
        case sf::Event::Resized:{
            sfEvent.m_type = Type_Resized;
            // Window Size
            sfEvent.m_size.width     = event->size.width;
            sfEvent.m_size.height    = event->size.height;
            break;
        }
        case sf::Event::LostFocus:{
            sfEvent.m_type = Type_LostFocus;
            // No Data
            break;
        }
        case sf::Event::GainedFocus:{
            sfEvent.m_type = Type_GainedFocus;
            // No Data
            break;
        }
        case sf::Event::TextEntered:{
            sfEvent.m_type = Type_TextEntered;
            // Char Enter
            sfEvent.m_text.unicode = event->text.unicode; 
            break;
        }
        /*
        case sf::Event::KeyPressed:{
            sfEvent.m_type = Type_KeyPressed;
            // Key Data
            sfEvent.m_key.code     = (KeyboardKey)event->key.code;
            sfEvent.m_key.alt      = event->key.alt;
            sfEvent.m_key.control  = event->key.control;
            sfEvent.m_key.shift    = event->key.shift;
            sfEvent.m_key.system   = event->key.system;
            break;
        }
        case sf::Event::KeyReleased:{
            sfEvent.m_type = Type_KeyReleased;
            // Key Data
            sfEvent.m_key.code     = (KeyboardKey)event->key.code;
            sfEvent.m_key.alt      = event->key.alt;
            sfEvent.m_key.control  = event->key.control;
            sfEvent.m_key.shift    = event->key.shift;
            sfEvent.m_key.system   = event->key.system;
            break;
        }
        case sf::Event::MouseWheelScrolled:{
            sfEvent.m_type = Type_MouseWheelScrolled;
            // Mouse Wheel
            sfEvent.m_mouseWheel.delta = event->mouseWheel.delta;
            sfEvent.m_mouseWheel.x     = event->mouseWheel.x;
            sfEvent.m_mouseWheel.y     = event->mouseWheel.y;
            break;
        }
        case sf::Event::MouseButtonPressed:{
            sfEvent.m_type = Type_MouseButtonPressed;
            // Mouse Button
            sfEvent.m_mouseButton.button   = (KeyboardKey)(Key_MOUSE_START + event->mouseButton.button);
            sfEvent.m_mouseButton.x        = event->mouseButton.x;
            sfEvent.m_mouseButton.y        = event->mouseButton.y;
            break;
        }
        case sf::Event::MouseButtonReleased:{
            sfEvent.m_type = Type_MouseButtonReleased;
            // Mouse Button
            sfEvent.m_mouseButton.button   = (KeyboardKey)(Key_MOUSE_START + event->mouseButton.button);
            sfEvent.m_mouseButton.x        = event->mouseButton.x;
            sfEvent.m_mouseButton.y        = event->mouseButton.y;
            break;
        }
        case sf::Event::MouseMoved:{
            sfEvent.m_type = Type_MouseMoved;
            // Mouse Move
            sfEvent.m_mouseMove.x = event->mouseMove.x;
            sfEvent.m_mouseMove.y = event->mouseMove.y;
            break;
        }*/
        case sf::Event::MouseEntered:{
            sfEvent.m_type = Type_MouseEntered;
            // No Data
            break;
        }
        case sf::Event::MouseLeft:{
            sfEvent.m_type = Type_MouseLeft;
            // No Data
            break;
        }
        case sf::Event::JoystickButtonPressed:{
            sfEvent.m_type = Type_JoystickButtonPressed;
            // Joystick button
            sfEvent.m_joystickButton.joystickId    = event->joystickButton.joystickId;
            sfEvent.m_joystickButton.button        = event->joystickButton.button;
            break;
        }
        case sf::Event::JoystickButtonReleased:{
            sfEvent.m_type = Type_JoystickButtonReleased;
            // Joystick button
            sfEvent.m_joystickButton.joystickId    = event->joystickButton.joystickId;
            sfEvent.m_joystickButton.button        = event->joystickButton.button;
            break;
        }
        case sf::Event::JoystickMoved:{
            sfEvent.m_type = Type_JoystickMoved;
            // Joystick move
            sfEvent.m_joystickMove.joystickId  = event->joystickMove.joystickId;
            sfEvent.m_joystickMove.axis        = (JoystickAxis)event->joystickMove.axis;
            sfEvent.m_joystickMove.position    = event->joystickMove.position;
            break;
        }
        case sf::Event::JoystickConnected:{
            sfEvent.m_type = Type_JoystickConnected;
            // Joystick id
            sfEvent.m_joystickConnect.joystickId = event->joystickConnect.joystickId;
            break;
        }
        case sf::Event::JoystickDisconnected:{
            sfEvent.m_type = Type_JoystickDisconnected;
            // Joystick id
            sfEvent.m_joystickConnect.joystickId = event->joystickConnect.joystickId;
            break;
        }
        case sf::Event::TouchBegan:{
            sfEvent.m_type = Type_TouchBegan;
            // Touch 
            sfEvent.m_touch.finger     = event->touch.finger;
            sfEvent.m_touch.x          = event->touch.x;
            sfEvent.m_touch.y          = event->touch.y;
            break;
        }
        case sf::Event::TouchMoved:{
            sfEvent.m_type = Type_TouchMoved;
            // Touch 
            sfEvent.m_touch.finger     = event->touch.finger;
            sfEvent.m_touch.x          = event->touch.x;
            sfEvent.m_touch.y          = event->touch.y;
            break;
        }
        case sf::Event::TouchEnded:{
            sfEvent.m_type = Type_TouchEnded;
            // Touch 
            sfEvent.m_touch.finger     = event->touch.finger;
            sfEvent.m_touch.x          = event->touch.x;
            sfEvent.m_touch.y          = event->touch.y;
            break;
        }
        case sf::Event::SensorChanged:{
            sfEvent.m_type = Type_SensorChanged;
            // Sensor
            sfEvent.m_sensor.type  = (SensorType)event->sensor.type;
            sfEvent.m_sensor.x     = event->sensor.x;
            sfEvent.m_sensor.y     = event->sensor.y;
            sfEvent.m_sensor.z     = event->sensor.z;
            break;
        }
        default:{
            break;
        }
    }

    const TEvent* pointer = &sfEvent;

    return OnEvent(*pointer);
}


bool IODriver::OnEvent(const TEvent& event){
    if (event.m_type == Type_Closed) m_close = true;

    if(event.m_type == Type_KeyPressed){
        if (event.m_key.code == Key_Escape){
            m_close = true;
        }
    }

    return m_close;
}

KeyboardKey IODriver::ConvertKeyGLFW(int key){

    KeyboardKey newKey;

    switch(key){
        case  -1: newKey = Key_Unknown;         break;
        case  32: newKey = Key_Space;           break;       
        case  39: newKey = Key_Apostrophe;      break;   
        case  44: newKey = Key_Comma;           break;
        case  45: newKey = Key_MINUS;           break;
        case  46: newKey = Key_PERIOD;          break;
        case  47: newKey = Key_SLASH;           break;
        case  48: newKey = Key_0;               break;
        case  49: newKey = Key_1;               break;
        case  50: newKey = Key_2;               break;
        case  51: newKey = Key_3;               break;
        case  52: newKey = Key_4;               break;
        case  53: newKey = Key_5;               break;
        case  54: newKey = Key_6;               break;
        case  55: newKey = Key_7;               break;
        case  56: newKey = Key_8;               break;
        case  57: newKey = Key_9;               break;
        case  59: newKey = Key_SEMICOLON;       break;
        case  61: newKey = Key_EQUAL;           break;
        case  65: newKey = Key_A;               break;
        case  66: newKey = Key_B;               break;
        case  67: newKey = Key_C;               break;
        case  68: newKey = Key_D;               break;
        case  69: newKey = Key_E;               break;
        case  70: newKey = Key_F;               break;
        case  71: newKey = Key_G;               break;
        case  72: newKey = Key_H;               break;
        case  73: newKey = Key_I;               break;
        case  74: newKey = Key_J;               break;
        case  75: newKey = Key_K;               break;
        case  76: newKey = Key_L;               break;
        case  77: newKey = Key_M;               break;          
        case  78: newKey = Key_N;               break;          
        case  79: newKey = Key_O;               break;          
        case  80: newKey = Key_P;               break;          
        case  81: newKey = Key_Q;               break;          
        case  82: newKey = Key_R;               break;          
        case  83: newKey = Key_S;               break;          
        case  84:  newKey = Key_T;              break;
        case  85:  newKey = Key_U;              break;
        case  86:  newKey = Key_V;              break;
        case  87:  newKey = Key_W;              break;
        case  88:  newKey = Key_X;              break;
        case  89:  newKey = Key_Y;              break;
        case  90:  newKey = Key_Z;              break;
        case  91:  newKey = Key_LEFT_BRACKET;   break;
        case  92:  newKey = Key_BACKSLASH;      break;
        case  93:  newKey = Key_RIGHT_BRACKET;  break;
        case  96:  newKey = Key_GRAVE_ACCENT;   break;
        case 161:  newKey = Key_WORLD_1;        break;
        case 162:  newKey = Key_WORLD_2;        break;
        case 256:  newKey = Key_Escape;         break;
        case 257:  newKey = Key_ENTER;          break;
        case 258:  newKey = Key_TAB;            break;
        case 259:  newKey = Key_BACKSPACE;      break;
        case 260:  newKey = Key_INSERT;         break;
        case 261:  newKey = Key_DELETE;         break;
        case 262:  newKey = Key_Right;          break;
        case 263:  newKey = Key_Left;           break;
        case 264:  newKey = Key_Down;           break;
        case 265:  newKey = Key_Up;             break;
        case 266:  newKey = Key_PAGE_UP;        break;
        case 267:  newKey = Key_PAGE_DOWN;      break;
        case 268:  newKey = Key_HOME;           break;
        case 269:  newKey = Key_END;            break;
        case 280:  newKey = Key_CAPS_LOCK;      break;
        case 281:  newKey = Key_SCROLL_LOCK;    break;
        case 282:  newKey = Key_NUM_LOCK;       break;
        case 283:  newKey = Key_PRINT_SCREEN;   break;
        case 284:  newKey = Key_PAUSE;          break;
        case 290:  newKey = Key_F1;             break;
        case 291:  newKey = Key_F2;             break;
        case 292:  newKey = Key_F3;             break;
        case 293:  newKey = Key_F4;             break;
        case 294:  newKey = Key_F5;             break;
        case 295:  newKey = Key_F6;             break;
        case 296:  newKey = Key_F7;             break;
        case 297:  newKey = Key_F8;             break;
        case 298:  newKey = Key_F9;             break;
        case 299:  newKey = Key_F10;            break;
        case 300:  newKey = Key_F11;            break;
        case 301:  newKey = Key_F12;            break;
        case 302:  newKey = Key_F13;            break;
        case 303:  newKey = Key_F14;            break;
        case 304:  newKey = Key_F15;            break;
        case 305:  newKey = Key_F16;            break;
        case 306:  newKey = Key_F17;            break;
        case 307:  newKey = Key_F18;            break;
        case 308:  newKey = Key_F19;            break;
        case 309:  newKey = Key_F20;            break;
        case 310:  newKey = Key_F21;            break;
        case 311:  newKey = Key_F22;            break;
        case 312:  newKey = Key_F23;            break;
        case 313:  newKey = Key_F24;            break;
        case 314:  newKey = Key_F25;            break;
        case 320:  newKey = Key_KP_0;           break;
        case 321:  newKey = Key_KP_1;           break;
        case 322:  newKey = Key_KP_2;           break;
        case 323:  newKey = Key_KP_3;           break;
        case 324:  newKey = Key_KP_4;           break;
        case 325:  newKey = Key_KP_5;           break;
        case 326:  newKey = Key_KP_6;           break;
        case 327:  newKey = Key_KP_7;           break;
        case 328:  newKey = Key_KP_8;           break;
        case 329:  newKey = Key_KP_9;           break;
        case 330:  newKey = Key_KP_DECIMAL;     break;
        case 331:  newKey = Key_KP_DIVIDE;      break;
        case 332:  newKey = Key_KP_MULTIPLY;    break;
        case 333:  newKey = Key_KP_SUBTRACT;    break;
        case 334:  newKey = Key_KP_ADD;         break;
        case 335:  newKey = Key_KP_ENTER;       break;
        case 336:  newKey = Key_KP_EQUAL;       break;
        case 340:  newKey = Key_LEFT_SHIFT;     break;
        case 341:  newKey = Key_LEFT_CONTROL;   break;
        case 342:  newKey = Key_LEFT_ALT;       break;
        case 343:  newKey = Key_LEFT_SUPER;     break;
        case 344:  newKey = Key_RIGHT_SHIFT;    break;
        case 345:  newKey = Key_RIGHT_CONTROL;  break;
        case 346:  newKey = Key_RIGHT_ALT;      break;
        case 347:  newKey = Key_RIGHT_SUPER;    break;
        case 348:  newKey = Key_MENU;           break;
        case   0:  newKey = Key_MouseLeft;      break;
        case   1:  newKey = Key_MouseRight;     break;
        case   2:  newKey = Key_MouseMiddle;    break;
        case   3:  newKey = Key_MouseXButton1;  break;
        case   4:  newKey = Key_MouseXButton2;  break;
        case   5:  newKey = Key_MouseXButton3;  break;
        case   6:  newKey = Key_MouseXButton4;  break;
        case   7:  newKey = Key_MouseXButton5;  break;
        default:   newKey = Key_Unknown;
    }
    return newKey;
}