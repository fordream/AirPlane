#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "EnemyLayer.h"
#include "BulletLayer.h"
#include "UFOLayer.h"
#include "PlaneLayer.h"
#include "MutiBulletsLayer.h"
#include "UFOLayer.h"
#include "ControlLayer.h"
class GameLayer : public cocos2d::Layer
{
	CC_SYNTHESIZE(EnemyLayer*, _enemyLayer, EnemyLayer);
	CC_SYNTHESIZE(BulletLayer*, _bulletLayer, BulletLayer);
	CC_SYNTHESIZE(UFOLayer*, _UFOLayer, UFOLayer);
	CC_SYNTHESIZE(PlaneLayer*, _planeLayer, PlaneLayer);
	CC_SYNTHESIZE(MutiBulletsLayer*, _mutiBulletsLayer, MutiBulletsLayer);
	CC_SYNTHESIZE(ControlLayer*, _controlLayer, ControlLayer);
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameLayer);

	void GameLayer::backgroundMove(float);
	static Level getCurLevel(){ return _level; }
	void updateBigBoomItem();
	void menuBigBoomCallback(Ref*);
	virtual void update(float dt);
private:
	cocos2d::Sprite* _background1;
	cocos2d::Sprite* _background2;
	static Level _level;
	int _score;
	int _bigBoomCount;
	cocos2d::Menu* _menuBigBoom;
	cocos2d::Label* _bigBoomCountItem;


};

#endif