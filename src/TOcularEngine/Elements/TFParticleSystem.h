#ifndef TFPARTICLESYSTEM_H
#define TFPARTICLESYSTEM_H

#include "TFNode.h"

class TFParticleSystem: public TFNode{
	friend class SceneManager;
public:
	TFParticleSystem(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1)
	);
	~TFParticleSystem();

	void Update(float deltaTime);
private:
};

#endif