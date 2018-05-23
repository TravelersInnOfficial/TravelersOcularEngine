#ifndef TPARTICLESYSTEM_H
#define TPARTICLESYSTEM_H

/**
 * @brief ParticleSystem Entity that will emit particles and manage them.
 * 
 * @file TParticleSystem.h
 */

#include <glm/vec3.hpp>
#include "./TEntity.h"
#include "./../Resources/TResourceTexture.h"
#include "./../TOcularEngine/Elements/Particles/ParticleManager.h"

class TParticleSystem: public TEntity{
public:
	/**
	 * @brief	- Constructor del sistema de particulas
	 * 				en este se inicializan y rellenan los buffers
	 */
	TParticleSystem(std::string path = "");
	
	/**
	 * @brief	- Destructor del sistema de particulas donde eliminamos el manager
	 * 				ademas de vaciar los buffers 
	 */
	~TParticleSystem();

	/**
	 * @brief	- Empezamos a pintar las particulas 
	 */
	virtual void BeginDraw() override;

	/**
	 * @brief	- Acabamos de pintar las particulas reseteando las variables 
	 */
	virtual void EndDraw() override;

	/**
	 * @brief	- Como no queremos que se pinten las sombras de las particulas este metodo solamente
	 * 				cambia el booleano de pintar sombras 
	 */
	virtual void DrawShadow() override;

	/**
	 * @brief	- Update de las particulas en las que se actualizan sus valores segun el manager que tenga
	 * 
	 * @param 	- deltaTime - DeltaTime para poder actualizar sus valores en funcion del tiempo de ejecucion 
	 */
	void Update(float deltaTime);

	/**
	 * @brief	- Cargamos la textura que pintan las particulas 
	 * 
	 * @param 	- path - Ruta de la textura a utilizar
	 */
	void SetTexture(std::string path);

	/**
	 * @brief	- Cambiamos el manager de particulas que se va a utilizar 
	 * 
	 * @param 	- manager - Puntero al nuevo manager 
	 */
	void SetManager(ParticleManager* manager);

	/**
	 * @brief	- Cambiamos la posicion del centro de las particulas sin que estas se teletransporten 
	 * 
	 * @param  	- position - Posicion a la que lo transladamos
	 */
	void SetTranslate(glm::vec3 position);

	/**
	 * @brief	- Transladamos el centro del sistema de particulas sin que estas se teletransporten 
	 * 
	 * @param 	- position - Translacion a hacer 
	 */
	void Translate(glm::vec3 position);
	
	/**
	 * @brief	- Cambiamos el numero de particulas que se generan por segundo
	 * 
	 * @param 	- newPerSecond - numero de particular a generar
	 */
	void SetNewPerSecond(int newPerSecond);
	
	/**
	 * @brief 	- Devuelve el numero de particulas que se generan por segundo
	 * 
	 * @return 	- int - numero de particulas que se generan por segundo
	 */
	int GetNewPerSecond();

private:
	/**
	 * @brief	- Enviamos la informacion al shader 
	 */
	void SendShaderData();

	/**
	 * @brief	- Reseteamos la informacion que hemos alterado de los shaders
	 */
	void ResetShaderData();

	/**
	 * @brief 	- Buscamos en el array de particulas una que no se este usando
	 * 
	 * @return 	- int - posicion en el array de la particula
	 */
	int FindUnusedParticle();

	/**
	 * @brief 	- Anyadimos una nueva particula
	 * 
	 * @param 	- deltaTime - valor del deltaTime
	 */
	void AddNewParticles(float deltaTime);

	ParticleManager*	m_manager;					// m_manager - Manager de las particulas que se encarga de updatearlas y inicializarlas
	TResourceTexture*	m_texture;					// m_texture - Textura que utilizan las particulas

	int 				m_particleCount;			// m_particleCount - Numero de particulas activas en el momento
	static const int 	m_maxParticles = 10000;		// m_maxParticles - Numero maximo de particulas
	int					m_newParticlesPerSecond;	// m_newParticlesPerSecond - Numero de particulas que se crean cada segundo
	float				m_particleAcumulation;		// m_particleAcumulation - Numero de particulas a crear desde el ultimo frame
	
	GLuint 				m_vbo;	// m_vbo - Vertex buffer del mesh basico
	GLuint				m_pbo; 	// m_pbo - Buffer con las posiciones de las particulas
	GLuint				m_ebo;	// m_ebo - Buffer con los extras de las particulas
	GLuint				m_cbo;	// m_cbo - Buffer con los colores de las particular

	int 				m_lastUsedParticle; 	// m_lastUsedParticle - Numero de la ultima particula que se actualizo

	Particle 			m_particleContainer		[m_maxParticles*1];		// m_particleContainer - Array con todas las particulas
	unsigned char 		m_particlesColorData	[m_maxParticles*3];		// m_particlesColorData - Array con todos los colores de las particulas
	float				m_particlePositionData	[m_maxParticles*3];		// m_particlePositionData - Array con las posiciones de las particulas
	float 				m_particlesExtra		[m_maxParticles*2];		// m_particlesExtra - Array con el tamanyo y la rotacion de las particulas

	bool 				m_drawingShadows;		// m_drawingShadows - Variable para saber si pintar las sombras
};

#endif