#ifndef TCAMERA_H
#define TCAMERA_H

#include "TEntity.h"

class TCamera: public TEntity{
public:
	TCamera();
	~TCamera();

	// void setPerspectiva(float, float, ...);
	// void setParalela(float, float, ...);

	void BeginDraw();
	void EndDraw();
private:
	// bool m_esPerspectiva
	// float m_cercano, m_lejano
};

#endif