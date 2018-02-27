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
	bool LoadFile(std::string name);
	
	std::string GetName();
	void SetName(std::string name);

	bool GetLoaded();

protected:
	std::string m_name;
	bool m_loaded;
	void SetLoaded(bool loaded);

};

#endif