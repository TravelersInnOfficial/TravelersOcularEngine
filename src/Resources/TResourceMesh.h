#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "TResource.h"

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

private:
    //GLfloat* m_vertex;
    //GLfloat* m_normals;
    //GLfloat* m_textures;
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