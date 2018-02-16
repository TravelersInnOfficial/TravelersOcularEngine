#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "TResource.h"

#include "./../Loaders/TObjLoader.h"

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

    //GLfloat* m_verTriangles;
    //GLfloat* m_normTriangles;
    //GLfloat* m_texTriangles;

    //static CVertexBufferObject vboModelData;
    //static UINT uiVAO;
    //static vector <CTexture> tTextures;

    //vector<int> iMeshStartIndices;
    //vector<int> iMeshSizes;
    //vector<int> iMaterialIndices;

    //int iNumMaterials;
    
};

#endif