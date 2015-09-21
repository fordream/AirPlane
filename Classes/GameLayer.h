#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "EnemyLayer.h"
#include "BulletLayer.h"
#include "UFOLayer.h"
#include "PlaneLayer.h"
class GameLayer : public cocos2d::Layer
{

	CC_SYNTHESIZE(EnemyLayer*, enemyLayer, EnemyLayer);
	CC_SYNTHESIZE(BulletLayer*, bulletLayer, BulletLayer);
	CC_SYNTHESIZE(UFOLayer*, ufoLayer, UFOLayer);
	CC_SYNTHESIZE(PlaneLayer*, planeLayer, PlaneLayer);
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameLayer);

	void GameLayer::backgroundMove(float);
	static Level getCurLevel(){ return _level; }
	virtual void update(float dt);
private:
	cocos2d::Sprite* _background1;
	cocos2d::Sprite* _background2;
	static Level _level;
	int _score;
	int _bigBoomCount;
	
};

#endif