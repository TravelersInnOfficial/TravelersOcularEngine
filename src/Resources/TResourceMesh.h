#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "TResource.h"

#include "./../Loaders/TObjLoader.h"
#include "./../Loaders/TAssimpLoader.h"

class TResourceMesh: public TResource {

public:
    TResourceMesh();
    TResourceMesh(std::string name);
    ~TResourceMesh();

    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();

    GLuint* GetVertexBuffer();
    GLuint* GetElementBuffer();

private:
    std::vector<glm::vec3> m_vertex;
    std::vector<glm::vec2> m_textures;
    std::vector<glm::vec3> m_normals;
    std::vector<unsigned int> m_vertexIndex;

    GLuint m_vbo;
    GLuint m_ebo;
    
};

#endif