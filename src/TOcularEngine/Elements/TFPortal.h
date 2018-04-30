#ifndef TFPORTAL_H
#define TFPORTAL_H

#include <TOEvector3d.h>

class TPortal;
class TFRoom;

class TFPortal{
	friend class TFRoom;
public:

	void SetVisible(bool visible);
	void SetCenter(TOEvector3df center);
	void SetRotation(TOEvector3df rot);
	void SetSize(TOEvector3df size);
private:
	TPortal* m_portal;
	TFRoom* m_room;

	~TFPortal();
	TFPortal(TPortal* portal);
	TPortal* GetPortal();
};

#endif