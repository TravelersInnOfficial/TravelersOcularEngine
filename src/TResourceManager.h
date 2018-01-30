#ifndef TRESOURCEMANAGER_H
#define TRESOURCEMANAGER_H

#include "./Resources/TResource.h"

#include <iostream>
#include <vector>

// -----------------------------------IMPORTANTE-------------------------------
// Singleton? 

class TResourceManager{
public:
	TResourceManager();
	~TResourceManager();

	TResource* FindResource(std::string);
	TResource* GetResource(std::string);

private:
	std::vector<TResource*> m_resources;
};

#endif