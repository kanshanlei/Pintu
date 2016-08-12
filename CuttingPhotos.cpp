#include"stdlib.h"
#include "CuttingPhotos.h"
#include "SimpleAudioEngine.h"

CuttingPhotos::CuttingPhotos() :
_rows(3),
_columns(3)
{

}


CuttingPhotos::~CuttingPhotos()
{
	this->removeAllChildren();
}

CuttingPhotos* CuttingPhotos::create(const char *photo, unsigned int rows,
	unsigned int columns){
	CuttingPhotos *cp = new CuttingPhotos();
	
	if (cp&&cp->initWitchPhoto(photo, rows, columns)){
		cp->autorelease();
		return cp;
	}

	CC_SAFE_DELETE(cp);

	return nullptr;
}

bool CuttingPhotos::initWitchPhoto(const char* photo, unsigned int rows,
	unsigned int columns){
	bool result = false;
	this->_ignoreAnchorPointForPosition = false;//这一句在需要放大缩小的时候避免anchorpoint的混乱
	if (Layer::init()){
		_rows = rows;
		_columns = columns;
		if(initSlices(photo)){//初始化块
			initTouchEventListener();

			restart();

			result = true;
		}
		else{
			result = false;
		}
	}
	else{ result = false; }
	return result;
}

bool CuttingPhotos::initSlices(const char*photo){
	Texture2D *texture = Director::getInstance()->getTextureCache()->
		addImage(photo);
	
	if (texture == nullptr){ return false; }
	for (int w = 0; w < _rows; ++w){
		std::vector<Sprite*> row;
		for (int h = 0; h < _columns; h++){
			row.push_back(nullptr);
		}
		_slices.push_back(row);//初始化行*列个元素的精灵矩阵
	}

	auto size = texture->getContentSize();
	_sliceWidth = size.width / _rows;
	_sliceHeight = size.height / _columns;

	this->setContentSize(size);
	//挖出最后一块
	auto endSlice = Sprite::createWithTexture(texture, Rect(_sliceWidth*
		(_rows - 1), _sliceHeight*(_columns - 1), _sliceWidth, _sliceHeight));
	endSlice->setAnchorPoint(Vec2(0, 0));
	endSlice->setPosition(_sliceWidth*(_rows - 1), 0);
	endSlice->setOpacity(100);//透明度
	this->addChild(endSlice);

	_slices[_rows - 1][_columns - 1] = nullptr;
	//添加各块
	for (int w = 0; w < _rows; ++w){
		for (int h = 0; h < _columns; h++){
			if (w == _rows - 1 && h == _columns - 1) break;
			Sprite*slice = Sprite::createWithTexture(texture, Rect(_sliceWidth*
				w , _sliceHeight*h , _sliceWidth, _sliceHeight));
			slice->setAnchorPoint(Vec2(0, 0));
			//设置各块标识以便检验是否拼完
			std::stringstream ss;
			std::string str;
			ss << w*_columns+h;
			ss >> str;
			slice->setName(str);
			this->addChild(slice);

			_slices[w][h] = slice;
		}
	}
	return true;
}

void CuttingPhotos::initTouchEventListener()
{
	auto listner = EventListenerTouchOneByOne::create();

	listner->onTouchBegan = [&](Touch *touch, Event* event){
		Point locationInNode = this->convertToNodeSpace(touch->getLocation());

		Size s = this->getContentSize();

		Rect rect = Rect(50, 50, s.width-50, s.height-50);

		if (rect.containsPoint(locationInNode)){
			int x = static_cast<int>(floor(locationInNode.x / this->_sliceWidth));
			int y = static_cast<int>(floor(locationInNode.y / this->_sliceHeight));
			this->move(x, y);
			return true;
		}
		else{

			return false;
		}
	};
	/*
		listner->onTouchBegan = [&](Touch *touch, Event *event){
			Point locationInNode = this->convertToNodeSpace(touch->getLocation());
			int x = static_cast<int>(floor(locationInNode.x / this->_sliceWidth));
			int y = static_cast<int>(floor(locationInNode.y / this->_sliceHeight));
			this->move(x, y);
			return true;
		};
	*/
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this); 
}

void CuttingPhotos::initMove(int& row, int& column)
{
	auto value = static_cast<int>(CCRANDOM_0_1() * 4);//上下左右
	switch (value){
	case 0:
		if (row > 0){
			_slices[row][column] = _slices[row - 1][column];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[--row][column] = nullptr;
		}
		break;
	case 1:
		if (row < _rows-1){
			_slices[row][column] = _slices[row + 1][column];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[++row][column] = nullptr;
		}
		break;
	case 2:
		if (column>0){
			_slices[row][column] = _slices[row][column - 1];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[row][--column] = nullptr;
		}
		break;
	case 3:
		if (column < _columns-1){
			_slices[row][column] = _slices[row][column + 1];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[row][++column] = nullptr;
		}
		break;
	default:break;
	}
}

bool CuttingPhotos::check(){
	for (int w = 0; w < _rows; w++)
	for (int h = 0; h < _columns; h++){
		if (w == _rows - 1 && h == _columns - 1)return true;
		if (_slices[w][h] == nullptr) return false;
		if (atoi(_slices[w][h]->getName().c_str()) != w*_columns + h) return false;
	}
}

void CuttingPhotos::move(int x, int y)
{
	y = _columns - y - 1;
	auto slice = _slices[x][y];

	if (slice == nullptr) return;

	bool isFind = false;
	Point targetPos;
	if (y < _columns - 1 && _slices[x][y + 1] == nullptr){
		targetPos.x = x;
		targetPos.y = y + 1;
		isFind = true;
	}
	else if (y>0 && _slices[x][y - 1] == nullptr){
		targetPos.x = x;
		targetPos.y = y - 1;
		isFind = true;
	}
	else if (x < _rows - 1 && _slices[x + 1][y] == nullptr){
		targetPos.x = x + 1;
		targetPos.y = y;
		isFind = true;
	}
	else if (x>0 && _slices[x - 1][y] == nullptr){
		targetPos.x = x-1;
		targetPos.y = y;
		isFind = true;
	}

	if (isFind == false) return;
	auto music = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/7611.mp3");
	slice->runAction(MoveTo::create(0.25f, Vec2(targetPos.x*_sliceWidth,
		_sliceHeight*_columns - (targetPos.y + 1)*_sliceHeight)));
	_slices[targetPos.x][targetPos.y] = slice;
	_slices[x][y] = nullptr;
	
	if (check()){
		//进入下一关卡
		_completeCallback();
	}
}

void CuttingPhotos::restart(){
	_slices[_rows - 1][_columns - 1] = nullptr;
	int _randRound = _rows*_columns * 10;
	int row = _rows - 1;
	int column = _columns - 1;
	while (_randRound--){
		initMove(row,column);
	}
	
}

void CuttingPhotos::registerCallFunc(std::function<void()> completeCallback)
{
	_completeCallback = completeCallback;
}