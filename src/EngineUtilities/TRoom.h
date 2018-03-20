#ifndef TROOM_H
#define TROOM_H

#include "./TNode.h"
#include "./TPortal.h"

#include <map>

class TRoom: public TNode{
public:
	TRoom();
	~TRoom();

	void AddPortal(TRoom* connection);
	void Draw();	// Pinta sus nodos y luego mira si tiene que pintar alguna habitacion por alguno de sus portales

private:
	std::vector<TPortal*> portals;
	// MAPA QUE CONECTA PORTALES CON HABITACIONSES

};

#endif