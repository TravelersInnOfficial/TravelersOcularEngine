#ifndef TLIGHT_H
#define TLIGHT_H

#include "./TEntity.h"
#include <TColor.h>

class TLight: public TEntity{
public:
	TLight(TColor color = TColor(), float intensity = 1.0f);
	~TLight();

	void 	SetColor(TColor color);		// Guarda el color que se le pasa por parametros
	TColor 	GetColor();						// Devuelve la intentsidad de la luz

	void 	SetIntensity(float intensity);	// Guarda el color que se le pasa por parametros
	float 	GetIntensity();					// Devuelve la intentsidad de la luz

	void 	BeginDraw();					// Empezar a pintar la luz
	void 	EndDraw();						// Acabar de pintar la luz

private:
	TColor m_color;
	float m_intensity;
	
};

#endif