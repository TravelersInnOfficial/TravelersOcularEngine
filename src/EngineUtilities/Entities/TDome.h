#ifndef TDOME_H
#define TDOME_H

#include "TMesh.h"

class TDome: public TMesh{
public:
	TDome(std::string texturePath = "");
	~TDome();

	/**
	 * @brief Draw mesh and send shader data
	 * 
	 */
	void BeginDraw() override;
	
	/**
	 * @brief Empty method overriding mesh one for not drawing dome shadows
	 * 
	 */
	void DrawShadow() override;

private:
	/**
	 * @brief Send to shader all vertex and texture
	 * 
	 */
	void SendShaderData();

};

#endif