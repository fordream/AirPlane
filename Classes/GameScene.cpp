//GameScene.cpp
#include "GameScene.h"
#include "PlaneLayer.h"
GameScene::GameScene()
{
	_gameLayer = NULL;
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	Scene::init();

	_gameLayer = GameLayer::create();
	if (!_gameLayer)
		return false;

	_planeLayer = PlaneLayer::create();
	if (!_planeLayer)
		return false;

	_bulletLayer = BulletLayer::create();
	if (!_bulletLayer)
		return false;

	_enemyLayer = EnemyLayer::create();
	if (!_enemyLayer)
		return false;
	//飞机层在游戏层的上层
	this->addChild(_gameLayer,-10);
	this->addChild(_planeLayer,-9);
	this->addChild(_bulletLayer, -9);
	this->addChild(_enemyLayer, -9);

	_bulletLayer->startShoot(1);
	return true;
}