#include "TTextureLoader.h"
#include <SOIL2/SOIL2.h>
#include <fstream>
#include <string.h>

bool TTextureLoader::LoadTexture(std::string path, unsigned char** imageData, int* width, int* height){

	std::ifstream file(path);									// |
	if(!file.fail()) file.close();								// |
	else{														// |
		std::cout<<"File not found " + path<<std::endl;			// |
		return false;											// | Comprobacion de que exista
	}

	// Cargamos la imagen forzando el numero de canales a 4 (SOIL_LOAD_RGBA)
	int channels;
	*imageData = SOIL_load_image(path.c_str(), width, height, &channels, SOIL_LOAD_RGBA);

	// Comprobamos si hemos cargado la imagen
	bool toRet = true;
	if(imageData == nullptr){
		std::cout<<"Could not open file " + path<<std::endl;
		toRet = false;
	}

	return toRet;
}

bool TTextureLoader::LoadTextureBinary(std::string path, std::vector<unsigned char>* imageData, int* width, int* height){
	bool output = false;

	std::ifstream texFile;
	texFile.open(path, std::ios::binary);

	if(texFile.is_open()){
		texFile.read(reinterpret_cast<char*>(width), sizeof(int));
		texFile.read(reinterpret_cast<char*>(height), sizeof(int));

		int size = (*width)*(*height) * 4;

		unsigned char currentChar;
		for(int i=0; i<size; i++){
			texFile.read(reinterpret_cast<char*>(&currentChar), sizeof(unsigned char));
			imageData->push_back(currentChar);
		}

		output = true;
	}
	texFile.close();

	return output;
}
