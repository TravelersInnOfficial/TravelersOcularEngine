#include "TMaterialLoader.h"
#include "./../TResourceManager.h"
#include "./../Resources/TResourceMaterial.h"

bool TMaterialLoader::LoadMaterial(std::string name, TResourceMesh* mesh, const aiMaterial* material){
	TResourceMaterial* recMaterial = TResourceManager::GetInstance()->GetResourceMaterial(name);

	// Cargamos el material en el caso de que no haya sido cargado antes
	if(!recMaterial->GetLoaded()){
		//std::cout<<"Cargamos el material: "<<name<<std::endl;

		aiColor3D  vec3;
		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, vec3))
			recMaterial->SetColorDifuse(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Diffuse: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, vec3))
			recMaterial->SetColorSpecular(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Specular: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, vec3))
			recMaterial->SetColorAmbient(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Ambient: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_EMISSIVE, vec3))
			recMaterial->SetColorEmmisive(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Emissive: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_COLOR_TRANSPARENT, vec3))
			recMaterial->SetColorTransparent(glm::vec3(vec3.r, vec3.g, vec3.b));
			//std::cout<<"Color Transparent: "<<vec3.r<<" "<<vec3.g<<" "<<vec3.b<<std::endl;

		int ivalue;
		if(AI_SUCCESS == material->Get(AI_MATKEY_TWOSIDED, ivalue))
			recMaterial->SetTwoSided(ivalue);
			//std::cout<<"Twosided: "<<ivalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, ivalue))
			recMaterial->SetShadingMode(ivalue);
			//std::cout<<"Shanding Model: "<<ivalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_BLEND_FUNC, ivalue))
			recMaterial->SetBlendFunc(ivalue);
			//std::cout<<"Blend Func: "<<ivalue<<std::endl;

		float fvalue;
		if(AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, fvalue))
			recMaterial->SetOpacity(fvalue);
			//std::cout<<"Opacity: "<<fvalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, fvalue))
			recMaterial->SetShininess(fvalue);
			//std::cout<<"Shininess: "<<fvalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS_STRENGTH, fvalue))
			recMaterial->SetShininessStrength(fvalue);
			//std::cout<<"Shininess Strength: "<<fvalue<<std::endl;

		if(AI_SUCCESS == material->Get(AI_MATKEY_REFRACTI, fvalue))
			recMaterial->SetReflact(fvalue);
			//std::cout<<"Refracti: "<<fvalue<<std::endl;

		// Damos el material como cargado
		recMaterial->LoadFile();
	}
	mesh->AddMaterial(recMaterial);

	return true;
}