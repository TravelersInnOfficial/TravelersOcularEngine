#ifndef TRESOURCEMATERIAL_H
#define TRESOURCEMATERIAL_H

#include "TResource.h"

class TResourceMaterial: public TResource {

public:
    TResourceMaterial(std::string name);
    ~TResourceMaterial();

    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();

private:

};

#endif