#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
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
};

#endif