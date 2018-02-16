#include "TAssimpLoader.h"

// VBO = VERTEX BUFFER OBJECT

bool TAssimpLoader::LoadObj(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals){
    std::ifstream file(path);						// |
    if(!file.fail()) file.close();					// |
    else{											// |
        std::cout<<"Could not open file " + path;	// |
        return false;								// | Comprobacion de que exista
    }

	const struct aiScene* scene = NULL;
	Assimp::Importer importer;
	scene = importer.ReadFile(path.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    
	if(!scene){										// |
        std::cout<<"Could not open file " + path;	// |
        return false;								// | Comprobacion de que se lea bien
    }

	// Recorremos todos los MESHES de la ESCENA
	for(int i = 0; i < scene->mNumMeshes; i++){
		aiMesh* mesh = scene->mMeshes[i]; 					// Cogemos el MESH a tratar
		int iMeshFaces = mesh->mNumFaces; 					// Guardamos el NUMERO DE CARAS
		for(int j = 0; j < iMeshFaces ;j++){				// Iteramos por las CARAS
			const aiFace& face = mesh->mFaces[j];			// Nos guardamos la cara que estamos tratando
			for(int k = 0; k < 3 ;k++){
				aiVector3D pos = mesh->mVertices[face.mIndices[k]];			// POSICION DEL VERTICE
				aiVector3D normal = mesh->mNormals[face.mIndices[k]];		// NORMAL DEL VERTICE
				aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];	// COORDENADA DE TEXTURA
				
				out_vertices->push_back(glm::vec3(pos.x, pos.y, pos.z));			// |
				out_normals->push_back(glm::vec3(normal.x, normal.y, normal.z));	// |
				out_uvs->push_back(glm::vec2(uv.x, uv.y));							// | Lo guardamos para DEVOLVER
			}
		}
	}

	return true;
}