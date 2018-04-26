#ifndef TFROOM_H
#define TFROOM_H

#include "./TFNode.h"
#include "./TFPortal.h"

class TFLight;

class TFRoom: public TFNode{
	friend class SceneManager;
public:
	TFPortal* AddConnection(TFRoom* room, 
							toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0), 
							toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0),
							toe::core::TOEvector3df scale = toe::core::TOEvector3df(1,1,1));

	bool DeletePortal(TFPortal* portal);

	void SetTranslate(toe::core::TOEvector3df translation) override;	
	void SetRotation(toe::core::TOEvector3df rotation) override;		
	void SetScale(toe::core::TOEvector3df scale) override;			

	void Translate(toe::core::TOEvector3df translation) override;	
	void Rotate(toe::core::TOEvector3df rotation) override;					
	void Scale(toe::core::TOEvector3df scale) override;

	toe::core::TOEvector3df GetTranslation() override;
	toe::core::TOEvector3df GetRotation() override;
	toe::core::TOEvector3df GetScale() override;

	bool AddChild(TFNode* children) override;


	float GetDistance(toe::core::TOEvector3df position);
	void DeleteLight(TFNode* light);

private:
	std::vector<TFPortal*> m_portals;
	std::vector<TFLight*> m_roomLights;		// COPIA a las luces, no eliminar
	bool lightsSend;

	void Draw();
	int DrawLights(int value, int nextTo = 2);
	TNode* GetConnectionNode() override;
	TFRoom(toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1));
	~TFRoom();
};

#endif