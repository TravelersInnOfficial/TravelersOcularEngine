#include "TTextureLoader.h"
#include <SOIL/SOIL.h>
#include <fstream>

GLuint TTextureLoader::LoadTexture(std::string path){
	std::ifstream file(path);									// |
	if(!file.fail()) file.close();								// |
	else{														// |
		std::cout<<"File not found " + path<<std::endl;			// |
		return 0;												// | Comprobacion de que exista
	}

	// Cargamos la imagen forzando el numero de canales a 4 (SOIL_LOAD_RGBA)
	int width, height, channels;
	unsigned char* imageData = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	
	if(imageData != NULL){
		std::cout<<"MIS PIXELES SON: "<<std::endl;
		for(int i = 0; i < width*height*4; i++){
			std::cout<<imageData[i]<<std::endl;
		}
	}

	// Comprobamos si hemos cargado la imagen
	if(imageData == NULL) std::cout<<"Could not open file " + path<<std::endl;
	return 0;
}