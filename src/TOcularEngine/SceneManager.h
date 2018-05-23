#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

/**
 * @brief Manages everything inside the scene, meshes, cameras, lights, etc.
 * 
 * @file SceneManager.h
 */

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
    friend class TFRoom;
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
     * @brief       Delete the Animationo given
     * 
     * @return      true - the mesh has been deleted
     * @return      false - the mesh couldn't be deleted
     */
    bool DeleteAnimation(TFNode*);

    /**
     * @brief Sets the Ambient Light
     * 
     * @param ambientLight 
     */
    void SetAmbientLight(TOEvector3df ambientLight);
    
    /**
     * @brief   - Cambia el valor de luz ambiente del juego 
     * 
     * @param   - ambientLight - valor ambiente 
     */
    void SetAmbientLight(float ambientLight);

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
     * @brief   - Inicializa el array de vertices para los objetos
     */
    void InitScene();

    /**
     * @brief   - Hacemos update del de los objetos del motor
     *              como la posicion del Dome que debe moverse con la camara
     * 
     */
    void Update();
    
    /**
     * @brief   - Pinta la escena
     * 
     */
    void Draw();


    /**
     * @brief   - Pinta los elementos 2D
     */
    void Draw2DElements();

    /**
     * @brief   - Pinta los elementos 2D del fondo 
     */
    void DrawBkg2DElements();

    /**
     * @brief   - Des/Activamos el pintar todas las bounding box
     * 
     */
    void DrawBoundingBoxes(bool draw);
    
    /**
     * @brief   - Pintamos una linea 
     * 
     */
    void DrawLine(TOEvector3df start, TOEvector3df end, TOEvector3df color);

    /**
     * @brief   - Reseteamos el arbol de escena
     */
    void ResetManager();
    
    /**
     * @brief De/Active the clipping for the objects of the game
     * 
     * @param value True-Activate / False-Deactivate
     */
    void SetClipping(bool value);

    /**
     * @brief Push the TFDrawable object to the background of the elements
     * 
     * @param  Object Drawable
     */
    void PushToBkg(TFDrawable*);

    /**
     * @brief Push the TFDrawable object to the front of the elements
     * 
     * @param  Object Drawable
     */
    void PushToFront(TFDrawable*);

    /**
     * @brief Change the shader that are using one type of entity
     * 
     * @param shader Shader ENUM
     * @param entity Entity Type
     */
    void ChangeShader(SHADERTYPE shader, ENTITYTYPE entity);

    /**
     * @brief Delete the light from the room
     * 
     * @param light The lights to delete
     */
    void DeleteRoomLight(TFNode* light);

    /**
     * @brief De/Active the sending of ligths to the shader
     * 
     * @param value True - Activate / False - Deactivate
     */
    void SetSendLights(bool value);

        /**
     * @brief Change the light from the sceneRoot to the rooms
     * 
     * @param node - Lights
     * @return True - Done correctly
     */
    bool Light2Room(TFNode* node);

private:
    GLuint m_vao;                                   // m_vao - Buffer de vertices
    
    TNode* m_SceneTreeRoot;                         // m_SceneTreeRoot - Root of the scene
    std::vector<TFRoom*>        m_rooms;            // m_rooms - Rooms in the scene  
    int                         m_currentRoom;      // m_currentRoom - room of the Camera
    std::vector<TFLight*>       m_lightRooms;       // m_lightRooms - Lights of the rooms

    std::vector<TFCamera*>      m_cameras;          // m_cameras - Pointers to the cameras created
    std::vector<TFLight*>       m_lights;           // m_lights - Pointers to the lights created
    std::vector<TFNode*>        m_objects;          // m_objects - Pointers to the nodes created
    std::vector<TFDrawable*>    m_2Delems;          // m_2Delems - Pointers to the 2Delements created
    std::vector<TFDrawable*>    m_bkg2Delems;       // m_bkg2Delems - Pointers to the 2Delements created situated at the background

    glm::vec3 m_ambientLight;   // m_ambientLight - Ambient Light values
    TFCamera* m_main_camera;    // m_main_camera - Pointer to the main camera
    TFDome* m_dome;             // m_dome - Pointer to the dome of the scene
    int m_numshadowlights;      // m_numshadowlights - NUmber of shadow lights
    bool m_sendLights;          // m_sendLights - Send the lights to the shaders?


    /**
     * @brief Draw the elements from the rooms
     */
    void DrawRooms();

    /**
     * @brief Send the lights from the room
     * 
     * @param value the ID from the last light sended to the shader
     * @return the number of lights sended
     */
    int SendRoomLights(int value);

    /**
     * @brief Update the current room of the sceneManager
     */
    void UpdateCurrentRoom();

    /**
     * @brief   - Recalculate all the lights position 
     */
    void RecalculateLightPosition();

    /**
     * @brief   - Recalcular el numero de luces que emiten sombra 
     */
    void RecalculateShadowLightsNumber();

    /**
     * @brief   - Enviamos las luces a los shaders 
     */
    void SendLights();

    /**
     * @brief   - Enviamos las luces al shader actual 
     */
    void SendLightsToShader();

    /**
     * @brief   - Enviamos las luces que emiten sombra al shader actual 
     */
    void SendShadowLightsToShader();

    /**
     * @brief   - Envia al shader la matriz MVP de la luz para calcular la sombra 
     */
    int SendLightMVP();

    /**
     * @brief   - Dibuja las texturas de la sombra 
     */
    void DrawSceneShadows();
    
    /**
     * @brief   - Pinta todas las lineas 
     */
    void DrawAllLines(); 
    std::vector<GLfloat> vertexVector;  // vertexVector - Vertices de las lineas 

    /**
     * @brief   - Eliminamos los elementos del SceneManager 
     */
    void ClearElements();
};
#endif