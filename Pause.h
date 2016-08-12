#include <stdio.h>
#include "cocos2d.h"
#include <functional>

USING_NS_CC;


class Pause :public Layer
{
protected:
	std::function<void()> _continueCallback;
	std::function<void()> _endGameCallback;


public:


	Pause();
	virtual ~Pause();

	CREATE_FUNC(Pause);

	virtual bool init();

	virtual void registerCallback(std::function<void()> continueCallback, std::function<void()> endGameCallback);
};
