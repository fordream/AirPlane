#ifndef __NOTOUCH_LAYER_H__
#define __NOTOUCH_LAYER_H__
#include "cocos2d.h"

class NoTouchLayer : public cocos2d::Layer
{
public:
	virtual bool init();

	// implement the "static node()" method manually 
	CREATE_FUNC(NoTouchLayer);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
};
#endif