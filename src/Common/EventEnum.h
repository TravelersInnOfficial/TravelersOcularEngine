#ifndef EVENT_ENUM_H
#define EVENT_ENUM_H

/**
 * @brief All event types availeables in TOE.
 * 
 */

enum EventType{
	Type_Unknow					= -1,
	Type_Closed 				=  0,
	Type_Resized				=  1,
	Type_LostFocus				=  2,
	Type_GainedFocus			=  3,
	Type_TextEntered			=  4,
	Type_KeyPressed				=  5,
	Type_KeyReleased			=  6,
	Type_MouseWheelScrolled		=  7,
	Type_MouseButtonPressed		=  8,
	Type_MouseButtonReleased	=  9,
	Type_MouseMoved 			= 10,
	Type_MouseEntered			= 11,
	Type_MouseLeft				= 12,
	Type_JoystickButtonPressed	= 13,
	Type_JoystickButtonReleased	= 14,
	Type_JoystickMoved			= 15,
	Type_JoystickConnected		= 16,
	Type_JoystickDisconnected	= 17,
	Type_TouchBegan      	    = 18,
	Type_TouchMoved				= 19,             
	Type_TouchEnded             = 20,
	Type_SensorChanged          = 21
};

/*
 * 	Toda las teclas que el motor puede identificar como input
 */

enum KeyboardKey{
	Key_Unknown   			= -1, 
	Key_Space   			= 0, 
	Key_Apostrophe   		= 1, 
	Key_Comma, 
	Key_MINUS,
	Key_PERIOD,
	Key_SLASH,
	Key_0,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,
	Key_SEMICOLON,
	Key_EQUAL,
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_LEFT_BRACKET,
	Key_BACKSLASH,
	Key_RIGHT_BRACKET,
	Key_GRAVE_ACCENT,
	Key_WORLD_1,
	Key_WORLD_2,
	Key_Escape,
	Key_ENTER,
	Key_TAB,
	Key_BACKSPACE,
	Key_INSERT,
	Key_DELETE,
	Key_Right,
	Key_Left,
	Key_Down,
	Key_Up,
	Key_PAGE_UP,
	Key_PAGE_DOWN,
	Key_HOME,
	Key_END,
	Key_CAPS_LOCK,
	Key_SCROLL_LOCK,
	Key_NUM_LOCK,
	Key_PRINT_SCREEN,
	Key_PAUSE,
	Key_F1,
	Key_F2,
	Key_F3,
	Key_F4,
	Key_F5,
	Key_F6,
	Key_F7,
	Key_F8,
	Key_F9,
	Key_F10,
	Key_F11,
	Key_F12,
	Key_F13,
	Key_F14,
	Key_F15,
	Key_F16,
	Key_F17,
	Key_F18,
	Key_F19,
	Key_F20,
	Key_F21,
	Key_F22,
	Key_F23,
	Key_F24,
	Key_F25,
	Key_KP_0,
	Key_KP_1,
	Key_KP_2,
	Key_KP_3,
	Key_KP_4,
	Key_KP_5,
	Key_KP_6,
	Key_KP_7,
	Key_KP_8,
	Key_KP_9,
	Key_KP_DECIMAL,
	Key_KP_DIVIDE,
	Key_KP_MULTIPLY,
	Key_KP_SUBTRACT,
	Key_KP_ADD,
	Key_KP_ENTER,
	Key_KP_EQUAL,
	Key_LEFT_SHIFT,
	Key_LEFT_CONTROL,
	Key_LEFT_ALT,
	Key_LEFT_SUPER,
	Key_RIGHT_SHIFT,
	Key_RIGHT_CONTROL,
	Key_RIGHT_ALT,
	Key_RIGHT_SUPER,
	Key_MENU,
	Key_LAST,

	Key_MouseLeft,
	Key_MouseRight,
	Key_MouseMiddle,
	Key_MouseMiddle_Up,
	Key_MouseMiddle_Down,
	Key_MouseXButton1,
	Key_MouseXButton2,
	Key_MouseXButton3,
	Key_MouseXButton4,
	Key_MouseXButton5,

	Key_KeyCount,
};

/*
 *	Los eventos del motor que identifica el motor
 */

enum ButtonMouse{
	ButtonMouse_Unknown 	= -1,
	ButtonMouse_Left 		=  0,       
	ButtonMouse_Right 		=  1,      
	ButtonMouse_Middle 		=  2,     
	ButtonMouse_XButton1 	=  3,   
	ButtonMouse_XButton2	=  4,   
	ButtonMouse_ButtonCount	=  5 
};

/*
 *	Eventos de Joystick que reconoce el motor
 */

enum JoystickAxis{
	X 		= 0,    
	Y 		= 1,    
	Z 		= 2,    
	R 		= 3,    
	U 		= 4,    
	V 		= 5,    
	PovX	= 6, 
	PovY	= 7  
};

/*
 *	Sensores que recononce el motor
 *	Estos sensores son de la version con SFML, con glfw no los leemos
 *	aunque dejamos los enumeradores preparados por si lo incorporamos
 */

enum SensorType{
	Accelerometer 		= 0,    
	Gyroscope 			= 1,        
	Magnetometer    	= 2,     
	Gravity 			= 3,          
	UserAcceleration	= 4, 
	Orientation			= 5,      
	Count             	= 6
};

#endif