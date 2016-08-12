#include "HelloWorldScene.h"
#include"UserData.h"
#include <algorithm>
USING_NS_CC;
HelloWorld::~HelloWorld()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void HelloWorld::initLevelDataList()
{
	auto str = FileUtils::getInstance()->getStringFromFile("leveldata.csv");

	std::vector<std::string> rowList;

	char *row = strtok((char*)str.c_str(), "\n");
	while (row)
	{
		rowList.push_back(row);
		row = strtok(nullptr, "\n");
	}

	for (auto row = rowList.begin(); row != rowList.end(); ++row) {
		char* rows = strtok((char*)row->c_str(), ",");
		char* columns = strtok(nullptr, ",");
		char* loss = strtok(nullptr, ",");

		if (rows == nullptr || columns == nullptr || loss == nullptr) {
			continue;
		}

		LevelData level;

		level.rows = atoi(rows);
		level.columns = atoi(columns);
		level.loss = atoi(loss);

		if (level.rows*level.columns <= 0 || (level.rows*level.columns) % 2 != 0 || level.loss<0) {
			continue;
		}
		_levelDataList.push_back(level);

	}
	_allLevel = static_cast<int>(_levelDataList.size());
}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	initLevelDataList();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	// 预加载背景音乐和音效
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/va1.mp3");
	isPause = false;
	// 先默认播放背景音乐
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/va1.mp3", true);
//	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);

	_nowLevel = -1;
	initUI();
	nextLevel();
	timer = ScoreTimer::create();
	this->addChild(timer);
	

    return true;
}

void HelloWorld::initUI()
{

	Size viewSize = Director::getInstance()->getVisibleSize();
	Layer* background = LayerColor::create(Color4B(255,255,255,128));
	addChild(background);
	// 添加 声音  的开关按钮
	
	auto _turnOn = MenuItemImage::create(
		"button_voi_on.png",
		"button_voi_on.png");
	auto _turnOff = MenuItemImage::create(
		"button_voi_off.png",
		"button_voi_off.png");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::menuMusicCallback, this), _turnOn, _turnOff, NULL);

	toggleItem->setScale(0.3f);
	toggleItem->setPosition(Point(viewSize.width - 50, 50));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	
	
	_pauseButton = ui::Button::create("pause.png");
	_pauseButton->setAnchorPoint(Vec2(0, 1));
	_pauseButton->setPosition(Vec2(0, viewSize.height));
	this->addChild(_pauseButton);

	_pauseButton->addClickEventListener([this](Ref* ref){
		timer->stopTimer();
		auto pauseBox = Pause::create();
		pauseBox->registerCallback([this, pauseBox](){
			timer->startTimer();
			pauseBox->removeFromParent();
			//this->scheduleUpdate();
			//update用来根据时间计分，这里先不用
		}, [this](){
			gameOver();
		});

		this->addChild(pauseBox);
	});
}
void HelloWorld::nextLevel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_nowLevel++;
	if (_nowLevel >= _allLevel) {
		gameOver();
	}

	_nowLevelData = _levelDataList[_nowLevel];

	photo = CuttingPhotos::create("psu.jpg", _nowLevelData.rows, _nowLevelData.columns);
	photo->setAnchorPoint(Vec2(0.5, 0.5));

	auto size = photo->getContentSize();
	float scale = std::min((visibleSize.width - 100) / size.width, (visibleSize.height - 100) / size.height);
	photo->setScale(scale);
	//缩放以后真实锚点位置仍是相对于原图的位置
	
	photo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(photo);

	
	CallbackTimeCounter* counter = CallbackTimeCounter::create();
	this->addChild(counter);
	photo->registerCallFunc([this,counter](){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto particle = ParticleSystemQuad::create("ExplodingRing.plist");
		particle->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		particle->setAutoRemoveOnFinish(true); 
		this->addChild(particle);			
		auto ye=SimpleAudioEngine::getInstance()->playEffect("music/victory_screen_start.mp3");
		//等待2秒再切下一关
		
		
		counter->start(2.0f,[this](){

			this->removeChild(photo);
			this->nextLevel();
			
		});
	});
}

void HelloWorld::gameOver()
{
	timer->stopTimer();//这里暂时没有处理time值是负数的情况

	UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, _nowLevel);
	UserDefault::getInstance()->setIntegerForKey(NEW_TIME, timer->getTime());

	std::vector<int> scoreList;
	std::vector<int> timeList;

	for (int j = 0; j<5; j++) {
		int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, j).c_str(), 0);
		int time = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", CONSUME_TIME, j).c_str(), 10000);
		scoreList.push_back(score);
		timeList.push_back(time);
	}
	scoreList.push_back(_nowLevel);
	timeList.push_back(timer->getTime());
	/*
	std::sort(scoreList.begin(), scoreList.end(), [](int &a, int &b){
		return a>b;
	});
*/
	int i;
	for (i = scoreList.size() - 2; i >= 0; i--) {
		if (_nowLevel < scoreList[i]){		
			break;
		}
	}
	for (i++; i < scoreList.size() - 1; i++)
	{
		if (timer->getTime() < timeList[i])break;
		if (_nowLevel>scoreList[i])break;
	}
	for (int j = scoreList.size() - 2; j >i; j--)
	{
		scoreList[j + 1] = scoreList[j];
		timeList[j + 1] = timeList[j];
	}
	scoreList[i] = _nowLevel;
	timeList[i] = timer->getTime();

	
	for (i = 0; i < 5; i++){
		UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), scoreList[i]);
		UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", CONSUME_TIME, i).c_str(),timeList[i] );

	}
	

	SceneMediator::getInstance()->gotoScoreScene();
}

void HelloWorld::menuMusicCallback(cocos2d::Ref* pSender)
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