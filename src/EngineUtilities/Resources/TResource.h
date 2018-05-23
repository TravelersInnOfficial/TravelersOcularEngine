#ifndef TRESOURCE_H
#define TRESOURCE_H

/**
 * @brief Father class of all resources that will be obtained from disk.
 * 
 * @file TResource.h
 */

#include <string>

class TResource{
public:
	/**
	 * @brief 	- Constructo vacio de la clase Recurso
	 */
	TResource();

	/**
	 * @brief	- Destructor vacio de la clase Recurso 
	 */
	virtual ~TResource();

	/**
	 * @brief	- Metodo abstracto para cargar archivo 
	 */
	virtual bool LoadFile() = 0;

	/**
	 * @brief	- Cargamos el archivo a partir de su ruta 
	 * 
	 * @param 	- name - Path del recurso 
	 * @return 	- bool - El recurso se ha cargado correctamente
	 */
	bool LoadFile(std::string name);
	
	/**
	 * @brief	- Devolvemos la ruta al recurso 
	 * 
	 * @return 	- std::string - Ruta al recurso
	 */
	std::string GetName();

	/**
	 * @brief	- Cambiamos la ruta al recurso 
	 * 
	 * @param 	- name - Nueva ruta 
	 */
	void SetName(std::string name);

	/**
	 * @brief	- Devolvemos si el recurso esta correctamente cargado 
	 * 
	 * @return 	- bool - True: Se ha cargado bien
	 * @return 	- bool - False: No se ha cargado bien
	 */
	bool GetLoaded();

protected:
	std::string m_name;				// m_name - Ruta al recurso
	bool m_loaded;					// m_loaded - Si el recurso se ha cargado bien

	/**
	 * @brief	- Cambia el valor de si esta cargado bien 
	 * 
	 * @param 	- loaded -  Nuevo valor de carga 
	 */
	void SetLoaded(bool loaded);

};

#endif