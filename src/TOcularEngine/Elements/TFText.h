#ifndef TFTEXT_H
#define TFTEXT_H

#include "TFNode.h"
#include <TOEvector4d.h>

class TFText: public TFNode{
	friend class TFNode;
public:

	void SetText(std::string text);
	void SetSize(float charSize);

protected:
	TFText(
		TOEvector3df position,
		TOEvector3df rotation,
		TOEvector3df scale,
		std::string text,
		float charSize,
		std::string texture
	);

	~TFText();
	
};

#endif