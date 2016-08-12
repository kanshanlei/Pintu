#pragma once
#include<Background.h>
#include<ui/CocosGUI.h>

USING_NS_CC;
class ScoreScene:public Layer
{
protected:
	Background* _background;
	ui::Button* _backBut;
	Sprite* _newScoreTitle;
	ui::TextAtlas* _newScore;
	ui::TextAtlas* _newTime;
	Sprite* _chartsScoreTitle;
	std::vector<Node*> _chartList;

	Node* createScore(int rank, int score,int time);
public:
	ScoreScene();
	virtual ~ScoreScene();
	CREATE_FUNC(ScoreScene);
	virtual bool init();

	static Scene* createScene();
};

