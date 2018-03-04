#ifndef TFTEXT_H
#define TFTEXT_H

#include <TOEvector4d.h>
#include "TFNode.h"

class TFText: public TFNode{
	friend class TFNode;
public:

	void SetText(std::string text);
	void SetSize(float charSize);

protected:
	TFText(
		toe::core::TOEvector3df position,
		toe::core::TOEvector3df rotation,
		toe::core::TOEvector3df scale,
		std::string text,
		float charSize,
		std::string texture
	);

	~TFText();
	
};

#endif