#ifndef TCOLOR_H
#define TCOLOR_H

/**
 * @brief Color class which contains vector4 of floats.
 * 
 * @file TColor.h
 */

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

class TColor {
public:
	/**
	 * @brief - Constructor de la clase color
	 * 
	 * @param - rgbaData - Componentes RGBA del color, por defecto todos los valores se quedan a 0
	 */
	TColor(glm::vec4 rgbaData = glm::vec4(0,0,0,0));

	/**
	 * @brief 	- Destructor de la clase color
	 * @details - Como esta clase no hace uso de variables dinamicas no hay nada que eliminar 
	 * 				por lo que el metodo esta vacio
	 */
	~TColor();

	/**
	 * @brief 	- Cambia los valores RGBA del color por los pasados por parametros 
	 * 
	 * @param 	- newVal - Componentes RGBA del nuevo color
	 */
	void SetRGBA(glm::vec4 newVal);

	/**
	 * @brief 	- Cambia los valores RGBA del color por los pasador por parametros
	 * 
	 * @param 	- R - Nuevo valor Red del color
	 * @param 	- G - Nuevo valor Green del color 
	 * @param 	- B - Nuevo valor Blue del color 
	 * @param 	- A - Nuevo valor Alpha del color 
	 */
	void SetRGBA(float R, float G, float B, float A);

	/**
	 * @brief 	- Cambia valores RGB del color, dejando el alpha igual
	 * 
	 * @param 	- newVal - Componentes RGB del nuevo color
	 */
	void SetRGB(glm::vec3 newVal);

	/**
	 * @brief 	- Cambia el componente Red del color
	 * 
	 * @param 	- newVal - Valor nuevo de Red
	 */
	void SetR(float newVal);

	/**
	 * @brief 	- Cambia el componente Green del color
	 * 
	 * @param 	- newVal - Valor nuevo de Green
	 */
	void SetG(float newVal);

	/**
	 * @brief	- Cambia el componente Blue del color
	 * 
	 * @param 	- newVal - Valor nuevo de Blue
	 */
	void SetB(float newVal);

	/**
	 * @brief 	- Cambia el componente Alpha del color
	 * 
	 * @param 	- newVal - Valor nuevo de Alpha
	 */
	void SetA(float newVal);

	/**
	 * @brief 	- Devuelve el valor RGBA del color  
	 * 
	 * @return 	- glm::vec4 - Componente RGBA del color
	 */
	glm::vec4 GetRGBA();

	/**
	 * @brief 	- Devuelve el valor RGB del color 
	 *
	 * @return - glm::vec3 - Componente RGB del color
	 */
	glm::vec3 GetRGB();

	/**
	 * @brief 	- Devuelve el valor Red del color
	 *
	 * @return	- float - Componente Red del color
	 */
	float GetR() const;

	/**
	 * @brief	- Devuelve el valor Green del color 
	 *
	 * @return	- float - Componente Green del color 
	 */
	float GetG() const;

	/**
	 * @brief	- Devuelve el valor Blue del color
	 * 
	 * @return	- float - Componente Blue del color
	 */
	float GetB() const;

	/**
	 * @brief	- Devuelve el valor Alpha del color
	 * 
	 * @return	- float - Componente Alpha del color
	 */
	float GetA() const;

	/**
	 * @brief	- Trunca el valor pasado por parametro para que se encuentre en el rango de [0, 1]
	 * 				ya que la clase color utiliza valores en estos rangos
	 * 
	 * @param 	- valueToCap - Valor a truncar
	 * @return  - float - Valor entre [0, 1] del que se ha pasado por parametro
	 */
	float CapValues(float valueToCap);

	/**
	 * @brief	- Trunca los valores pasados por parametros para que se encuentren en el rango de [0, 1]
	 * 				ya que la clase color utiliza valores en estos rangos
	 * 
	 * @param 	- valueToCap - Valores a truncar
	 * @return 	- glm::vec3 - Valores entre [0, 1] de los pasados por parametros
	 */
	glm::vec3 CapValues(glm::vec3 valueToCap);

	/**
	 * @brief	- Trunca los valores pasados por parametros para que se encuentren en el rango de [0, 1]
	 * 				ya que la clase color utiliza valores en estos rangos
	 * 
	 * @param 	- valueToCap - Valores a truncar
	 * @return 	- glm::vec4 - Valores entre [0, 1] de los pasados por parametros
	 */
	glm::vec4 CapValues(glm::vec4 valueToCap);

private:
	glm::vec4 m_rgba;		// m_rgba - Valor RGBA del color

};

#endif