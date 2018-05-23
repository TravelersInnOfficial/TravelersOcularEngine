#ifndef TLIGHT_H
#define TLIGHT_H

#include "./TEntity.h"
#include <TColor.h>
#include <TOEvector3d.h>

class TLight: public TEntity{
public:
	/**
	 * @brief	- Constructor de la luz
	 * 
	 * @param 	- color - Parametros de color de la luz
	 * @param 	- attenuation - Valor de atenuacion de la luz
	 */
	TLight(TColor color = TColor(), float attenuation = 0.0f);

	/**
	 * @brief	- Destructor de la luz, al no tener variables que haya que hacer delete el metodo esta vacio
	 */
	~TLight();

	/**
	 * @brief	- Guardamos el color pasado por parametros 
	 * 
	 * @param 	- color - Nuevo color de la luz	 
	 */
	void 	SetColor(TColor color);		

	/**
	 * @brief	- Devolvemos la variable color de la luz 
	 * 
	 * @return 	- TColor - Color de la luz
	 */
	TColor 	GetColor();					

	/**
	 * @brief	- Cambiamos la atenuacion de la luz 
	 * 
	 * @param 	- attenuation - nueva atenuacion de la luz 
	 */
	void 	SetAttenuation(float attenuation);	
	
	/**
	 * @brief	- Devolvemos la atenuacion de la luz 
	 * 
	 * @return - float - Atenuacion de la luz
	 */
	float 	GetAttenuation();					

	/**
	 * @brief	- Activamos o desactivamos la luz 
	 * 
	 * @param 	- active - Activar o desactivar la luz 
	 */
	void	SetActive(bool active);

	/**
	 * @brief	- Devuelve el booleano de activacion de la luz 
	 * 
	 * @return 	- bool - True: la luz esta activada
	 * @return 	- bool - False: la luz esta desactivada
	 */
	bool	GetActive();

	/**
	 * @brief	- Cambiamos o quitamos el tipo de luz a direccional 
	 * 
	 * @param 	- directional - Cambia el tipo de luz a direccional o la quita
	 */
	void	SetDirectional(bool directional);

	/**
	 * @brief	- Devuelve si el tipo de luz es direccional o no 
	 * 
	 * @return 	- bool - True: la luz es direccional
	 * @return 	- bool - False: la luz no es direccional
	 */
	bool	GetDirectional();

	/**
	 * @brief	- Cambia la direccion a la que esta apunando la luz 
	 * 
	 * @param 	- direction - Nueva direccion a la que apunta la luz 
	 */
	void	SetDirection( TOEvector3df direction);

	/**
	 * @brief	- Devuelve la direccion de la luz
	 * 
	 * @return 	- TOEvector3df - Direccion de la luz
	 */
	TOEvector3df GetDirection();

	/**
	 * @brief	- En el caso de estar activado dibuja el bounding box de la luz 
	 */
	virtual void BeginDraw() override;

	/**
	 * @brief 	- Acaba de pintar la luz 
	 */
	virtual void EndDraw() override;

	/**
	 * @brief	- Cambia la variable de pintar sombras de la luz 
	 */
	virtual void DrawShadow() override;
	
	/**
	 * @brief	- Pinta el bounding box que forma la luz 
	 */
	void 	DrawBB();

	bool 	drawBB;		// drawBB - variable para saber si hay que pintar el bounding box o no

	/**
	 * @brief 	- Cambia la variable de si la luz emite sombras
	 * 
	 * @param 	- shadowState - Nueva valor de la variable m_shadowState
	 */
	void SetShadowsState(bool shadowState);

	/**
	 * @brief	- Devuelve un booleano diciendo si la luz emite sombras o no 
	 * 
	 * @return	- Bool - True: La luz emite sombras
	 * @return 	- Bool - False: La luz no emite sombras
	 */
	bool GetShadowsState();

private:
	TColor m_color;				// m_color - Color de la luz
	float m_attenuation;		// m_attenuation - Atenuacion de la luz
	bool m_active;				// m_active - Si la luz esta activa o no
	bool m_directional;			// m_directional - Si la luz es direccional o no
	TOEvector3df m_direction;	// m_direction - Direccion de la luz
	bool m_shadowState;			// m_shadowState - Si la luz emite sombras o no
	bool m_drawingShadows;		// m_drawingShadows - Si se han pintado las sombras o no
	
};

#endif