#include "IODriver.h"
#include "VideoDriver.h"

TEvent::TEvent(){}

TEvent::~TEvent(){}

IODriver::IODriver(){
    m_close = false;
}

IODriver::~IODriver(){}

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
            sfEvent.m_mouseButton.button   = (ButtonMouse)event->mouseButton.button;
            sfEvent.m_mouseButton.x        = event->mouseButton.x;
            sfEvent.m_mouseButton.y        = event->mouseButton.y;
            break;
        }
        case sf::Event::MouseButtonReleased:{
            sfEvent.m_type = Type_MouseButtonReleased;
            // Mouse Button
            sfEvent.m_mouseButton.button   = (ButtonMouse)event->mouseButton.button;
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
        }
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
        if (event.m_key.code == Key_Left){
            //addVertices(-2, 0);
            VideoDriver::xdist -= 0.5f;
            std::cout << "VideoDriver::Xdist: " << VideoDriver::xdist << "\n";
        }
        if (event.m_key.code == Key_Right){
            //addVertices(2, 0);
            VideoDriver::xdist += 0.5f;
            std::cout << "VideoDriver::Xdist: " << VideoDriver::xdist << "\n";
        }
        if (event.m_key.code == Key_Down){
            //addVertices(0, -2);
            VideoDriver::zdist -= 0.5f;
            std::cout<<"VideoDriver::zdist: " << VideoDriver::zdist << "\n";
        }
        if (event.m_key.code == Key_Up){
            //addVertices(0, 2);                
            VideoDriver::zdist += 0.5f;
            std::cout<<"VideoDriver::zdist: " << VideoDriver::zdist << "\n";
        }
    }

    if (event.m_type == Type_KeyReleased){ 
        if(event.m_key.code == Key_Space){
        } 
    }
    return m_close;
}