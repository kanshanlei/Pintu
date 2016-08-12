#include "ScoreTimer.h"


ScoreTimer::ScoreTimer()
{
}


ScoreTimer::~ScoreTimer()
{
}

bool ScoreTimer::init()
{
	_time = 0;
	scheduleUpdate();
	return true;
}

void ScoreTimer::startTimer()
{
	scheduleUpdate();
}

void ScoreTimer::stopTimer()
{
	unscheduleUpdate();
}

void ScoreTimer::update(float dt)
{
	_time=_time+dt;

	if (_time < 0){
		stopTimer();
	}
}

double ScoreTimer::getTime()
{
	return _time;
}