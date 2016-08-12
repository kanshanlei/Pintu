#include "ScoreScene.h"
#include"UserData.h"
#include"SceneMediator.h"

ScoreScene::ScoreScene()
{
}


ScoreScene::~ScoreScene()
{
}

bool ScoreScene::init()
{
	if (Layer::init() == false) {
		return false;
	}
	_background = Background::create();
	addChild(_background);
	auto viewSize = Director::getInstance()->getVisibleSize();
	/*
	_background = Background::create();
	addChild(_background);
	*/
	_backBut = ui::Button::create("back.png");
	_backBut->setAnchorPoint(Vec2(0, 1));
	_backBut->setPosition(Vec2(10, viewSize.height - 10));
	addChild(_backBut);

	_newScoreTitle = Sprite::create("new_score.png");
	_newScoreTitle->setAnchorPoint(Vec2(0, 0.5f));
	_newScoreTitle->setPosition(Vec2(10, viewSize.height / 2 + 250));
	addChild(_newScoreTitle);
	

	_newScore = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	_newScore->setPosition(Vec2(viewSize.width / 2-50, viewSize.height / 2 + 200));
	auto newScore = UserDefault::getInstance()->getIntegerForKey(NEW_SCORE, 0);
	_newScore->setString(StringUtils::format("%d", newScore));
	this->addChild(_newScore);
	_newTime = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	_newTime->setPosition(Vec2(viewSize.width -200, viewSize.height / 2 + 200));
	auto newTime = UserDefault::getInstance()->getIntegerForKey(NEW_TIME, 1000);
	_newTime->setString(StringUtils::format("%d", newTime));
	this->addChild(_newTime);

	_chartsScoreTitle = Sprite::create("charts_score.png");
	_chartsScoreTitle->setAnchorPoint(Vec2(0, 0.5f));
	_chartsScoreTitle->setPosition(Vec2(10, viewSize.height / 2 + 100));
	addChild(_chartsScoreTitle);
	auto score_label = LabelTTF::create("Level", "Arial", 48);
	score_label->setColor(Color3B(0, 0, 0));
	score_label->setAnchorPoint(Vec2(0, 0));
	score_label->setPosition(viewSize.width / 2 - 50, viewSize.height / 2 + 100);
	addChild(score_label);
	auto time_label = LabelTTF::create("Time", "Arial", 48);
	time_label->setColor(Color3B(0, 0, 0));
	time_label->setAnchorPoint(Vec2(0, 0));
	time_label->setPosition(viewSize.width - 200, viewSize.height / 2 + 100);
	addChild(time_label);

	for (int i = 0; i<5; i++) {
		int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
		int time = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", CONSUME_TIME, i).c_str(), 10000);
		auto row = createScore(i, score, time);
		row->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 50 - 80 * i));
		addChild(row);
	}

	_backBut->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoStartScene();
	});

	return true;
}

Node* ScoreScene::createScore(int rank, int score,int time)
{
	auto viewSzie = Director::getInstance()->getVisibleSize();

	auto row = Node::create();
	auto r = ui::TextAtlas::create(StringUtils::format("%d", rank + 1), "number.png", 63, 83, "0");

	auto s = ui::TextAtlas::create(StringUtils::format("%d", score), "number.png", 63, 83, "0");
	auto t = ui::TextAtlas::create(StringUtils::format("%d", time), "number.png", 63, 83, "0");
	r->setAnchorPoint(Vec2(0, 0));
	s->setAnchorPoint(Vec2(0, 0));
	t->setAnchorPoint(Vec2(0, 0));
	r->setPosition(Vec2(10, 0));
	s->setPosition(Vec2(viewSzie.width /2-50, 0));
	t->setPosition(Vec2(viewSzie.width - 200, 0));
	row->addChild(r);
	row->addChild(s);
	row->addChild(t);
	row->setContentSize(Size(viewSzie.width, 100));
	row->setAnchorPoint(Vec2(0.5, 0.5));
	return row;

}

Scene* ScoreScene::createScene()
{
	auto layer = ScoreScene::create();

	auto scene = Scene::create();

	scene->addChild(layer);

	return scene;
}
