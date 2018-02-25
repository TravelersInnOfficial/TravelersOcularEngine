#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "./Elements/TFCamera.h"
#include "./Elements/TFLight.h"
#include "./Elements/TFMesh.h"

#include <vector>

class SceneManager{
public:
    /**
     * @brief Scene Manager constructor
     * 
     */
    SceneManager();

    /**
     * @brief SceneManager destructor
     * 
     */
    ~SceneManager();

    /**
     * @brief Adds a new camera to the scene tree
     * 
     * @param position (toe::core::vector3df)
     * @param rotation (toe::core::vector3df)
     * @param perspective (bool)
     * @return TFCamera* NewCamera
     */
    TFCamera*   AddCamera(toe::core::vector3df position, toe::core::vector3df rotation, bool perspective);

    /**
     * @brief Adds a new Light to the scene tree
     * 
     * @param position (toe::core::vector3df)
     * @param rotation (toe::core::vector3df)
     * @param color (toe::core::vector4df)
     * @param intensity (float)
     * @return TFLight* NewLight
     */
    TFLight*    AddLight(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector4df color, float intensity);

    /**
     * @brief Adds a new Mesh to the scene tree
     * 
     * @param position (toe::core::vector3df)
     * @param rotation (toe::core::vector3df)
     * @param scale (toe::core::vector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewMesh
     */
    TFMesh*     AddMesh(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector3df scale, std::string meshPath);

    /**
     * @brief Deletes the Camera given
     * 
     * @return true The camera has been deleted
     * @return false The camera couldn't be deleted
     */
    bool        DeleteCamera(TFCamera*);

    /**
     * @brief Deletes the Light given
     * 
     * @return true The light has been deleted
     * @return false The light couldn't be deleted
     */
    bool        DeleteLight(TFLight*);

    /**
     * @brief Deletes the Mesh given
     * 
     * @return true The mesh has been deleted
     * @return false The mesh couldn't be deleted
     */
    bool        DeleteMesh(TFMesh*);

    void Update();

    void InitScene();

    void Draw();

    TNode* GetRootNode();

private:
    TNode* m_SceneTreeRoot;

    GLuint vao;
    Program* program;

    std::vector<TFCamera*> m_cameras; //Pointers to the cameras created
    std::vector<TFLight*> m_lights; //Pointers to the lights created

    TFCamera* main_camera;

    glm::mat4 GetTransformInTree(TNode* node);
};
#endif