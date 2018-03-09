#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "./Elements/TFParticleSystem.h"
#include "./Elements/TFCamera.h"
#include "./Elements/TFLight.h"
#include "./Elements/TFMesh.h"
#include "./Elements/TFDome.h"
#include "./Elements/2DElements/TFRect.h"
#include <TOEvector2d.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

// Forward declaration
typedef unsigned int GLuint;
class Program;

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
     * @param attenuation (float)
     * @return TFLight* NewLight
     */
    TFLight*    AddLight(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector4df color, float attenuation);

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
     * @brief Adds a Dome/Skybox to the scene tree
     * 
     * @param position (toe::core::TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewDome
     */
    TFDome* AddDome(toe::core::TOEvector3df position = toe::core::TOEvector3df(0.0f,0.0f,0.0f), std::string meshPath = "", std::string texturePath = "");

    /**
     * @brief Adds a 2d rectangle to the screen
     * 
     * @param position 
     * @param size 
     * @param rotation 
     * @return TFRect* 
     */
    TFRect*     Add2DRect(toe::core::TOEvector2df size, toe::core::TOEvector2df position, float rotation);
    
    /**
     * @brief Adds a Particle System in the scene
     * 
     * @param position  (toe::core::TOEvector3df)
     * @param rotation  (toe::core::TOEvector3df)
     * @param scale     (toe::core::TOEvector3df)
     * 
     * @return TFParticleSystem* 
     */
    TFParticleSystem* AddParticleSystem(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale);

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
    bool        DeleteMesh(TFNode*);

    /**
     * @brief Sets the Ambient Light
     */
    void SetAmbientLight(toe::core::TOEvector3df ambientLight);

    void Update();

    void InitScene();

    void DrawLight(TFLight* light, int num);
    void Draw();
    void Draw2DElements();

    TNode* GetRootNode();

    
    TFCamera* GetMainCamera();

private:
    GLuint m_vao;
    TNode* m_SceneTreeRoot;

    //Program* m_program;

    std::vector<TFCamera*>  m_cameras;  // Pointers to the cameras created
    std::vector<TFLight*>   m_lights;   // Pointers to the lights created
    std::vector<TFNode*>    m_objects;  // Pointers to the nodes created
    std::vector<TFDrawable*> m_2Delems;

    glm::vec3 m_ambientLight;
    TFCamera* m_main_camera;
    TFDome* m_dome;

    glm::mat4 GetTransformInTree(TNode* node);
};
#endif