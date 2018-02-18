#include "TObjectLoader.h"
#include "./../TResourceManager.h"

bool LoadObjFromFile();

// VBO = VERTEX BUFFER OBJECT

void TObjectLoader::IndexVBO(TResourceMesh* mesh){
	std::map<PackedVertex, unsigned int> VertexToOutIndex;
	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_uvs;
	
	// Conseguimos un puntero a los vectores del mesh
	std::vector<glm::vec3>* out_vertices = mesh->GetVertexVector();
	std::vector<glm::vec2>* out_uvs = mesh->GetUvVector();
	std::vector<glm::vec3>* out_normals = mesh->GetNormalVector();

	// Copio los vectores que han pasado en otros temporales
	temp_vertices.insert	(temp_vertices.begin(), 	out_vertices->begin(), 	out_vertices->end());
	temp_uvs.insert			(temp_uvs.begin(), 			out_uvs->begin(), 		out_uvs->end());
	temp_normals.insert		(temp_normals.begin(), 		out_normals->begin(), 	out_normals->end());

	// Una vez copiados los valores, procedo a vaciar los pasados por parametros
	mesh->ClearVertex();
	mesh->ClearUv();
	mesh->ClearNormal();

	// For each input vertex
	int size = temp_vertices.size();
	for ( unsigned int i=0; i<size; i++ ){

		PackedVertex packed = {temp_vertices[i], temp_uvs[i], temp_normals[i]};
		
		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = GetSimilarVertexIndex_fast(&packed, &VertexToOutIndex, &index);

		if (found){ // A similar vertex is already in the VBO, use it instead !
			mesh->AddVertexIndex(index);
		}else{ // If not, it needs to be added in the output data.
			mesh->AddVertex(temp_vertices[i]);
			mesh->AddUv(temp_uvs[i]);			
			mesh->AddNormal(temp_normals[i]);
			unsigned int newindex = (unsigned int)out_vertices->size() - 1;
			mesh->AddVertexIndex(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

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

// ============================================================================================================================================
//
// ASSIMP
//
// ============================================================================================================================================

bool TObjectLoader::LoadObjAssimp(TResourceMesh* mesh){
	if(!LoadObjFromFileAssimp(mesh)){
		return false;
	}
	IndexVBO(mesh);
	return true;
}

bool TObjectLoader::LoadObjFromFileAssimp(TResourceMesh* mesh){
	std::string path = mesh->GetName();
	std::ifstream file(path);									// |
	if(!file.fail()) file.close();								// |
	else{														// |
		std::cout<<"File not found " + path<<std::endl;			// |
		return false;											// | Comprobacion de que exista
	}

	const struct aiScene* scene = NULL;
	Assimp::Importer importer;
	scene = importer.ReadFile(path.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	
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
			for(int k = 0; k < 3 ;k++){
				aiVector3D pos = meshCustom->mVertices[face.mIndices[k]];			// POSICION DEL VERTICE
				aiVector3D normal = meshCustom->mNormals[face.mIndices[k]];		// NORMAL DEL VERTICE
				aiVector3D uv = meshCustom->mTextureCoords[0][face.mIndices[k]];	// COORDENADA DE TEXTURA
				
				mesh->AddVertex(glm::vec3(pos.x, pos.y, pos.z));					// |
				mesh->AddUv(glm::vec2(uv.x, uv.y));									// |
				mesh->AddNormal(glm::vec3(normal.x, normal.y, normal.z));			// | Lo guardamos para DEVOLVER
			}
		}
	}

	if (scene->HasMaterials()){
		for (unsigned int i = 0; i < scene->mNumMaterials; i++){
			const aiMaterial* material = scene->mMaterials[i];
			aiString texturePath;
			unsigned int numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);
			for(int i = 0; i < numTextures; i++){
				if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
					if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS){
						// Treat texture path
						std::string file = std::string(texturePath.C_Str());
						std::string auxPath = path.substr(0,path.find_last_of('/'));
						auxPath = auxPath.substr(0, auxPath.find_last_of('/'));
						std::string finalPath = auxPath + "/textures/" + file;
						
						// Load texture (But do nothing with it)
						TResourceManager::GetInstance()->GetResourceTexture(finalPath);
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
	if(!LoadObjFromFileCustom(mesh)){
		return false;
	}
	IndexVBO(mesh);
	return true;
}

bool TObjectLoader::LoadObjFromFileCustom(TResourceMesh* mesh){
	// Creamos algunas variables temporales para cargar el obj
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	// Intentamos leer el archivo, en el caso de que no existiera volvemos
	std::string path = mesh->GetName();
	FILE * file = std::fopen(path.c_str(),"r");
	if( file == NULL ){
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
		mesh->AddVertex(vertex);
	}
	// Analizamos los UV
	size = uvIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice del uv
		int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex-1];
		mesh->AddUv(uv);
	}
	// Analizamos las normales
	size = normalIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice de la normal
		int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex-1];
		mesh->AddNormal(normal);
	}
	return true;
}