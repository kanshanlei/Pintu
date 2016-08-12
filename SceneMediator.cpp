#include "SceneMediator.h"

#include "StartScene.h"
#include "ScoreScene.h"
#include"aboutScene.h"
#include "HelloWorldScene.h"
//#include "ScoreStrategy.h"
#include <memory>

SceneMediator* SceneMediator::_instance = nullptr;

SceneMediator* SceneMediator::getInstance()
{
	if (_instance == nullptr) {
		_instance = new SceneMediator();
	}
	return _instance;
}

void SceneMediator::gotoStartScene()
{
	auto scene = StartScene::createScene();

	Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.25, scene));
}

void SceneMediator::gotoGameScene()
{
	
	//std::shared_ptr<ScoreStrategy> scoreStrategy(new ScoreStrategy());

	auto scene = HelloWorld::createScene();

	Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.25, scene));

}

void SceneMediator::gotoScoreScene()
{
	auto scene = ScoreScene::createScene();

	Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.25, scene));

}

void SceneMediator::gotoaboutScene()
{
	auto scene = aboutScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.25, scene));
}
