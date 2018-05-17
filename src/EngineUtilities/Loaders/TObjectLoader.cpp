#include "TObjectLoader.h"
#include "TMaterialLoader.h"
#include "./../TResourceManager.h"

//Headers to load models
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

// VBO = VERTEX BUFFER OBJECT

bool PackedVertex::operator<(const PackedVertex that) const{
	return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
};

bool TObjectLoader::GetSimilarVertexIndex_fast(PackedVertex* packed, std::map<PackedVertex,unsigned int>* VertexToOutIndex, unsigned int* result){
	std::map<PackedVertex,unsigned int>::iterator it = VertexToOutIndex->find(*packed);
	bool output = false;
	if ( it == VertexToOutIndex->end() ){
		output = false;
	}else{
		*result = it->second;
		output = true;
	}
	return output;
}

void TObjectLoader::IndexVBO(TResourceMesh* mesh, std::vector<glm::vec3>* vertexVec, std::vector<glm::vec2>* uvVec, std::vector<glm::vec3>* normalVec, std::vector<unsigned int>* indexVec){
	std::map<PackedVertex, unsigned int> VertexToOutIndex;
	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_uvs;

	// Copio los vectores que han pasado en otros temporales
	temp_vertices.insert	(temp_vertices.begin(), 	vertexVec->begin(), 	vertexVec->end());
	temp_uvs.insert			(temp_uvs.begin(), 			uvVec->begin(), 		uvVec->end());
	temp_normals.insert		(temp_normals.begin(), 		normalVec->begin(), 	normalVec->end());

	// Una vez copiados los valores, procedo a vaciar los pasados por parametros
	vertexVec->clear();
	uvVec->clear();
	normalVec->clear();
	indexVec->clear();
	// For each input vertex
	int size = temp_vertices.size();
	for ( unsigned int i=0; i<size; i++ ){

		PackedVertex packed = {temp_vertices[i], temp_uvs[i], temp_normals[i]};
	
			// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = GetSimilarVertexIndex_fast(&packed, &VertexToOutIndex, &index);

		if (found){ // A similar vertex is already in the VBO, use it instead !
			indexVec->push_back(index);
		}else{ // If not, it needs to be added in the output data.
			vertexVec->push_back(temp_vertices[i]);
			uvVec->push_back(temp_uvs[i]);			
			normalVec->push_back(temp_normals[i]);
			unsigned int newindex = (unsigned int)vertexVec->size() - 1;
			indexVec->push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

bool TObjectLoader::LoadBoundingBox(TResourceMesh* mesh, std::vector<glm::vec3>* vertexVec){
	float min_x, max_x, min_y, max_y, min_z, max_z; 

	min_x = max_x = vertexVec->at(0).x;	
	min_y = max_y = vertexVec->at(0).y;
	min_z = max_z = vertexVec->at(0).z;
	
	int size = vertexVec->size();
	for (int i = 0; i < size; i++) {
		if (vertexVec->at(i).x < min_x) min_x = vertexVec->at(i).x;
		if (vertexVec->at(i).x > max_x) max_x = vertexVec->at(i).x;
		if (vertexVec->at(i).y < min_y) min_y = vertexVec->at(i).y;
		if (vertexVec->at(i).y > max_y) max_y = vertexVec->at(i).y;
		if (vertexVec->at(i).z < min_z) min_z = vertexVec->at(i).z;
		if (vertexVec->at(i).z > max_z) max_z = vertexVec->at(i).z;
	}

	glm::vec3 sizeV = glm::vec3(max_x-min_x, max_y-min_y, max_z-min_z);
	glm::vec3 center = glm::vec3((min_x+max_x)/2.0f, (min_y+max_y)/2.0f, (min_z+max_z)/2.0f);

	mesh->SetSize(sizeV);
	mesh->SetCenter(center);

	return true;
}

bool TObjectLoader::LoadObj(TResourceMesh* mesh, int option){
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normal;
	std::vector<unsigned int> index;

	bool loaded = false;
	switch(option){
		case 0:
			loaded = LoadObjFromFileAssimp(mesh, &vertex, &uv, &normal);
			break;
		case 1:
			loaded = LoadObjFromFileCustom(mesh, &vertex, &uv, &normal);
			break;
		default:
			std::cout<<"La opcion a la que intenta acceder no existe. Opcion: "<<option<<std::endl;
	}

	if(!loaded){
		return false;
	}


	IndexVBO(mesh, &vertex, &uv, &normal, &index);

	// Cargamos el buffer de vertices
	GLuint currentBuffer = mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size()*sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
	//glBufferStorage(GL_ARRAY_BUFFER, vertex.size()*sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	// Cargamos el buffer de uvs
	currentBuffer = mesh->GetUvBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size()*sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
	
	// Cargamos el buffer de normales
	currentBuffer = mesh->GetNormalBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
	glBufferData(GL_ARRAY_BUFFER, normal.size()*sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

	// Cargamos el buffer de elementos
	currentBuffer = mesh->GetElementBuffer();
	mesh->SetElementSize(index.size());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()*sizeof(unsigned int), &index[0], GL_STATIC_DRAW);

	LoadBoundingBox(mesh, &vertex);

	return true;
}

// ============================================================================================================================================
//
// BINARY
//
// ============================================================================================================================================

/*
	1º  SIZE 	- 3 FLOATS, SIZE
	2º  CENTER	- 3 FLOATS, CENTER
	3º  INT 	- SIZE DE VERTICES (3*SIZE = TOTAL FLOATS)
	4º  FLOAT 	- VERTICES
	5º  INT  	- SIZE DE UVS (2*SIZE = TOTAL FLOATS)
	6º  FLOAT 	- UVS
	7º  INT 	- SIZE DE NORMALES (3*SIZE = TOTAL FLOATS)
	8º  FLOAT 	- NORMALES	
	9º  INT 	- SIZE DE ELEMENTOS
	10º UINT	- ELEMENTOS
	11º INT		- SIZE DEL STRING DE TEXTURA
	12º CHAR	- CADA CHAR DEL STRING
	13º INT		- SIZE DEL STRING DEL NORMAL MAP
	14º CHAR	- CADA CHAR DEL STRING
	15º INT 	- SIZE DEL STRING DEL SPECULAR MAP
	16º CHAR	- CADA CHAR DEL STRING
	17º INT		- SIZE DEL STRING DE MATERIAL
	18º CHAR	- CADA CHAR DEL STRING
*/

bool TObjectLoader::LoadObjBinary(TResourceMesh* mesh){

	bool output = false;

	std::string objPath = mesh->GetName();

	std::ifstream objFile;
	objFile.open(objPath, std::ios::binary);

	if(objFile.is_open()){

		std::vector<glm::vec3> vertex;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> normal;
		std::vector<unsigned int> index;

		// -------------------------------------------------------------- 1º
		glm::vec3 vecRead;
		objFile.read(reinterpret_cast<char*>(&vecRead.x), sizeof(float));  
		objFile.read(reinterpret_cast<char*>(&vecRead.y), sizeof(float));
		objFile.read(reinterpret_cast<char*>(&vecRead.z), sizeof(float));
		mesh->SetSize(vecRead);

		// -------------------------------------------------------------- 2º
		objFile.read(reinterpret_cast<char*>(&vecRead.x), sizeof(float));  
		objFile.read(reinterpret_cast<char*>(&vecRead.y), sizeof(float));
		objFile.read(reinterpret_cast<char*>(&vecRead.z), sizeof(float));
		mesh->SetCenter(vecRead);
		// -------------------------------------------------------------- 3º
		int size;
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 4º
			// vertices
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&vecRead.x), sizeof(float));  
			objFile.read(reinterpret_cast<char*>(&vecRead.y), sizeof(float));
			objFile.read(reinterpret_cast<char*>(&vecRead.z), sizeof(float));
			vertex.push_back(vecRead);
		}
		// -------------------------------------------------------------- 5º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 6º
			// uvs
			glm::vec2 vecRead2;
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&vecRead2.x), sizeof(float));  
			objFile.read(reinterpret_cast<char*>(&vecRead2.y), sizeof(float));
			uv.push_back(vecRead2);
		}
		// -------------------------------------------------------------- 7º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 8º
			//normales
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&vecRead.x), sizeof(float));  
			objFile.read(reinterpret_cast<char*>(&vecRead.y), sizeof(float));
			objFile.read(reinterpret_cast<char*>(&vecRead.z), sizeof(float));
			normal.push_back(vecRead);
		}
		// -------------------------------------------------------------- 9º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 10º
			// elementos
		unsigned int element;
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&element), sizeof(unsigned int));  
			index.push_back(element);
		}
		// -------------------------------------------------------------- 11º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 12º
			// path textura
		std::string path;
		char currentChar;
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&currentChar), sizeof(char));
			path.push_back(currentChar);
		}
		if(size>0){
			TResourceTexture* texture = TResourceManager::GetInstance()->GetResourceTexture(path);
			if(texture != nullptr){
				mesh->AddTexture(texture);
			}
		}
		// -------------------------------------------------------------- 13º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 14º
			// path normal_map
		path.clear();
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&currentChar), sizeof(char));
			path.push_back(currentChar);
		}
		if(size>0){
			TResourceTexture* texture = TResourceManager::GetInstance()->GetResourceTexture(path);
			if(texture != nullptr){
				mesh->AddBumpMap(texture);
			}
		}
		// -------------------------------------------------------------- 15º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 16º
			// path specular_map
		path.clear();
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&currentChar), sizeof(char));
			path.push_back(currentChar);
		}
		if(size>0){
			TResourceTexture* texture = TResourceManager::GetInstance()->GetResourceTexture(path);
			if(texture != nullptr){
				mesh->AddSpecularMap(texture);
			}
		}
		// -------------------------------------------------------------- 17º
		objFile.read(reinterpret_cast<char*>(&size), sizeof(int));
		// -------------------------------------------------------------- 18º
			// path material
		path.clear();
		for(int i=0; i<size; i++){
			objFile.read(reinterpret_cast<char*>(&currentChar), sizeof(char));
			path.push_back(currentChar);
		}
		TMaterialLoader::LoadMaterial(path, objPath, mesh);

		// -------------------------------------------------------------- RELLENAR BUFFERS
		// Cargamos el buffer de vertices
		GLuint currentBuffer = mesh->GetVertexBuffer();
		glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex.size()*sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

		// Cargamos el buffer de uvs
		currentBuffer = mesh->GetUvBuffer();
		glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
		glBufferData(GL_ARRAY_BUFFER, uv.size()*sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
		
		// Cargamos el buffer de normales
		currentBuffer = mesh->GetNormalBuffer();
		glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
		glBufferData(GL_ARRAY_BUFFER, normal.size()*sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

		// Cargamos el buffer de elementos
		currentBuffer = mesh->GetElementBuffer();
		mesh->SetElementSize(index.size());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()*sizeof(unsigned int), &index[0], GL_STATIC_DRAW);

		output = true;
	}else{
		std::cout<<"Error al abrir el archivo: "<<objPath<<std::endl;
	}

	objFile.close();
	return output;
}

// ============================================================================================================================================
//
// ASSIMP
//
// ============================================================================================================================================

bool TObjectLoader::LoadObjAssimp(TResourceMesh* mesh){
	return LoadObj(mesh, 0);
}

bool TObjectLoader::LoadObjFromFileAssimp(TResourceMesh* mesh, std::vector<glm::vec3>* vertexVec, std::vector<glm::vec2>* uvVec, std::vector<glm::vec3>* normalVec){

	std::string path = mesh->GetName(); 
	
	std::ifstream file(path);									// |
	if(!file.fail()) file.close();								// |
	else{														// |
		std::cout<<"File not found " + path<<std::endl;			// |
		return false;											// | Comprobacion de que exista
	}

	const struct aiScene* scene = nullptr;
	Assimp::Importer importer;
	scene = importer.ReadFile(path.c_str(),  aiProcessPreset_TargetRealtime_Fast | aiProcess_ConvertToLeftHanded);
	
	if(!scene){													// |
		std::cout<<"Could not open file " + path<<std::endl;	// |
		return false;											// | Comprobacion de que se lea bien
	}

	// Recorremos todos los MESHES de la ESCENA
	for(int i = 0; i < scene->mNumMeshes; i++){
		aiMesh* meshCustom = scene->mMeshes[i]; 					// Cogemos el MESH a tratar
		int iMeshFaces = meshCustom->mNumFaces; 					// Guardamos el NUMERO DE CARAS
		for(int j = 0; j < iMeshFaces ;j++){				// Iteramos por las CARAS
			const aiFace& face = meshCustom->mFaces[j];			// Nos guardamos la cara que estamos tratando
			if(face.mNumIndices == 3){
				for(int k = 0; k < 3 ;k++){
					aiVector3D pos = meshCustom->mVertices[face.mIndices[k]];			// POSICION DEL VERTICE
					aiVector3D normal = meshCustom->mNormals[face.mIndices[k]];			// NORMAL DEL VERTICE
					aiVector3D uv = meshCustom->mTextureCoords[0][face.mIndices[k]];	// COORDENADA DE TEXTURA
					
					vertexVec->push_back(glm::vec3(pos.x, pos.y, pos.z));				// |		
					uvVec->push_back(glm::vec2(uv.x, uv.y));						// |
					normalVec->push_back(glm::vec3(normal.x, normal.y, normal.z));		// | Lo guardamos para DEVOLVER
				}
			}
		}
	}

	if (scene->HasMaterials()){
		for (unsigned int i = 0; i < scene->mNumMaterials; i++){
			const aiMaterial* material = scene->mMaterials[i];
			aiString texturePath;
			unsigned int numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

			aiString name;
			material->Get(AI_MATKEY_NAME, name);
			TMaterialLoader::LoadMaterial(name.C_Str(), mesh, material);

			// Cargamos las texturas que tenga el modelo
			for(int i = 0; i < numTextures; i++){
					if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS){
						// Treat texture path
						std::string file = std::string(texturePath.C_Str());
						std::string auxPath = path.substr(0,path.find_last_of('/'));
						auxPath = auxPath.substr(0, auxPath.find_last_of('/'));
						//std::string finalPath = auxPath + "/textures/" + file;
						std::string finalPath = auxPath + "/" + file;
						
						// Load texture (But do nothing with it)
						TResourceTexture* texture = TResourceManager::GetInstance()->GetResourceTexture(finalPath);
						if(texture != nullptr){
							mesh->AddTexture(texture);
						}
					}
			}
		}
	}

	return true;
}

// ============================================================================================================================================
//
// CUSTOM
//
// ============================================================================================================================================

bool TObjectLoader::LoadObjCustom(TResourceMesh* mesh){
	return LoadObj(mesh, 1);
}

bool TObjectLoader::LoadObjFromFileCustom(TResourceMesh* mesh, std::vector<glm::vec3>* vertexVec, std::vector<glm::vec2>* uvVec, std::vector<glm::vec3>* normalVec){
	// Creamos algunas variables temporales para cargar el obj
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	// Intentamos leer el archivo, en el caso de que no existiera volvemos
	std::string path = mesh->GetName();
	FILE * file = std::fopen(path.c_str(),"r");
	if( file == nullptr ){
   		std::cout<<"Impossible to open the file !\n";
		return false;
	}

	// Bucle de lectura del archivo, saldremos del bucle a partir de un break
	while(true){

		char lineHeader[128];							// Suponemos que la linea no ocupa mas de 128
		int res = fscanf(file, "%s", lineHeader);	 	// Lee la primera palabra de la línea
		if (res == EOF){ 	// EOF = End Of File, es decir, el final del archivo. Se finaliza el ciclo.
			break; 
		}
		else{				// Analizar el lineHeader
			// Miramos si se trada de un vertice
			if (strcmp(lineHeader, "v") == 0){
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
				temp_vertices.push_back(vertex);
			}
			// Miramos si se trata de un uv
			else if ( strcmp( lineHeader, "vt" ) == 0 ){
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				uv.y = 1.0f - uv.y;
				temp_uvs.push_back(uv);
			}
			// Miramos si se trata de una normal
			else if ( strcmp( lineHeader, "vn" ) == 0 ){
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				temp_normals.push_back(normal);
			}
			// Miramos si se trata de un triangulo
			else if ( strcmp( lineHeader, "f" ) == 0 ){
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9){
					std::cout<<"File can't be read by our simple parser : ( Try exporting with other options\n";
					return false;
				}
				//
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}
	// Una vez ya leido todo el documento y almacenado los valores en datos temporales, procedemos a analizarla
	// Analizamos los vertices
	int size = vertexIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice del vertice
		int vertexIndex = vertexIndices[i];
		// Tenemos que poner el -1 porque los obj empiezan por 1
		glm::vec3 vertex = temp_vertices[vertexIndex-1];
		vertexVec->push_back(vertex);
	}
	// Analizamos los UV
	size = uvIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice del uv
		int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex-1];
		uvVec->push_back(uv);
	}
	// Analizamos las normales
	size = normalIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice de la normal
		int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex-1];
		normalVec->push_back(normal);
	}
	return true;
}