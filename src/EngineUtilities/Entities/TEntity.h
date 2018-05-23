#ifndef TENTITY_H
#define TENTITY_H

/**
 * @brief Entity father class that will fill scene tree.
 * 
 * @file TEntity.h
 */

#include <ShaderTypes.h>
#include "../Resources/Program.h"
#include <stack>
#include <glm/mat4x4.hpp>

class TEntity{
public:
	/**
	 * @brief	- Destructor virtual de la clase TEntity, por defecto el destructor esta vacio
	 * 				y se va editando en las clases que heredan de esta
	 */
	virtual ~TEntity();

	/**
	 * @brief	- Metodo abstracto que se llama al dejar de pintar una entidad
	 */
	virtual void EndDraw() = 0;

	/**
	 * @brief	- Metodo abstracto que se llama al empezar a pintar una entidad
	 */
	virtual void BeginDraw() = 0;

	/**
	 * @brief	- Metodo que se llama al pintar las sombras, por defecto las entidades lo tienen vacio
	 */
	virtual void DrawShadow();

	/**
	 * @brief	- Metodo que compprueba si un objeto esta dentro de la pantalla
	 * 				por defecto solo compara con el centro
     *
	 * @return	- bool - En el caso de devolver true es que se encuentra dentro de la pantalla
	 */
	virtual bool CheckClipping();

	/**
	 * @brief	- Cambia el shader con el que se va a pintar la entidad 
	 * 
	 * @param 	- program - Enumerador del programa a utilizar 
	 */
	void SetProgram(SHADERTYPE program);

	/**
	 * @brief	- Cambia la matriz View que utilizan las entidades
	 * 
	 * @param 	- view - Nueva matriz View
	 */
	static void SetViewMatrixPtr(glm::mat4 view);

	/**
	 * @brief	- Vuelve a poner los limites del clipping a los valores por defecto, los extremos de la pantalla
	 */
	static void ResetClippingVariables();

	/**
	 * @brief	- Inicializa la matriz de la pila a la identidad 
	 *
	 * @return 	- std::stack<glm::mat4> - Pila de matrices con la que empezar
	 */
	static std::stack<glm::mat4> InitializeStack();

	static std::stack<glm::mat4> m_stack;	// m_stack - Pila de transformaciones de las entidades
	static bool m_checkClipping;			// m_checkClipping - Booleano para activar o desactivar la comprobacion del clipping
	static float m_clippingLimits[4];		// m_clippingLimits[] - Los cuatros limites de la pantalla para comparar el clipping
											// 0 (+X) / 1 (-X) / 2 (+Y) / 3 (-Y)
	
	static glm::mat4 ViewMatrix;			// ViewMatrix - Matriz view a utilizar por las entidades
	static glm::mat4 ProjMatrix;			// ProjMatrix - Matriz projection a utilizar por las entidades
	static glm::mat4 DepthWVP;				// DepthWVP - Matriz view desde la luz hasta las entidades

	static unsigned int currentFrame;		// currentFrame - Variable donde almacenamos el frame actual en el que nos encontramos
											// Esta variable se usa para asegurarnos que los objetos no se lleguen a pintar dos veces el mismo frame
	
    SHADERTYPE m_program = NONE_SHADER;		// m_program - Shader que va a utilizar la entidad

protected:
	/**
	 * @brief	- Comprueba si un punto se encuentra dentro de la pantalla 
	 * 
	 * @param 	- point - vector4 que es el resultado de multiplicar un punto por la MVP
	 * @return 	- bool - Si el punto se encuentra dentro de la pantalla devolverá true
	 */
	bool CheckClippingPoint(glm::vec4 point);

	/**
	 * @brief 	- Metodo que mira por que lados se el objeto de la pantalla
	 * 				En el caso de que se salga por uno de los lados se incrementara
	 * 				el valor correspondiente a ese lado
	 * 
	 * @param 	- point - vector4 que es el resultado de multiplicar un punto por la MVP
	 * @param 	- upDown - puntero que lleva la cuenta de cuantas veces se sale por arriba/abajo el objeto
	 * 						+1 en el caso de salirse por arriba, -1 en el caso de salirse por debajo
	 * @param 	- leftRight - puntero que lleva la cuenta de cuantas veces se sale por los lados el objeto
	 * 						+1 en el caso de salirse por la derecha, -1 en el caso de salirse por la izquiera
	 * @param 	- nearFar - puntero que lleva la cuenta de cuantas veces se sale del near/far de la camara el objeto
	 * 						+1 en el aso de salirse por el far, -1 en el caso de salirse por el near
	 */
	void CheckClippingAreas(glm::vec4 point, int* upDown, int* leftRight, int* nearFar);
};

#endif