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
     * @param position (toe::core::TOEvector3df)
     * @param rotation (toe::core::TOEvector3df)
     * @param perspective (bool)
     * @return TFCamera* NewCamera
     */
    TFCamera*   AddCamera(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, bool perspective);

    /**
     * @brief Adds a new Light to the scene tree
     * 
     * @param position (toe::core::TOEvector3df)
     * @param rotation (toe::core::TOEvector3df)
     * @param color (toe::core::TOEvector4df)
     * @param intensity (float)
     * @return TFLight* NewLight
     */
    TFLight*    AddLight(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector4df color, float intensity);

    /**
     * @brief Adds a new Mesh to the scene tree
     * 
     * @param position (toe::core::TOEvector3df)
     * @param rotation (toe::core::TOEvector3df)
     * @param scale (toe::core::TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewMesh
     */
    TFMesh*     AddMesh(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale, std::string meshPath);

    /**
     * @brief Deletes the Camera given
     * 
     * @return true The camera has been deleted
     * @return false The camera couldn't be deleted
     */
    bool        DeleteCamera(TFCamera*, bool eraseChildren = true);

    /**
     * @brief Deletes the Light given
     * 
     * @return true The light has been deleted
     * @return false The light couldn't be deleted
     */
    bool        DeleteLight(TFLight*, bool eraseChildren = true);

    /**
     * @brief Deletes the Mesh given
     * 
     * @return true The mesh has been deleted
     * @return false The mesh couldn't be deleted
     */
    bool        DeleteMesh(TFMesh*, bool eraseChildren = true);

    /**
     * @brief Sets the Ambient Light
     */
    void SetAmbientLight(toe::core::TOEvector3df ambientLight);

    void Update();

    void InitScene();

    void DrawLight(TFLight* light, int num);
    void Draw();

    TNode* GetRootNode();

private:
    TNode* m_SceneTreeRoot;

    GLuint vao;
    Program* program;

    std::vector<TFCamera*>  m_cameras;  // Pointers to the cameras created
    std::vector<TFLight*>   m_lights;   // Pointers to the lights created
    std::vector<TFMesh*>    m_meshes;    // Pointers to the nodes created

    glm::vec3 m_ambientLight;
    TFCamera* main_camera;

    glm::mat4 GetTransformInTree(TNode* node);
};
#endif