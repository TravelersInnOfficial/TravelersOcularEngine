#ifndef IODRIVER_H
#define IODRIVER_H
#include <EventEnum.h>


/**
 * @brief   - Clase en la que almacenan todos los tipos de eventos que trata el motor 
 */
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

    /**
     * @brief   - Enviamos el evento de tecla de keyboard pulsada
     * 
     * @param   - key - Valor de la tecla 
     * @param   - action - Accion que se ha llevado a cabo
     */
    bool UpdateKeyboard(int key, int action);

    /**
     * @brief   - Evento de movimento del raton 
     * 
     * @param   - xpos - Posicion en X del raton 
     * @param   - ypos - Posicion en Y del raton
     */
    bool UpdateMousePosition(int xpos, int ypos);

    /**
     * @brief   - Evento de tecla de raton pulsado 
     * 
     * @param   - button - Boton del evento 
     * @param   - action - Accion que se ha llevado a cabo
     */
    bool UpdateMouseButtons(int button, int action);

    /**
     * @brief   - Evento de girar la rueda del raton 
     * 
     * @param   - xoffset - Cambio en X 
     * @param   - yoffset - Cambio en Y
     */
    bool UpdateMouseWheel(int xoffset, int yoffset);

    /**
     * @brief   - Evento de cerrar la ventana 
     */
    bool UpdateShouldClose();
protected:
    /**
     * @brief   - Convierte las teclas glfw a nuestro propio numerador 
     * 
     * @param   - key - Valor de glfw 
     */
    KeyboardKey ConvertKeyGLFW(int key);

    /**
     * @brief   - Metodo que lee los eventos recibidos de glfw 
     * 
     * @param   - event - Evento recibido 
     */
	virtual bool OnEvent(const TEvent& event);
};

#endif