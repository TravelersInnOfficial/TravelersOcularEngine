#ifndef TFPARTICLESYSTEM_H
#define TFPARTICLESYSTEM_H

#include "TFNode.h"
#include "./../../Common/ParticleManager.h"

class TFParticleSystem: public TFNode{
	friend class SceneManager;
public:
	void SetTranslate(toe::core::TOEvector3df translation) override;
	void Translate(toe::core::TOEvector3df translation) override;

	void SetTexture(std::string path);
	void SetManager(ParticleManager* manager);
	void Update(float deltaTime);
private:
	TFParticleSystem(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1)
	);
	~TFParticleSystem();
};

#endif