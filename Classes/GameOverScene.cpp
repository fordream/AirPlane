#include "GameOverScene.h"
USING_NS_CC;
GameOverScene::GameOverScene()
{
	_gameOverLayer = nullptr;
	_score = 0;
}

GameOverScene::~GameOverScene(){}

GameOverScene* GameOverScene::create(int passScore)
{
	GameOverScene *pRet = new GameOverScene();
	pRet->_score = passScore;
	log("GameOverScene£º%d", passScore);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}

	return pRet;
}

bool GameOverScene::init()
{
	if (!Scene::init()){
		return false;
	}
	_gameOverLayer = GameOverLayer::create(_score);
	this->addChild(_gameOverLayer);
	
	return true;
}
