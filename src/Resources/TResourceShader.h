#ifndef TRESOURCESHADER_H
#define TRESOURCESHADER_H

#include "TResource.h"

class TResourceShader: public TResource {

public:
    TResourceShader(std::string name);
    ~TResourceShader();

    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();

private:

};

#endif