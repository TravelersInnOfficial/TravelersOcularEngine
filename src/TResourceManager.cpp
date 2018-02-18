#include "TResourceManager.h"

static TResourceManager* instance = NULL;

TResourceManager* TResourceManager::GetInstance() {
	if (instance == NULL) instance = new TResourceManager();
	return instance;
}

TResourceManager::TResourceManager(){}

/*********************************************
 * @brief Destructor
 *********************************************/
TResourceManager::~TResourceManager(){
	std::map<std::string, TResource*>::iterator it = m_resources.begin();

	for(; it != m_resources.end(); it++){
		TResource* tResource = it->second;
		if (tResource != NULL) delete tResource;	//Delete the resource in the map
	}

	m_resources.clear();		//Clear the map
}

/*********************************************
 * @brief Find the resource of the string passed
 * @param std::string path of the resource
 *********************************************/
TResource* TResourceManager::FindResource(std::string name){
	TResource* output = NULL;
	std::map<std::string, TResource*>::iterator it = m_resources.find(name); //Search the resource
	if (it != m_resources.end()) output = it->second;
	return output;
}

TResourceTexture* TResourceManager::GetResourceTexture(std::string name){ 
	TResourceTexture* toRet = NULL;
	std::string path = TreatName(name);
	toRet = (TResourceTexture*)FindResource(path);
	if(toRet == NULL){ 
		toRet = new TResourceTexture(path);
		m_resources[path] = toRet;
	}
	return toRet;
}

TResourceMesh* TResourceManager::GetResourceMesh(std::string name){ 
	TResourceMesh* toRet = NULL;
	std::string path = TreatName(name);
	toRet = (TResourceMesh*)FindResource(path);
	if(toRet == NULL) {
		toRet = new TResourceMesh(path);
		m_resources[path] = toRet;
	}
	return toRet;
}

TResourceMaterial* TResourceManager::GetResourceMaterial(std::string name){ 
	TResourceMaterial* toRet = NULL;
	std::string path = TreatName(name);
	toRet = (TResourceMaterial*)FindResource(path);
	if(toRet == NULL) {
		toRet = new TResourceMaterial(path);
		m_resources[path] = toRet;
	}
	return toRet;
}

TResourceShader* TResourceManager::GetResourceShader(std::string name){ 
	TResourceShader* toRet = NULL;
	std::string path = TreatName(name);
	toRet = (TResourceShader*)FindResource(path);
	if(toRet == NULL) {
		toRet = new TResourceShader(path);
		m_resources[path] = toRet;
	}
	return toRet;
}


std::string TResourceManager::TreatName(std::string newName) {

	std::string toSearch = "./";	//Pattern to delete
	int pos = 0;

	do {
		pos = newName.find(toSearch, pos);
		bool erase = true;

		if (pos == -1) erase = false; 								//If not found
		else if (pos == 0) erase = true;							//If first position 
		else if (newName.at(pos-1) != '.') erase = true;			//If hasnt dot behind
		else if (newName.at(pos-1) == '.') {erase = false; pos++;}	//If has dot behind

		//Erase the current position and next (./)
		if (erase) newName.erase(pos,2); 
	} while (pos != -1); // While we find "./"

	 //If there's a slash at the begining, erase it
	if (newName.at(0) == '/') newName.erase(0,1);

	//Erase the slashes at the end
	bool finish = false;
	do {
		finish = false;
		if (newName.at(newName.length()-1) == '/') {
			newName.erase(newName.length()-1,1);
			finish = true;
		} 
	} while (finish);

	return newName;
}
