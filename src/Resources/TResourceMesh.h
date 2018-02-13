#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "TResource.h"

class TResourceMesh: public TResource {

public:
    TResourceMesh();
    ~TResourceMesh();

    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    void loadMesh(std::string);

protected:

private:
    GLfloat* m_vertex;
    GLfloat* m_normals;
    GLfloat* m_textures;
    GLfloat* m_verTriangles;
    GLfloat* m_normTriangles;
    GLfloat* m_texTriangles;

    std::string path;
};

#endif