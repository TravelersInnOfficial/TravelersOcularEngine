#ifndef TFPARTICLESYSTEM_H
#define TFPARTICLESYSTEM_H

#include "./../TFNode.h"
#include "ParticleManager.h"

class TFParticleSystem: public TFNode{
	friend class SceneManager;
public:
	void Translate(TOEvector3df translation) override;
	void SetTranslateSmooth(TOEvector3df translation);

	void SetTexture(std::string path);
	void SetManager(ParticleManager* manager);
	void Update(float deltaTime);

	void SetNewPerSecond(int newPerSecond);
	int GetNewPerSecond();

private:
	TFParticleSystem(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1)
	);
	~TFParticleSystem();
};

#endif