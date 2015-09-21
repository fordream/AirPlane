#ifndef __PLANE_H__
#define __PLANE_H__
#include "cocos2d.h"
class Plane:public cocos2d::Node{
public:
	bool isAlive;
	void moveTo(cocos2d::Vec2);
	void blowUp();
	static Plane* getInstance();

	virtual bool init();

	cocos2d::Sprite* getPlaneSprite(){ return _plane; }
private:
	Plane() :isAlive(true), _plane(nullptr){};
	~Plane(){ _plane = nullptr; }

	static Plane* create();
	cocos2d::Sprite* _plane;
	static Plane* _instance;
};
#endif