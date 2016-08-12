
#include "StartScene.h"
#include"SceneMediator.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
StartScene::StartScene():
_title(nullptr),
_startBtn(nullptr),
_scoreBtn(nullptr),
_aboutBtn(nullptr)
{
}


StartScene::~StartScene()
{
	
}

bool StartScene::init()
{
	if (Layer::init() == false){ return false; }
	_background = Background::create();
	addChild(_background);
	auto viewSize = Director::getInstance()->getVisibleSize();

	_title = Sprite::create("aipin.png");
	_title->setPosition(viewSize.width / 2, viewSize.height - 100);
	addChild(_title);

	_startBtn = ui::Button::create("start.png");
	_startBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 ));
	addChild(_startBtn);

	_scoreBtn = ui::Button::create("charts.png");
	_scoreBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 -100));
	addChild(_scoreBtn);

	_aboutBtn = ui::Button::create("about.png");
	_aboutBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 200));
	
	addChild(_aboutBtn);

	_endBtn = ui::Button::create("end_game.png");
	_endBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 300));
	addChild(_endBtn);

	_startBtn->addClickEventListener([](Ref* ref){

		SceneMediator::getInstance()->gotoGameScene();

	});
	_scoreBtn->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoScoreScene();
	});
	_aboutBtn->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoaboutScene();
	});
	_endBtn->addClickEventListener([](Ref* ref){
		Director::getInstance()->end();
	});
	// Ìí¼Ó ÉùÒô  µÄ¿ª¹Ø°´Å¥
	auto _turnOn = MenuItemImage::create(
		"button_voi_on.png",
		"button_voi_on.png");
	auto _turnOff = MenuItemImage::create(
		"button_voi_off.png",
		"button_voi_off.png");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(StartScene::menuMusicCallback, this), _turnOn, _turnOff, NULL);

	toggleItem->setScale(0.3f);
	toggleItem->setPosition(Point(viewSize.width-50, 50));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	// Ô¤¼ÓÔØ±³¾°ÒôÀÖºÍÒôÐ§
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/aipin.mp3");

	// ÏÈÄ¬ÈÏ²¥·Å±³¾°ÒôÀÖ
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/aipin.mp3", true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8);

	isPause = false;
}

Scene* StartScene::createScene()
{
	auto layer = StartScene::create();

	auto scene = Scene::create();
	scene->addChild(layer);

	return scene;
}
void StartScene::menuMusicCallback(cocos2d::Ref* pSender)
{
	if (isPause == false)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		isPause = true;
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		isPause = false;
	}
}
