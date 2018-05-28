#include "TMaterialLoader.h"
#include "./../TResourceManager.h"
#include "./../Resources/TResourceMaterial.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

class TResourceTexture;


void TMaterialLoader::Read3Elements(float* value1, float* value2, float* value3, std::string line){
	std::string token;
	std::string delimiter = " ";

	// Vamos cogiendo el string desde el inicio de la cadena hasta el siguiente espacio
	// Y guardandonos el valor en un float
	// Ademas de acortar el string
	token = line.substr(0, line.find(delimiter));
	line.erase(0, token.length() + delimiter.length());
	*value1 = std::stof(token);

	token = line.substr(0, line.find(delimiter));
	line.erase(0, token.length() + delimiter.length());
	*value2 = std::stof(token);

	token = line.substr(0, line.find(delimiter));
	line.erase(0, token.length() + delimiter.length());
	*value3 = std::stof(token);
}

std::string TMaterialLoader::TreatPath(std::string objPath){
	// Sacamos la posicion del string donde se encuentra la parte .obj
	std::size_t pos = objPath.find(".obj");

	// Eliminamos .obj de la cadena e insertamos .mtl
	objPath.erase(pos, objPath.length()-1);
	objPath = objPath + ".mtl";

	// Devolvemos el path ya tratado
	return objPath;
}

bool TMaterialLoader::LoadMaterial(std::string name, std::string path, TResourceMesh* mesh){
	bool output = false;

	// Comprobamos que el nombre pasado no este ya en nuestra base de datos
	TResourceMaterial* recMaterial = nullptr;
	recMaterial = TResourceManager::GetInstance()->GetResourceMaterial(name);

	// En el caso de haberlo encontrado y este cargado damos el metodo por finalizado
	if(recMaterial->GetLoaded()){output = true;}
	else{
		// Primero de todo calculamos el path para el mtl, en este caso substituimos la parte final
		// del path de .obj a .mtl
		path = TreatPath(path);

		std::ifstream readFile;
		readFile.open(path, std::ifstream::out);

		// Miramos si el archivo se ha abierto correctamente
		if(readFile.is_open()){
			std::string line;

			std::string token;
			std::string mode;
			std::string delimiter = " ";

			// Leemos cada linea del fichero
			while(std::getline(readFile, line)){
				token = line.substr(0, line.find(delimiter));
				line.erase(0, token.length() + delimiter.length());

				// En el caso de encontrarnos # saltamos al siguiente valor
				if(token[0]=='#')continue;
				else mode = token;
				// En caso contrario nos guardamos el valor como token


				// Vamos leyendo cada una de las propiedades del material y a la vez cargando sus valores
				if(mode.compare("newmtl")==0){
					token = line.substr(0, line.find(delimiter));

					// Comprobamos si ya existia un material con el mismo nombre
					// En caso positivo salimos del bucle y se lo pasamos al mesh
					recMaterial = TResourceManager::GetInstance()->GetResourceMaterial(token);
					if(recMaterial->GetLoaded())break;
					else recMaterial->LoadFile();
				}
				else if(recMaterial!=nullptr && mode.compare("Ns")==0){
					token = line.substr(0, line.find(delimiter));

					float value = std::stof(token);
					recMaterial->SetShininess(value);

				}
	  			else if(recMaterial!=nullptr && mode.compare("Ka")==0){
	  				float value1, value2, value3;
	  				Read3Elements(&value1, &value2, &value3, line);

					recMaterial->SetColorAmbient(glm::vec3(value1, value2, value3));
	  			}
	  			else if(recMaterial!=nullptr && mode.compare("Kd")==0){
	  				float value1, value2, value3;
	  				Read3Elements(&value1, &value2, &value3, line);

	  				recMaterial->SetColorDifuse(glm::vec3(value1, value2, value3));
	  			}
	  			else if(recMaterial!=nullptr && mode.compare("Ks")==0){
	  				float value1, value2, value3;
	  				Read3Elements(&value1, &value2, &value3, line);
	  				
					recMaterial->SetColorSpecular(glm::vec3(value1, value2, value3));
	  			}
	  			else if(recMaterial!=nullptr && mode.compare("Ke")==0){
	  				float value1, value2, value3;
	  				Read3Elements(&value1, &value2, &value3, line);

	  				recMaterial->SetColorEmmisive(glm::vec3(value1, value2, value3));
	  			}
	  			else if(recMaterial!=nullptr && mode.compare("Ni")==0){

	  			}
	  			else if(recMaterial!=nullptr && mode.compare("d")==0){

	  			}
	  			else if(recMaterial!=nullptr && mode.compare("illum")==0){

	  			}
			}
			output = true;
		}else{
			//std::cout<<"No se ha encontrado el material: "<<name<<std::endl;
		}
		readFile.close();
	}
	
	mesh->AddMaterial(recMaterial);
	return output;
}

bool TMaterialLoader::LoadMaterial(std::string name, TResourceMesh* mesh, const aiMaterial* material){
	TResourceMaterial* recMaterial = TResourceManager::GetInstance()->GetResourceMaterial(name);

	// Cargamos el material en el caso de que no haya sido cargado antes
	if(!recMaterial->GetLoaded() && material != nullptr){
		//std::cout<<"Cargamos el material: "<<name<<std::endl;

		// Cargamos cada una de las propiedades del material
		aiColor3D  vec3;
		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, vec3))
			recMaterial->SetColorDifuse(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Diffuse: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, vec3))
			recMaterial->SetColorSpecular(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Specular: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, vec3))
			recMaterial->SetColorAmbient(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Ambient: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_EMISSIVE, vec3))
			recMaterial->SetColorEmmisive(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Emissive: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_TRANSPARENT, vec3))
			recMaterial->SetColorTransparent(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Transparent: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		int ivalue;
		if(AI_SUCCESS == material->Get(AI_MATKEY_TWOSIDED, ivalue))
			recMaterial->SetTwoSided(ivalue);
			//std::cout<<"Twosided: "<<ivalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, ivalue))
			recMaterial->SetShadingMode(ivalue);
			//std::cout<<"Shanding Model: "<<ivalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_BLEND_FUNC, ivalue))
			recMaterial->SetBlendFunc(ivalue);
			//std::cout<<"Blend Func: "<<ivalue<<std::endl;

		float fvalue;
		if(AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, fvalue))
			recMaterial->SetOpacity(fvalue);
			//std::cout<<"Opacity: "<<fvalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, fvalue))
			recMaterial->SetShininess(fvalue);
			//std::cout<<"Shininess: "<<fvalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS_STRENGTH, fvalue))
			recMaterial->SetShininessStrength(fvalue);
			//std::cout<<"Shininess Strength: "<<fvalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_REFRACTI, fvalue))
			recMaterial->SetReflact(fvalue);
			//std::cout<<"Refracti: "<<fvalue<<std::endl;
		aiString currentPath;
		if(AI_SUCCESS == material->GetTexture(aiTextureType_SHININESS,0, &currentPath)){}//std::cout<<"Mapa de normales: "<<currentPath.C_Str()<<std::endl;
		if(AI_SUCCESS == material->GetTexture(aiTextureType_HEIGHT, 0, &currentPath)){}//std::cout<<"Mapa de alturas: "<<currentPath.C_Str()<<std::endl;


		// Damos el material como cargado
		recMaterial->LoadFile();
	}
	// Le anyadimos el mateial al mesh
	mesh->AddMaterial(recMaterial);

	return true;
}