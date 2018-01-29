#ifndef TENTITY_H
#define TENTITY_H

class TEntity{
public:
	virtual void	BeginDraw() = 0;
	virtual void 	EndDraw() = 0;
private:
};

#endif