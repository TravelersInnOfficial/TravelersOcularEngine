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
	std::string checkModel(std::string path);
	std::string checkText(std::string path);

};

#endif