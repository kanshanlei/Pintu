#pragma once
#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class SceneMediator
{
protected:
	static SceneMediator* _instance;

public:
	static SceneMediator* getInstance();

	virtual void gotoStartScene();

	virtual void gotoGameScene();

	virtual void gotoScoreScene();

	virtual void gotoaboutScene();

};

