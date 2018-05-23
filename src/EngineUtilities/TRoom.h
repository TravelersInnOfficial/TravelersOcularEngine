#ifndef TROOM_H
#define TROOM_H

#include <vector>
#include "./TNode.h"
#include <glm/gtc/type_ptr.hpp>

class TPortal;

class TRoom: public TNode{
public:
	/**
	 * @brief	- Constructor de la clase habitacion 
	 * 
	 * @param 	- size - Tamanyo de la habitacion
	 * @param 	- center - Centro de la habitacion
	 * @param 	- rotation - Rotacion de la habitacion
	 */
	TRoom(glm::vec3 size, glm::vec3 center, glm::vec3 rotation);

	/**
	 * @brief	- Destructor de la clase Habitacion 
	 */
	~TRoom();

	/**
	 * @brief	- Pintamos todos los nodos hijo de la habitacion 
	 */
	void Draw() override;

	/**
	 * @brief	- Anyadimos un portal a la habitacion 
	 * 
	 * @param 	- connection - Habitacion a la que llevara el portal
	 * @param 	- size - Tamanyo del portal
	 * @param 	- center - Centro del protal
	 * @param 	- rotation - Rotacion del portal
	 * @return 	- TPortal - Portal que se ha creado
	 */
	TPortal* AddPortal(TRoom* connection, glm::vec3 size, glm::vec3 center, glm::vec3 rotation);
	
	/**
	 * @brief	- Elimina el portal pasado por parametros 
	 * 
	 * @param 	- portal - Portal a eliminar 
	 * @return 	- bool - El portal se ha eliminado correctamente
	 */
	bool DeletePortal(TPortal* portal);
	
	/**
	 * @brief	- Cambia el tamanyo de la habitacion 
	 */
	void SetSize(glm::vec3 size);

	/**
	 * @brief	- Cambia el centro de la habitacion 
	 */
	void SetCenter(glm::vec3 center);

	/**
	 * @brief	- Cambia la rotacion de la habitacion 
	 */
	void SetRotation(glm::vec3 rot);

	/**
	 * @brief	- Escala la habitacion 
	 */
	void Scale(glm::vec3 size);

	/**
	 * @brief	- Translada la habitacion 
	 */
	void Translate(glm::vec3 center);

	/**
	 * @brief	- Rota la habitacion 
	 */
	void Rotate(glm::vec3 rot);

	/**
	 * @brief	- Devuelve el tamanyo de la habitacion 
	 */
	glm::vec3 GetSize();

	/**
	 * @brief	- Devuelve el centro de la habitacion 
	 */
	glm::vec3 GetCenter();

	/**
	 * @brief	- Devuelve la rotacion de la habitacion 
	 */
	glm::vec3 GetRotation();

	/**
	 * @brief	- Devuelve si se ha pintado ya la habitacion 
	 */
	bool GetDrawed();

	/**
	 * @brief	- Cambiamos el valor de si se ha pintado la habitacion 
	 */
	void SetDrawed(bool value);

	/**
	 * @brief	- Devuelve la distancia de un punto a la habitacion 
	 * 
	 * @param 	- point - Punto con el que calcular la distancia 
	 * @return 	- float - distancia del punto a la habitacion
	 */
	float GetDistance(glm::vec3 point);

private:
	/**
	 * @brief	- Calcula el valor mas cercano entre A y B para el valor target 
	 * 
	 * @param 	- pointA - Extremo A
	 * @param 	- pointB - Extremo B
	 * @param 	- target - Valor con el que comparar
	 * @return 	- float - Valor mas cercano
	 */
	float NearestPoint(float pointA, float pointB, float target);

	/**
	 * @brief	- Calcula la transformacion de la habitacion 
	 */
	void CalculateTransform();

	/**
	 * @brief	- Guardamos en la clase los limites del clipping antes de pintar la habitacion 
	 */
	void PushClippingLimits();

	/**
	 * @brief	- Vuelve a poner los limites del clipping que habian antes de pintar la habitacion 
	 */
	void PopClippingLimits();
	bool drawed;						// drawed - Esta habitacion ha sido ya dibujada? Si/No

	std::vector<TPortal*> m_portals;	// m_portals - Portales de la habitacion
	float m_stackClipping[4];			// m_stackClipping[] - Copia de los limites del clipping

	// Tamanyo de la habitacion
	glm::mat4 m_transform;				// m_transform - Matriz transformacion de la habitacion
	glm::vec3 m_size;					// m_size - Tamanyo de la habitacion
	glm::vec3 m_center;					// m_center - Centro de la habitacion
	glm::vec3 m_rotation;				// m_rotation - Rotacion de la habition

	/**
	 * @brief	- Pinta la forma de la habitacion de color rojo 
	 */
	void DrawDebug();
};


#endif