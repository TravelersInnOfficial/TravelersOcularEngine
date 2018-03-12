#include "./ParticleManager.h"

ParticleManager::ParticleManager(){}

ParticleManager::~ParticleManager(){}

void ParticleManager::InitParticle(Particle& p){
	// Valores por defecto
	p.translation = glm::vec3(0,0,0);

	float X = (rand() % 10)/10.0f - 0.5f;
	float Y = (rand() % 10)/10.0f - 0.5f;
	float Z = (rand() % 10)/10.0f - 0.5f;

	p.pos 	= glm::vec3(X, Y, Z);

	X = (rand() % 4)/10.0f - 0.2f;
	Y = (rand() % 4)/10.0f - 0.2f;
	Z = (rand() % 4)/10.0f - 0.2f;

	p.speed = glm::vec3(X,Y,Z);

	p.r = (unsigned char)(rand() % 255);
	p.g = (unsigned char)(rand() % 255);
	p.b = (unsigned char)(rand() % 255);

	//size = (rand() % 5)/20.0f;
	p.size = (rand() % 5)/75.0f;
	p.rotation = (rand() % 360);
	p.life = 20.0f;
}

void ParticleManager::UpdateParticle(Particle& p, float deltaTime){
	// Simulate simple physics : gravity only, no collisions
	//p.speed += glm::vec3(0.0f,-0.01f, 0.0f) * deltaTime * 0.5f;
	p.speed += glm::vec3(0.0f,0.5f, 0.0f) * deltaTime * 0.5f;
	p.pos += p.speed * deltaTime;
}
