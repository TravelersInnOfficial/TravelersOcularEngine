// PROVISONAL INCLUDES
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"
#include "Resources/Program.h"
#include "Entities/TCamera.h"
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TResourceManager.h"
#include "Resources/TResourceMesh.h"
#include "TOcularEngine/TOcularEngine.h"

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::vector2df(800,600));

	VDriv->SetClearScreenColor(toe::core::vector4df(0.7, 0.7, 1, 1));
	while(VDriv->Update()){
		VDriv->Draw();
	}

    return EXIT_SUCCESS;
}