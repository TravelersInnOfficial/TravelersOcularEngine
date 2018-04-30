#ifndef TFROOM_H
#define TFROOM_H

#include "./TFNode.h"
#include "./TFPortal.h"

class TFLight;

class TFRoom: public TFNode{
	friend class SceneManager;
public:
	TFPortal* AddConnection(TFRoom* room, 
							TOEvector3df position = TOEvector3df(0,0,0), 
							TOEvector3df rotation = TOEvector3df(0,0,0),
							TOEvector3df scale = TOEvector3df(1,1,1));

	bool DeletePortal(TFPortal* portal);

	void SetTranslate(TOEvector3df translation) override;	
	void SetRotation(TOEvector3df rotation) override;		
	void SetScale(TOEvector3df scale) override;			

	void Translate(TOEvector3df translation) override;	
	void Rotate(TOEvector3df rotation) override;					
	void Scale(TOEvector3df scale) override;

	TOEvector3df GetTranslation() override;
	TOEvector3df GetRotation() override;
	TOEvector3df GetScale() override;

	bool AddChild(TFNode* children) override;
	void DeleteLight(TFNode* light);

	float GetDistance(TOEvector3df position);

private:
	std::vector<TFPortal*> m_portals;
	std::vector<TFLight*> m_roomLights;		// COPIA a las luces, no eliminar
	bool lightsSend;

	void Draw();
	int DrawLights(int value, int nextTo = 2);
	TNode* GetConnectionNode() override;
	TFRoom(TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1));
	~TFRoom();
};

#endif