#ifndef TDOME_H
#define TDOME_H

#include "TMesh.h"

class TDome: public TMesh{
public:
	TDome(std::string meshPath = "", std::string texturePath = "");
	~TDome();

	void BeginDraw();
	void EndDraw();

private:
	void SendShaderData();

};

#endif