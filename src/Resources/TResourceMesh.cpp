#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;
	LoadFile();
}

TResourceMesh::~TResourceMesh(){}

bool TResourceMesh::LoadFile(){

	//if (vboModelData.GetBufferID() == 0) {
	//	vboModelData.CreateVBO();
	//	tTextures.reserve(50);
	//}

	Assimp::Importer importer;
	//Load the scene
	std::cout << m_name << std::endl;
	const aiScene*  scene = importer.ReadFile(m_name,
	aiProcess_CalcTangentSpace 		|
	aiProcess_Triangulate	   		|
	aiProcess_JoinIdenticalVertices |
	aiProcess_SortByPType);

	//Check the scene is loaded
	if (!scene) {
		std::cout << "ERROR: couldn't load model" << std::endl;
	}

	//Total number of vertex
	const int iVertexTotalSize = sizeof(aiVector3D)*2+sizeof(aiVector2D);
	int iTotalVertices = 0;

	//Iterate over all meshes in the scene
	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];	//Current mesh
		//iMaterialIndices.push_back(mesh->mMaterialIndex);
		//int iSizeBefore = vboModelData.GetCurrentSize();
		//iMeshStartIndices.push_back(iSizeBefore/iVertexTotalSize);

		int iMeshFaces = mesh->mNumFaces;	//Number of faces of the current mesh

		//Iterate faces
		for (int j; j < iMeshFaces; j++) {
			const aiFace& face = mesh->mFaces[j];

			//Iterate vertex faces (3 for every face)
			for(int k; k < 3; k++) {
				aiVector3D vertex = mesh->mVertices[face.mIndices[k]];			//Store the vertex
				aiVector3D uv	  = mesh->mTextureCoords[0][face.mIndices[k]];	//Store the uv coords
				aiVector3D normal;								
				//Store the normals
				if (mesh->HasNormals()) {
					normal = mesh->mNormals[face.mIndices[k]];
				} else {
					normal = aiVector3D(1.0f, 1.0f, 1.0f);
				}
				//vboModelData.AddData(&vertex, sizeof(aiVector3D));
				//vboModelData.AddData(&uv, sizeof(aiVector3D));
				//vboModelData.AddData(&normal, sizeof(aiVector3D));	
			}
		}
	}
	return false;
}