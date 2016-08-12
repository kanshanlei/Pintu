
#include "cocos2d.h"
USING_NS_CC;
class ScoreTimer:public Node
{
public:
	ScoreTimer();
	virtual ~ScoreTimer();
	CREATE_FUNC(ScoreTimer);
	bool init();
	void startTimer();
	void stopTimer();
	virtual void update(float dt);
	double getTime();
private:
	double _time;
};

