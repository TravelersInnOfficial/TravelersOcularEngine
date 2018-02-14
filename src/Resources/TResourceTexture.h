#ifndef TRESOURCETEXTURE_H
#define TRESOURCETEXTURE_H

#include "TResource.h"

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

private:

};

#endif