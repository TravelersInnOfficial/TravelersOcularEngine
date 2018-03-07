#ifndef TRESOURCETEXTURE_H
#define TRESOURCETEXTURE_H

#include "TResource.h"

// Forward declaration
typedef unsigned int GLuint;

class TResourceTexture: public TResource {

public:
    TResourceTexture();
    TResourceTexture(std::string name);
    ~TResourceTexture();

    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();

    GLuint GetTextureId();
    int GetWidth();
    int GetHeight();

private:
    unsigned char* m_imageData;
    int m_width;
    int m_height;
    bool m_loaded;
    GLuint m_textureID;

};

#endif