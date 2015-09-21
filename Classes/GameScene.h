#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "MutiBulletsLayer.h"
#include "UFOLayer.h"
#include "ControlLayer.h"
class GameScene :
	public cocos2d::Scene
{
public:

	GameScene();

	~GameScene();

	CREATE_FUNC(GameScene);

	virtual bool init();
private:
	GameLayer* _gameLayer;
	PlaneLayer* _planeLayer;
	BulletLayer* _bulletLayer;
	EnemyLayer* _enemyLayer;
	UFOLayer* _UFOLayer;
	MutiBulletsLayer* _mutiBulletsLayer;
	ControlLayer* _controlLayer;
};

#endif