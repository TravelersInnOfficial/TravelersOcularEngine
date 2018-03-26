#ifndef TDOME_H
#define TDOME_H

#include "TMesh.h"

class TDome: public TMesh{
public:
	TDome(std::string texturePath = "");
	~TDome();

	void BeginDraw() override;
	void DrawShadow() override;
	void EndDraw() override;

private:
	void SendShaderData();

};

#endif