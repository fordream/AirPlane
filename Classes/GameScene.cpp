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

	_UFOLayer = UFOLayer::create();
	if (!_UFOLayer)
		return false;

	_mutiBulletsLayer = MutiBulletsLayer::create();
	if (!_mutiBulletsLayer)
		return false;

	_controlLayer = ControlLayer::create();
	if (!_controlLayer)
		return false;

	//飞机层在游戏层的上层
	this->addChild(_gameLayer,-10);
	this->addChild(_planeLayer,-9);
	this->addChild(_bulletLayer, -9);
	this->addChild(_enemyLayer, -9);
	this->addChild(_UFOLayer, -9);
	this->addChild(_mutiBulletsLayer, -9);
	this->addChild(_controlLayer, -9);

	_gameLayer->setBulletLayer(_bulletLayer);
	_gameLayer->setPlaneLayer(_planeLayer);
	_gameLayer->setEnemyLayer(_enemyLayer);
	_gameLayer->setUFOLayer(_UFOLayer);
	_gameLayer->setMutiBulletsLayer(_mutiBulletsLayer);
	_gameLayer->setControlLayer(_controlLayer);

	_bulletLayer->startShoot(0.1);
	return true;
}