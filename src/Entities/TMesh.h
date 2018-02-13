#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"

class TMesh: public TEntity{
public:
	TMesh();
	~TMesh();

	//void LoadMesh(TFichero);

	void BeginDraw();
	void EndDraw();
private:
	float vertices[];
	//TRecuersoMalla* m_malla
};

#endif