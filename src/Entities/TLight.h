#ifndef TLIGHT_H
#define TLIGHT_H

#include "./TEntity.h"
#include <TColor.h>

class TLight: public TEntity{
public:
	TLight(TColor intensity = TColor());
	~TLight();

	void 	SetIntensity(TColor intensity);	// Guarda el color que se le pasa por parametros
	TColor 	GetIntensity();					// Devuelve la intentsidad de la luz

	void 	BeginDraw();					// Empezar a pintar la luz
	void 	EndDraw();						// Acabar de pintar la luz

private:
	TColor m_intensity;
	
};

#endif