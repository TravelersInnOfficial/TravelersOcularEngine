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

	// Cargamos la textura
	GLuint toRet = SOIL_load_OGL_texture(
							path.c_str(),
							SOIL_LOAD_AUTO,
							SOIL_CREATE_NEW_ID,
							SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT
						);

	if(toRet == 0){

		toRet =	SOIL_load_OGL_HDR_texture(
					path.c_str(),
					SOIL_HDR_RGBdivA2,
					0,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS
				);

	}

	// Devolvemos el handler de la textura
	if(toRet == 0) std::cout<<"Could not open file " + path<<std::endl;
	return toRet;
}