#include "TResourceManager.h"
#include <iostream>

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
	std::map<std::string, TResource*>::iterator it = m_resources.find(name); // Buscamos el recurso
	if (it != m_resources.end()) output = it->second;	// En el caso de que exista lo almacenamos en el output y lo devolvemos
	return output;						
}

TResourceTexture* TResourceManager::GetResourceTexture(std::string name){ 
	TResourceTexture* toRet = nullptr;
	std::string path = TreatName(name);				// Tratamos la ruta para quitar elementos innecesarios de la ruta
	toRet = (TResourceTexture*)FindResource(path);	// Buscamos el recurso
	if(toRet == nullptr){							
		toRet = new TResourceTexture(path);			//
		m_resources[path] = toRet;					// Si no existe lo creamos y cargamos
	}
	return toRet;									// Devolvemos el recurso
}

TResourceMesh* TResourceManager::GetResourceMesh(std::string name){ 
	TResourceMesh* toRet = nullptr;
	std::string path = TreatName(name);				// Tratamos la ruta para quitar elemenots innecesarios d la ruta
	toRet = (TResourceMesh*)FindResource(path);		// Buscamos el recurso
	if(toRet == nullptr) {
		toRet = new TResourceMesh(path);			//
		m_resources[path] = toRet;					// Si no existe lo creamos y cargamos
	}
	return toRet;									// Devolvemos el recurso
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

TResourceShader* TResourceManager::GetResourceShader(std::string name, GLenum shaderType){ 
	TResourceShader* toRet = nullptr;
	std::string path = TreatName(name);				// Tratamos la ruta para quitar elemenots innecesarios d la ruta
	toRet = (TResourceShader*)FindResource(path);	// Buscamos el recurso
	if(toRet == nullptr) {
		toRet = new TResourceShader(path, shaderType);	//
		m_resources[path] = toRet;						// En caso de no encontrarlo lo creamos y cargamos
	}
	return toRet;									// Devolvemos el recurso
}		

bool TResourceManager::DeleteResourceTexture(std::string name){
	std::string path = TreatName(name);	// Tratamos la ruta

	// Buscamos entre los recursos uno que se llame igual que la ruta pasada
	std::map<std::string, TResource*>::iterator it = m_resources.begin();
	for(; it != m_resources.end(); ++it){
		if(path.compare(it->first) == 0){
			delete it->second;				//
			m_resources.erase(it);			//
			return true;					// En el caso de encontrarlo lo eliminamos
		}
	}
	return false;
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
