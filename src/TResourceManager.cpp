#include "TResourceManager.h"

TResourceManager::TResourceManager(){}

TResourceManager::~TResourceManager(){
	int size = m_resources.size();
	for(int i=0; i<size; i++){
		TResource* resource = m_resources[i];
		delete resource;
	}
	m_resources.clear();
}

TResource* TResourceManager::FindResource(std::string name){
	TResource* output = NULL;

	int size = m_resources.size();
	for(int i=0; i<size; i++){
		TResource* resource = m_resources[i];
		std::string resourceName = resource->GetName();
		if(name.compare(resourceName) == 0){
			output = m_resources[i];
			break;
		}
	}

	return output;
}

TResource* TResourceManager::GetResource(std::string name){
	TResource* resource = FindResource(name);
	if(resource == NULL){
		// -----------------------------------IMPORTANTE-------------------------------
		// Habria que saber que tipo de dato es, ya sea con diferenes metodo para cada
		// tipo de dato o con un segundo valor que lo especifique. OPTO POR PRIMERO
		
		//resource = new TResource();
		//resource->LoadFile(name);
		m_resources.push_back(resource);
	}
	return resource;
}
