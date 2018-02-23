#ifndef TFLIGHT_H
#define TFLIGHT_H

#include <vector4d.h>
#include "TFNode.h"

class TFLight: public TFNode{
	friend class SceneManager;

public:
	void SetColor(vector4df color);				// Changes the light color
	void SetIntensity(float intensity);			// Changes the light intensity
	void SetActive(bool active);				// Changes the light active state

	vector4df GetColor();	// Returns the light color
	float GetIntensity();	// Returns the light intensity
	bool GetActive();		// Returns the light active state

private:
	TFLight(
		vector3df position = vector3df(0, 0, 0),
		vector3df rotation = vector3df(0, 0, 0),
		vector4df color = vector4df(255.0f, 255.0f, 255.0f, 255.0f),
		float intensity = 1.0f
	);
	~TFLight();
	void CreateEstructure();

};

#endif