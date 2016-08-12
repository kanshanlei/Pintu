#include<stdio.h>
#include"cocos2d.h"

#pragma once

USING_NS_CC;
class CuttingPhotos:public Layer
{
public:
	CuttingPhotos();
	virtual ~CuttingPhotos();
public:
	static CuttingPhotos* create(const char*photo, unsigned int rows=3,
		unsigned int columns=3);
protected:
	unsigned int _rows;
	unsigned int _columns;
	unsigned int _sliceWidth;
	unsigned int _sliceHeight;
	float scale;
	std::vector<std::vector<Sprite*>> _slices;
	std::function<void()> _completeCallback;

	virtual bool initWitchPhoto(const char* photo, unsigned int rows,
		unsigned int columns);

	bool initSlices(const char* photo);

	void initTouchEventListener();

	void initMove(int& row, int& column );

	bool check();

	void move(int x, int y);

public:
	void restart();
	void registerCallFunc(std::function<void()> completeCallback);

};

