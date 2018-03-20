#ifndef TPORTAL_H
#define TPORTAL_H

#include "./TRoom.h"

class TPortal{
public:
	TPortal(TRoom* first, TRoom* second);
	~TPortal();
private:
	TRoom* m_firstRoom; 
	TRoom* m_secondRoom;
};

#endif