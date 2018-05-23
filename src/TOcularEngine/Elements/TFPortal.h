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

	void SetVisible(bool visible);
	void SetCenter(TOEvector3df center);
	void SetRotation(TOEvector3df rot);
	void SetSize(TOEvector3df size);
private:
	TPortal* m_portal;
	TFRoom*  m_firstRoom;
	TFRoom*  m_secondRoom;

	~TFPortal();
	TFPortal(TPortal* portal, TFRoom* first, TFRoom* second);
	TPortal* GetPortal();
	TFRoom* GetFirstRoom();
	TFRoom* GetSecondRoom();
	bool CheckVisibility();
	bool GetVisible();
};

#endif