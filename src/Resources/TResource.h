#ifndef TRESOURCE_H
#define TRESOURCE_H

#include <iostream>
#include <GL/glew.h>

class TResource{
public:
	TResource();
	virtual ~TResource();

	virtual bool LoadFile(std::string name) = 0;

	std::string GetName();
	void SetName(std::string name);
private:
	std::string m_name;
};

#endif