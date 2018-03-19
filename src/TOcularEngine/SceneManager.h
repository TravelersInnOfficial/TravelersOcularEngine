#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "./Elements/Particles/TFParticleSystem.h"
#include "./Elements/TFCamera.h"
#include "./Elements/TFLight.h"
#include "./Elements/TFMesh.h"
#include "./Elements/TFDome.h"
#include "./Elements/2DElements/TFRect.h"
#include "./Elements/2DElements/TFSprite.h"
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
    TFCamera* AddCamera(toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0), bool perspective = true);

    /**
     * @brief Adds a new Light to the scene tree
     * 
     * @param position (toe::core::TOEvector3df)
     * @param rotation (toe::core::TOEvector3df)
     * @param color (toe::core::TOEvector4df)
     * @param attenuation (float)
     * @return TFLight* NewLight
     */
    TFLight* AddLight(toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0), toe::core::TOEvector4df color = toe::core::TOEvector4df(1,1,1,1), float attenuation = 0.05f);

    /**
     * @brief Adds a new Mesh to the scene tree
     * 
     * @param position (toe::core::TOEvector3df)
     * @param rotation (toe::core::TOEvector3df)
     * @param scale (toe::core::TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewMesh
     */
    TFMesh* AddMesh(toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f,1.0f,1.0f), std::string meshPath = "");

    /**
     * @brief Adds a Dome/Skybox to the scene tree
     * 
     * @param position (toe::core::TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewDome
     */
    TFDome* AddDome(toe::core::TOEvector3df position = toe::core::TOEvector3df(0.0f,0.0f,0.0f), std::string texturePath = "");

    /**
     * @brief Adds a 2d rectangle to the screen
     * 
     * @param position 
     * @param size 
     * @param rotation 
     * @return TFRect* 
     */
    TFRect* Add2DRect(toe::core::TOEvector2df position, toe::core::TOEvector2df size, float rotation);

    /**
    * @brief Deletes a 2D element from draw vector
    * 
    * @param elem (TFDrawable*)
    */
    void Delete2Delement(TFDrawable* elem);
    
    /**
     * @brief Adds a 2d sprite to the screen
     * 
     * @param texture 
     * @param position 
     * @return TFSprite* 
     */
    TFSprite* AddSprite(std::string texture, toe::core::TOEvector2df position, toe::core::TOEvector2df size);

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
    bool DeleteCamera(TFCamera*);

    /**
     * @brief Deletes the Light given
     * 
     * @return true The light has been deleted
     * @return false The light couldn't be deleted
     */
    bool DeleteLight(TFLight*);

    /**
     * @brief Deletes the Mesh given
     * 
     * @return true The mesh has been deleted
     * @return false The mesh couldn't be deleted
     */
    bool DeleteMesh(TFNode*);

    /**
     * @brief Sets the Ambient Light
     * 
     * @param ambientLight 
     */
    void SetAmbientLight(toe::core::TOEvector3df ambientLight);

    /**
     * @brief Get the Ambient Light object
     * 
     * @return toe::core::TOEvector3df 
     */
    toe::core::TOEvector3df GetAmbientLight();

    /**
     * @brief Get the Root Node object
     * 
     * @return TNode* 
     */
    TNode* GetRootNode();

    /**
     * @brief Get the Main Camera object
     * 
     * @return TFCamera* 
     */
    TFCamera* GetMainCamera();

    /**
     * @brief Change the main camera
     * @details If no camera is passed, change to the next available camera
     * 
     * @param camera 
     */
    void ChangeMainCamera(TFCamera* camera = nullptr);

    /**
     * @brief Set the View matrix and the Projection matrix
     */
    void SetMainCameraData();

    /**
     * @brief TODO: finish comment
     * 
     */
    void Update();

    /**
     * @brief TODO: finish comment
     * 
     */
    void InitScene();
    
    /**
     * @brief TODO: finish comment
     * 
     */
    void ResetManager();

    /**
     * @brief TODO: finish comment
     * 
     * @param light 
     * @param num 
     */
    void DrawLight(TFLight* light, int num);
    
    /**
     * @brief TODO: finish comment
     * 
     */
    void Draw();

    /**
     * @brief TODO: finish comment
     * 
     */
    void Draw2DElements();

    /**
     * @brief TODO: finish comment
     * 
     */
    void DrawBoundingBoxes(bool draw);

    void RecalculateLightPosition();
    void SendLights();
    void SetClipping(bool value);

private:
    GLuint m_vao;
    TNode* m_SceneTreeRoot;

    std::vector<TFCamera*>   m_cameras;  // Pointers to the cameras created
    std::vector<TFLight*>    m_lights;   // Pointers to the lights created
    std::vector<TFNode*>     m_objects;  // Pointers to the nodes created
    std::vector<TFDrawable*> m_2Delems;

    glm::vec3 m_ambientLight;
    TFCamera* m_main_camera;
    TFDome* m_dome;

    glm::mat4 GetTransformInTree(TNode* node);
    void ClearElements();
};
#endif