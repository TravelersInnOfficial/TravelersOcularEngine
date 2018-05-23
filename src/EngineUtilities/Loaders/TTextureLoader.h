#ifndef TTEXTURELOADER_H
#define TTEXTURELOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>

#include "./../Resources/TResourceTexture.h"

class TTextureLoader{
public:
	/**
	 * @brief	- Cargamos la textura haciendo uso de la libreria Soil 
	 * 
	 * @param 	- path - Ruta hasta la textura
	 * @param 	- char - Informacion de la textura
	 * @param 	- width - Ancho de la textura
	 * @param 	- height - Altura de la textura
	 * @return 	- bool - Se ha cargado correctamene la imagen
	 */
	static bool LoadTexture(std::string path, unsigned char** imageData, int* width, int* height);
	
	/**
	 * @brief - Cargamos la textura haciendo uso de un cargador binario
	 * 
	 * @param 	- path - Ruta hasta la textura
	 * @param 	- imageData - Informacion de la textura
	 * @param 	- width - Ancho de la textura
	 * @param 	- height - Altura de la textura
	 * @return 	- bool - Se ha cargado correctamente la imagen
	 */
	static bool LoadTextureBinary(std::string path,  std::vector<unsigned char>* imageData, int* width, int* height);
private:
	
};

#endif