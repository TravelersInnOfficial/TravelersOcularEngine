#include "./ParticleManager.h"

ParticleManager::ParticleManager(){}

ParticleManager::~ParticleManager(){}

void ParticleManager::InitParticle(Particle& p){
	p.translation = TOEvector3df(0,0,0);

	// INITIAL POSITION
	int maxPosOffset = 10;
	float X = (rand() % maxPosOffset)/10.0f - maxPosOffset/20.0f;
	float Y = (rand() % maxPosOffset)/10.0f - maxPosOffset/20.0f;
	float Z = (rand() % maxPosOffset)/10.0f - maxPosOffset/20.0f;
	p.pos = TOEvector3df(X, Y, Z);

	// VELOCITY
	int maxVel = 10;
	X = (rand() % maxVel)/10.0f - maxVel/20.0f;
	Y = (rand() % maxVel)/10.0f - maxVel/20.0f;
	Z = (rand() % maxVel)/10.0f - maxVel/20.0f;
	p.speed = TOEvector3df(X,Y,Z);

	// COLOR
	p.r = (unsigned char)(rand() % 255);
	p.g = (unsigned char)(rand() % 255);
	p.b = (unsigned char)(rand() % 255);

	// SIZE
	int maxSize = 15;
	p.size = (rand() % maxSize)/10.0f;

	// ROTATION & LIFE
	p.rotation = (rand() % 360);
	p.life = 20.0f;
}

void ParticleManager::UpdateParticle(Particle& p, float deltaTime){
	p.pos.X += p.speed.X * deltaTime;
	p.pos.Y += p.speed.Y * deltaTime;
	p.pos.Z += p.speed.Z * deltaTime;
}
