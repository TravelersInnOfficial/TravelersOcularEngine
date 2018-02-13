#ifndef TRESOURCE_H
#define TRESOURCE_H

#include <iostream>
#include <GL/glew.h>

class TResource{
public:
	TResource();
	virtual ~TResource();

	virtual bool LoadFile() = 0;
	std::string GetName();

protected:
	std::string m_name;

};

#endif