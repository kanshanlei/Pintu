#pragma once
#include "BackGround.h"
#include<ui/CocosGUI.h>

USING_NS_CC;
class aboutScene :public Layer
{
private:
	Background* _background;
	ui::Button* _backBut;
public:
	aboutScene();
	virtual ~aboutScene();
	CREATE_FUNC(aboutScene);
	virtual bool init();
	static Scene* createScene();
};

