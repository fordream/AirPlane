#ifndef __PLANE_LAYER_H__
#define __PLANE_LAYER_H__
#include "cocos2d.h"
class Plane;
class PlaneLayer :
	public cocos2d::Layer
{
public:

	PlaneLayer(){}

	~PlaneLayer(){}

	CREATE_FUNC(PlaneLayer);

	virtual bool init();

	static Plane* getPlane(){ return _plane; }

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);

private:
	static Plane* _plane;
};

#endif