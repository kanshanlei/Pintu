#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "LevelData.h"
#include "SimpleAudioEngine.h"
#include "CuttingPhotos.h"
#include "CallbackTimeCounter.h"
#include "Pause.h"
#include "SceneMediator.h"
#include "ScoreTimer.h"
#include "ui/cocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;

class HelloWorld : public cocos2d::Layer
{
protected:
	float _angle;

	cocos2d::Vec2 _direction;

	bool isPause;
	int _nowLevel;
	int _allLevel;
	std::vector<LevelData> _levelDataList;
	LevelData _nowLevelData;

	CuttingPhotos* photo;
	ui::Button* _pauseButton;

	ScoreTimer* timer;
	void initLevelDataList();

	void initUI();
public:
	~HelloWorld();
    static cocos2d::Scene* createScene();//根据关卡创建

    virtual bool init();
//	virtual bool initWithLevelData(LevelData* leveldata);
    // a selector callback
	virtual void nextLevel();
	void gameOver();
    void menuMusicCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);//默认创建法
};

#endif // __HELLOWORLD_SCENE_H__
