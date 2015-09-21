#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__
#include "cocos2d.h"
#include "NoTouchLayer.h"

const int MAX_SCORE = 0x7fffffff;

class ControlLayer : public cocos2d::Layer
{
public:

	ControlLayer(void);

	~ControlLayer(void);

	virtual bool init();

	CREATE_FUNC(ControlLayer);

	void menuPauseCallback(cocos2d::Ref* pSender);

	void updateScore(int score);

public:

	cocos2d::Label* _scoreItem;

	cocos2d::MenuItemSprite* _pauseItem;

	NoTouchLayer* _noTouchLayer;
};
#endif