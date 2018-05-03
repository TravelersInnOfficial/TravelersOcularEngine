#ifndef TLIGHT_H
#define TLIGHT_H

#include "./TEntity.h"
#include <TColor.h>
#include <TOEvector3d.h>

class TLight: public TEntity{
public:
	TLight(TColor color = TColor(), float attenuation = 0.0f);
	~TLight();

	void 	SetColor(TColor color);		// Guarda el color que se le pasa por parametros
	TColor 	GetColor();					// Devuelve la intentsidad de la luz

	void 	SetAttenuation(float attenuation);	// Guarda el color que se le pasa por parametros
	float 	GetAttenuation();					// Devuelve la intentsidad de la luz

	void	SetActive(bool active);
	bool	GetActive();

	void	SetDirectional(bool directional);
	bool	GetDirectional();

	void	SetDirection( TOEvector3df direction);
	TOEvector3df GetDirection();

	void 	BeginDraw();				// Empezar a pintar la luz
	void 	EndDraw();					// Acabar de pintar la luz
	
	void 	DrawBB();
	bool 	drawBB;

	void SetShadowsState(bool shadowState);
	bool GetShadowsState();

private:
	TColor m_color;
	float m_attenuation;
	bool m_active;
	bool m_directional;
	TOEvector3df m_direction;
	bool m_shadowState;
	
};

#endif