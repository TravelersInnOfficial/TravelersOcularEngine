#ifndef TFPORTAL_H
#define TFPORTAL_H

/**
 * @brief Clipping Portal Facade.
 * 
 * @file TFPortal.h
 */

#include <TOEvector3d.h>

class TPortal;
class TFRoom;

class TFPortal{
	friend class TFRoom;
public:
	/**
	 * @brief	- Des/Activamos el protal 
	 */
	void SetVisible(bool visible);

	/**
	 * @brief	- Cambiamos el centro del portal 
	 */
	void SetCenter(TOEvector3df center);

	/**
	 * @brief	- Cambiamos la rotacion del portal 
	 */
	void SetRotation(TOEvector3df rot);

	/**
	 * @brief	- Cambiamos el tamanyo del portal 
	 */
	void SetSize(TOEvector3df size);
private:
	TPortal* m_portal;		// m_portal - Puntero al TPortal
	TFRoom*  m_firstRoom;	// m_firstRoom - Primera habitacion del portal
	TFRoom*  m_secondRoom;	// m_secondRoom - SEgunda habitaicon del portal

	/**
	 * @brief	- Destructor del portal 
	 */
	~TFPortal();

	/**
	 * @brief	- Constructor del portal 
	 * 
	 * @param 	- portal - Puntero al objeto TPortal
	 * @param 	- first - Primera habitacion
	 * @param 	- second - Segunda habitacion
	 */
	TFPortal(TPortal* portal, TFRoom* first, TFRoom* second);
	
	/**
	 * @brief	- Devuelve el portal almacenado en la clase 
	 */
	TPortal* GetPortal();

	/**
	 * @brief	- Devuelve la primera habitacion 
	 */
	TFRoom* GetFirstRoom();

	/**
	 * @brief	- Devuelve la segunda habitacion 
	 */
	TFRoom* GetSecondRoom();

	/**
	 * @brief	- Devuelve si el portal es visible o no 
	 */
	bool CheckVisibility();

	/**
	 * @brief 	- Devuelve si el portal esta activo o no 
	 */
	bool GetVisible();
};

#endif