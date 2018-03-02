#ifndef IODRIVER_H
#define IODRIVER_H
#include <SFML/Graphics.hpp>
#include <EventEnum.h>

class TEvent{
public:
	TEvent();
	~TEvent();


	struct SizeEvent{
        unsigned int 	width;  
        unsigned int 	height; 
    };

    struct TextEvent{
        unsigned int 	unicode; 
    };

    struct KeyEvent{
        KeyboardKey 	code;    
        bool         	alt;     
        bool          	control; 
        bool          	shift;   
        bool          	system;  
    };

    struct MouseWheelEvent{
        int 			delta; 
        int 			x;     
        int 			y;     
    };

    struct MouseButtonEvent{
        KeyboardKey 	button; 
        int           	x;      
        int           	y;      
    };

    struct MouseMoveEvent{
        int x; 
        int y; 
    };

    struct JoystickButtonEvent{
        unsigned int joystickId; 
        unsigned int button;     
    };

    struct JoystickMoveEvent{
        unsigned int   		joystickId; 
        JoystickAxis	 	axis;       
        float          		position;   
    };

    struct JoystickConnectEvent{
        unsigned int joystickId; 
    };

    struct TouchEvent{
        unsigned int finger; 
        int x;               
        int y;               
    };

    struct SensorEvent{
        SensorType 	type; 
        float 		x;           
        float 		y;           
        float 		z;           
    };

	// Union: Todos los datos comparten el mismo espacio, haciendo que ahorre espacio
	// Como esta pensado para que solo gaste un tipo de dato no deberia haber problema
	union{
		SizeEvent				m_size;
		TextEvent				m_text;
		KeyEvent				m_key;
		MouseWheelEvent 		m_mouseWheel;
		MouseButtonEvent 		m_mouseButton;
		MouseMoveEvent			m_mouseMove;
		JoystickButtonEvent		m_joystickButton;
		JoystickMoveEvent		m_joystickMove;
		JoystickConnectEvent 	m_joystickConnect; 
		TouchEvent				m_touch;
		SensorEvent				m_sensor;
	};

	EventType m_type;
	
};

class IODriver{
public:
    IODriver();
    virtual ~IODriver();
    bool Update(sf::Event* event);
protected:
	virtual bool OnEvent(const TEvent& event);
    bool m_close;
};

#endif