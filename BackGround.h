#ifndef _HelloWorld_BackGround_
#define  _HelloWorld_BackGround_
#include "cocos2d.h"

USING_NS_CC;

class Background :public Node
{
protected:
	Sprite* _backgorund;

public:
	Background();
	virtual ~Background();

	CREATE_FUNC(Background);
	virtual bool init();
	virtual void update(float t);
};

#endif