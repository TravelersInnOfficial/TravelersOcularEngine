#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "./Elements/Particles/TFParticleSystem.h"
#include "./Elements/2DElements/TFSprite.h"
#include "./Elements/2DElements/TFRect.h"
#include "./Elements/2DElements/TF2DText.h"
#include "./Elements/TFCamera.h"
#include "./Elements/TFLight.h"
#include "./Elements/TFRoom.h"
#include "./Elements/TFMesh.h"
#include "./Elements/TFDome.h"
#include "./Elements/TFAnimation.h"

#include <glm/mat4x4.hpp>
#include <TOEvector2d.h>
#include <glm/vec3.hpp>
#include <vector>

// Forward declaration
#include <GL/glew.h>
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
     * @param position (TOEvector3df)
     * @param rotation (TOEvector3df)
     * @param perspective (bool)
     * @return TFCamera* NewCamera
     */
    TFCamera* AddCamera(TOEvector3df position = TOEvector3df(0,0,0), TOEvector3df rotation = TOEvector3df(0,0,0), bool perspective = true);

    /**
     * @brief Adds a new Light to the scene tree
     * 
     * @param position (TOEvector3df)
     * @param rotation (TOEvector3df)
     * @param color (TOEvector4df)
     * @param attenuation (float)
     * @return TFLight* NewLight
     */
    TFLight* AddLight(TOEvector3df position = TOEvector3df(0,0,0), TOEvector3df rotation = TOEvector3df(0,0,0), TOEvector4df color = TOEvector4df(1,1,1,1), float attenuation = 0.05f);

    /**
     * @brief Adds a new Mesh to the scene tree
     * 
     * @param position (TOEvector3df)
     * @param rotation (TOEvector3df)
     * @param scale (TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewMesh
     */
    TFMesh* AddMesh(TOEvector3df position = TOEvector3df(0,0,0), TOEvector3df rotation = TOEvector3df(0,0,0), TOEvector3df scale = TOEvector3df(1.0f,1.0f,1.0f), std::string meshPath = "");

    /**
     * @brief Adds a Dome/Skybox to the scene tree
     * 
     * @param position (TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewDome
     */
    TFDome* AddDome(TOEvector3df position = TOEvector3df(0.0f,0.0f,0.0f), std::string texturePath = "");

    /**
     * @brief Adds a Dome/Skybox to the scene tree
     * 
     * @param position (TOEvector3df)
     * @param meshPath (std::string)
     * @return TFMesh* NewDome
     */
    TFAnimation* AddAnimation(TOEvector3df position = TOEvector3df(0.0f,0.0f,0.0f), TOEvector3df rotation = TOEvector3df(0,0,0), TOEvector3df scale = TOEvector3df(1.0f,1.0f,1.0f));

    /**
     * @brief Adds a 2d rectangle to the screen
     * 
     * @param position 
     * @param size 
     * @param rotation 
     * @return TFRect* 
     */
    TFRect* Add2DRect(TOEvector2df position, TOEvector2df size, float rotation);

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
    TFSprite* AddSprite(std::string texture, TOEvector2df position, TOEvector2df size);
    
    /**
     * @brief Adds 2D text to the screen
     * 
     * @param text 
     * @param position 
     * @return TF2DText* 
     */
    TF2DText* Add2DText(std::string text, TOEvector2df position);

    /**
     * @brief Adds a Particle System in the scene
     * 
     * @param position  (TOEvector3df)
     * @param rotation  (TOEvector3df)
     * @param scale     (TOEvector3df)
     * 
     * @return TFParticleSystem* 
     */
    TFParticleSystem* AddParticleSystem(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale);

    /**
     * @brief Adds a Room in the Scene
     * 
     * @param position  (TOEvector3df)   Position of the Room
     * @param rotation  (TOEvector3df)   Rotation of the Room
     * @param scale     (TOEvector3df)   Size of the Room
     * 
     * @return          (TFRoom*)                   The Room Created
     */
    TFRoom* AddRoom(TOEvector3df position = TOEvector3df(0.0f, 0.0f, 0.0f), TOEvector3df rotation = TOEvector3df(0.0f, 0.0f, 0.0f), TOEvector3df scale = TOEvector3df(1.0f, 1.0f, 1.0f));

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
     * @brief      Delete the Room given
     *
     * @return     true The mesh has been deleted
     * @return     false The mesh couldn't be deleted
     */
    bool DeleteRoom(TFNode*);

    /**
     * @brief Sets the Ambient Light
     * 
     * @param ambientLight 
     */
    void SetAmbientLight(TOEvector3df ambientLight);

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
     * @brief Get the Ambient Light object
     * 
     * @return TOEvector3df 
     */
    TOEvector3df GetAmbientLight();

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
     * @brief TODO: finish comment
     * 
     */
    void InitScene();

    /**
     * @brief TODO: finish comment
     * 
     */
    void Update();
    
    /**
     * @brief TODO: finish comment
     * 
     */
    void Draw();

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
    void Draw2DElements();

    void DrawBkg2DElements();

    /**
     * @brief TODO: finish comment
     * 
     */
    void DrawBoundingBoxes(bool draw);
    
    /**
     * @brief TODO: finish comment
     * 
     */
    void DrawLine(TOEvector3df start, TOEvector3df end, TOEvector3df color);

    /**
     * @brief TODO: finish comment
     * 
     */
    void ResetManager();

    bool AddDynamicLight(TFLight*);
    
    void SetClipping(bool value);
    void PushToBkg(TFDrawable*);
    void PushToFront(TFDrawable*);

    void ChangeShader(SHADERTYPE shader, ENTITYTYPE entity);

    void DrawRooms();
    int SendRoomLights(int value);
    void UpdateCurrentRoom();
    bool Light2Room(TFNode* node);
    void DeleteRoomLight(TFNode* light);


private:
    GLuint m_vao;
    GLuint m_fbo;
    GLuint m_shadowMap;
    
    TNode* m_SceneTreeRoot;                         // Root of the scene
    std::vector<TFRoom*>        m_rooms;            // Rooms in the scene  
    int                         m_currentRoom;      // Current room of the Camera
    std::vector<TFLight*>       m_lightRooms;       // Lights of the rooms

    std::vector<TFCamera*>      m_cameras;          // Pointers to the cameras created
    std::vector<TFLight*>       m_lights;           // Pointers to the lights created
    std::vector<TFLight*>       m_dynamicLights;    // Lights that emit shadows
    std::vector<TFNode*>        m_objects;          // Pointers to the nodes created
    std::vector<TFDrawable*>    m_2Delems;
    std::vector<TFDrawable*>    m_bkg2Delems;

    glm::vec3 m_ambientLight;
    TFCamera* m_main_camera;
    TFDome* m_dome;

    void RecalculateLightPosition();
    void SendLights();
    void SendLightsToShader();
    void DrawSceneShadows();
    void DrawAllLines(); 
    std::vector<GLfloat> vertexVector; 

    void ClearElements();
};
#endif