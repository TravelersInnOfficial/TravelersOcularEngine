#include "TTextureLoader.h"
#include <SOIL2.h>
#include <fstream>

bool TTextureLoader::LoadTexture(std::string path, unsigned char* imageData, int* width, int* height){
	std::ifstream file(path);									// |
	if(!file.fail()) file.close();								// |
	else{														// |
		std::cout<<"File not found " + path<<std::endl;			// |
		return false;												// | Comprobacion de que exista
	}

	// Cargamos la imagen forzando el numero de canales a 4 (SOIL_LOAD_RGBA)
	int channels;
	imageData = SOIL_load_image(path.c_str(), width, height, &channels, SOIL_LOAD_RGBA);
	
	// Mostramos los datos por consola
	/*if(imageData != NULL){
		std::cout<<"MIS PIXELES SON: "<<std::endl;
		for(int i = 0; i < *width * *height * 4; i++){
			std::cout<<(int)imageData[i]<<std::endl;
		}
	}*/

	// Comprobamos si hemos cargado la imagen
	bool toRet = true;
	if(imageData == NULL){
		std::cout<<"Could not open file " + path<<std::endl;
		toRet = false;
	}
	return toRet;
}