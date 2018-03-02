#ifndef TFTEXT_H
#define TFTEXT_H

#include <TOEvector4d.h>
#include "TFNode.h"

class TFText: public TFNode{
	friend class TFNode;
public:

	void SetText(std::string text);

protected:
	TFText(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(0, 0, 0),
		std::string text = "",
		std::string texture = ""
	);

	~TFText();
	
};

#endif