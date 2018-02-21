#ifndef TFLIGHT_H
#define TFLIGHT_H

#include <vector4d.h>
#include "TFNode.h"

class TFLight: public TFNode{
public:
	TFLight(
		vector3df position = vector3df(0, 0, 0),
		vector3df rotation = vector3df(0, 0, 0),
		vector4df color,
		float intensity
	);
	~TFLight();

	void SetColor(vector4df color);				// Changes the light color
	void SetIntensity(float intensity);			// Changes the light intensity

private:

};

#endif