#ifndef TRESOURCE_H
#define TRESOURCE_H

#include <iostream>
#include <GL/glew.h>

//Headers to load models
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class TResource{
public:
	TResource();
	virtual ~TResource();

	virtual bool LoadFile() = 0;
	virtual bool LoadFile(std::string name) = 0;
	
	std::string GetName();
	void SetName(std::string name);

	bool GetLoaded();

protected:
	std::string m_name;
	bool m_loaded;
	bool SetLoaded(bool loaded);

};

#endif