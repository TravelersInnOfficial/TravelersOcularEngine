#ifndef TFPARTICLESYSTEM_H
#define TFPARTICLESYSTEM_H

#include "./../TFNode.h"
#include "ParticleManager.h"

class TFParticleSystem: public TFNode{
	friend class SceneManager;
public:
	void Translate(toe::core::TOEvector3df translation) override;
	void SetTranslateSmooth(toe::core::TOEvector3df translation);

	void SetTexture(std::string path);
	void SetManager(ParticleManager* manager);
	void Update(float deltaTime);

	void SetNewPerSecond(int newPerSecond);
	int GetNewPerSecond();

private:
	TFParticleSystem(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1)
	);
	~TFParticleSystem();
};

#endif