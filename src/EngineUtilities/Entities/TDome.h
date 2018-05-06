#ifndef TDOME_H
#define TDOME_H

#include "TMesh.h"

class TDome: public TMesh{
public:
	TDome(std::string texturePath = "");
	~TDome();

	virtual void BeginDraw() override;
	virtual void EndDraw() override;
	virtual void DrawShadow() override;

private:
	/**
	 * @brief Send to shader all vertex and texture
	 * 
	 */
	void SendShaderData();

	bool m_drawingShadows;

};

#endif