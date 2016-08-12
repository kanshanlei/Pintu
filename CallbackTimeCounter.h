#pragma once
#include<cocos2d.h>
USING_NS_CC;
class CallbackTimeCounter:public Node
{
public:
	CallbackTimeCounter();
	virtual ~CallbackTimeCounter();
	CREATE_FUNC(CallbackTimeCounter);
	virtual bool init();
	virtual void update(float dt);
	void start(float fCBTime, std::function<void()>func);
private:
	float m_Time;
	float m_fCBTime;
	bool m_isCounting;
	std::function<void()>m_func;
};

