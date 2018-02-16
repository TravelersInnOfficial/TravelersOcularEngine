#include "TObjLoader.h"

bool TObjLoader::LoadObj(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals){
	// Creamos algunas variables temporales para cargar el obj
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	// Intentamos leer el archivo, en el caso de que no existiera volvemos
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

			    uvIndices    .push_back(uvIndex[0]);
			    uvIndices    .push_back(uvIndex[1]);
			    uvIndices    .push_back(uvIndex[2]);

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
		out_vertices->push_back(vertex);
	}
	// Analizamos los UV
	size = uvIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice del uv
		int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex-1];
		out_uvs->push_back(uv);
	}
	// Analizamos las normales
	size = normalIndices.size();
	for(int i=0; i<size; i++){
		// Nos guardamos el indice de la normal
		int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex-1];
		out_normals->push_back(normal);
	}
	return true;
}

bool LoadObj( std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals, std::vector<unsigned int>* out_indices){
		// Creamos algunas variables temporales para cargar el obj

	// Intentamos leer el archivo, en el caso de que no existiera volvemos
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
    			out_vertices->push_back(vertex);
			}
			// Miramos si se trata de un uv
    		else if ( strcmp( lineHeader, "vt" ) == 0 ){
			    glm::vec2 uv;
			    fscanf(file, "%f %f\n", &uv.x, &uv.y );
			    out_uvs->push_back(uv);
			}
			// Miramos si se trata de una normal
			else if ( strcmp( lineHeader, "vn" ) == 0 ){
			    glm::vec3 normal;
			    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			    out_normals->push_back(normal);
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
			    out_indices->push_back(vertexIndex[0]);
			    out_indices->push_back(vertexIndex[1]);
			    out_indices->push_back(vertexIndex[2]);

			    //uvIndices    .push_back(uvIndex[0]);
			    //uvIndices    .push_back(uvIndex[1]);
			    //uvIndices    .push_back(uvIndex[2]);

			    //normalIndices.push_back(normalIndex[0]);
			    //normalIndices.push_back(normalIndex[1]);
			    //normalIndices.push_back(normalIndex[2]);
			}
		}
	}
	return true;
}