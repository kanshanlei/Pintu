#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackGround.h"
#include "UserData.h"
USING_NS_CC;
class StartScene:public Layer
{
protected:
	Background* _background;
	Sprite* _title;
	ui::Button *_startBtn;
	ui::Button *_scoreBtn;
	ui::Button *_aboutBtn;
	ui::Button *_endBtn;
	cocos2d::MenuItemImage *_turnOn, *_turnOff;
	void menuMusicCallback(cocos2d::Ref* pSender);
	bool isPause;
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	virtual bool init();
	static Scene* createScene();
};

