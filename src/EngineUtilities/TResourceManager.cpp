#include "TResourceManager.h"

TResourceManager* TResourceManager::GetInstance() {
	static TResourceManager instance;
	return &instance;
}

TResourceManager::TResourceManager(){}

/*********************************************
 * @brief Destructor
 *********************************************/
TResourceManager::~TResourceManager(){
	std::map<std::string, TResource*>::iterator it = m_resources.begin();

	for(; it != m_resources.end(); it++){
		TResource* tResource = it->second;
		if (tResource != nullptr) delete tResource;	//Delete the resource in the map
	}

	m_resources.clear();		//Clear the map
}

/*********************************************
 * @brief Find the resource of the string passed
 * @param std::string path of the resource
 *********************************************/
TResource* TResourceManager::FindResource(std::string name){
	TResource* output = nullptr;
	std::map<std::string, TResource*>::iterator it = m_resources.find(name); //Search the resource
	if (it != m_resources.end()) output = it->second;
	return output;
}

TResourceTexture* TResourceManager::GetResourceTexture(std::string name){ 
	TResourceTexture* toRet = nullptr;
	std::string path = TreatName(name);
	toRet = (TResourceTexture*)FindResource(path);
	if(toRet == nullptr){
		toRet = new TResourceTexture(path);
		m_resources[path] = toRet;
	}
	return toRet;
}

TResourceMesh* TResourceManager::GetResourceMesh(std::string name){ 
	TResourceMesh* toRet = nullptr;
	std::string path = TreatName(name);
	toRet = (TResourceMesh*)FindResource(path);
	if(toRet == nullptr) {
		toRet = new TResourceMesh(path);
		m_resources[path] = toRet;
	}
	return toRet;
}

TResourceMaterial* TResourceManager::GetResourceMaterial(std::string name){
	// En el caso de los materiales en nombre no sera el path para el recurso
	// Sera directamente el nombre del material
	TResourceMaterial* toRet = nullptr;
	std::string path = TreatName(name);
	toRet = (TResourceMaterial*)FindResource(path);
	if(toRet == nullptr) {
		// Una vez llegados aqui significa que no se ha encontrado un material con este nombre
		// Asi que crearemos uno nuevo con este nombre para que se rellene a partir del puntero
		toRet = new TResourceMaterial(path);
		m_resources[path] = toRet;
	}
	return toRet;
}

TResourceShader* TResourceManager::GetResourceShader(std::string name){ 
	TResourceShader* toRet = nullptr;
	std::string path = TreatName(name);
	toRet = (TResourceShader*)FindResource(path);
	if(toRet == nullptr) {
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
