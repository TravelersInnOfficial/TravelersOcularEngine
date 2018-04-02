#ifndef TDOME_H
#define TDOME_H

#include "TMesh.h"

class TDome: public TMesh{
public:
	TDome(std::string texturePath = "");
	~TDome();

	void BeginDraw() override;
	void EndDraw() override;
	// Declare as empty method overriding mesh one for not drawing dome shadows
	void DrawShadow() override;

private:
	void SendShaderData();

};

#endif