#ifndef TFROOM_H
#define TFROOM_H

/**
 * @brief Clipping Room Facade.
 * 
 * @file TFRoom.h
 */

#include "./TFNode.h"
#include "./TFPortal.h"

class TFLight;

class TFRoom: public TFNode{
	friend class SceneManager;
public:
	/**
	 * @brief	- AddConnection 
	 * 
	 * @param 	- room - Rotacion con la que conecta
	 * @param 	- position - Posicion del portal
	 * @param 	- scale - Tamanyo del portal
	 * @param 	- rotation - Rotacion del portal
	 * @return 	- TFPortal - Portal que se crea
	 */
	TFPortal* AddConnection(TFRoom* room, 
							TOEvector3df position = TOEvector3df(0,0,0), 
							TOEvector3df rotation = TOEvector3df(0,0,0),
							TOEvector3df scale = TOEvector3df(1,1,1));

	/**
	 * @brief	- Elimina el portal pasado por parametros 
	 */
	bool DeletePortal(TFPortal* portal);

	/**
	 * @brief	- Cambia la posicion de la habitaion
	 */
	void SetTranslate(TOEvector3df translation) override;

	/**
	 * @brief	- Cambia la rotacion de la habitacion
	 */	
	void SetRotation(TOEvector3df rotation) override;

	/**
	 * @brief	- Cambia el tamanyo de la habitacion
	 */		
	void SetScale(TOEvector3df scale) override;			

	/**
	 * @brief	- Translada la habitacion 
	 */
	void Translate(TOEvector3df translation) override;	

	/**
	 * @brief	- Rota la habitacion 
	 */
	void Rotate(TOEvector3df rotation) override;

	/**
	 * @brief	- Escala la habitacion 
	 */					
	void Scale(TOEvector3df scale) override;

	/**
	 * @brief	- Devuelve la translacion de la habitacion 
	 */
	TOEvector3df GetTranslation() override;

	/**
	 * @brief	- Devuelve la rotacion de la habitacon 
	 */
	TOEvector3df GetRotation() override;

	/**
	 * @brief	- Devuelve el escalado de la habitacion 
	 */
	TOEvector3df GetScale() override;

	/**
	 * @brief	- Anyade un nodo a la habitacion 
	 */
	bool AddChild(TFNode* children) override;

	/**
	 * @brief	- Elimina la luz de la habitacion 
	 */
	void DeleteLight(TFNode* light);

	/**
	 * @brief	- Devuelve la distancia del punto a la habitacion 
	 */
	float GetDistance(TOEvector3df position);

	/**
	 * @brief	- Cambia la variable de enviar luces al shader
	 */
	void SetLightsSend(bool value);

private:
	std::vector<TFPortal*> m_portals;		// m_portals - Vector de portales de la habitacion
	std::vector<TFLight*> m_roomLights;		// m_roomLights - Vector de luces de la habitacion
	bool lightsSend;						// lightsSend - Enviar las luces al shader?

	/**
	 * @brief	- Pintamos los elementos de la habitacion 
	 */
	void Draw();

	/**
	 * @brief	- Enviamos las luces al shader 
	 * 
	 * @param 	- value - Ultima luz pintada 
	 * @param 	- nextTo - Grado de cercania de la habitacion
	 * 
	 * @return	- int - Numero de luces enviadas al shader 
	 */
	int DrawLights(int value, int nextTo = 2);

	/**
	 * @brief	- Marcamos la habitacion como (No)Pintado 
	 */
	void SetDrawed(bool value);

	// Devuelve el nodo al que se uniran los demas nodos
	TNode* GetConnectionNode() override;

	/**
	 * @brief	- Constructor de la clase TFRoom  
	 * 
	 * @param 	- position - Posicion de la habitacion
	 * @param 	- rotation - ROtacion de la habitacion
	 * @param 	- scale - Tamanyo de la habitacion
	 */
	TFRoom(TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1));

	/**
	 * @brief	- Destructor de la habitacion 
	 */
	~TFRoom();
};

#endif