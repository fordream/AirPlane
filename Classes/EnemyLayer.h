#ifndef __ENEMY_LAYER_H__
#define __ENEMY_LAYER_H__
#include "cocos2d.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"

const int ENEMY1_MAXLIFE = 1;
const int ENEMY2_MAXLIFE = 2;
const int ENEMY3_MAXLIFE = 5;

enum Level
{
	EASY,
	MIDDLE,
	HARD,
};

class EnemyLayer : public cocos2d::Layer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);

	CREATE_FUNC(EnemyLayer);
	virtual bool init();

	void addEnemy1(float dt);
	void enemy1MoveFinished(cocos2d::Node* pSender);
	void enemy1Blowup(Enemy* enemy1);
	void removeEnemy1(cocos2d::Node* pTarget);
	void removeAllEnemy1();

	void addEnemy2(float dt);
	void enemy2MoveFinished(cocos2d::Node* pSender);
	void enemy2Blowup(Enemy* enemy2);
	void removeEnemy2(cocos2d::Node* pTarget);
	void removeAllEnemy2();

	void addEnemy3(float dt);
	void enemy3MoveFinished(cocos2d::Node* pSender);
	void enemy3Blowup(Enemy* enemy3);
	void removeEnemy3(cocos2d::Node* pTarget);
	void removeAllEnemy3();
	void removeAllEnemy();

	cocos2d::Vector<cocos2d::Node*> allEnemy1;
	cocos2d::Vector<cocos2d::Node*> allEnemy2;
	cocos2d::Vector<cocos2d::Node*> allEnemy3;
private:
	cocos2d::SpriteFrame* enemy1SpriteFrame;
	cocos2d::SpriteFrame* enemy2SpriteFrame;
	cocos2d::SpriteFrame* enemy3SpriteFrame_1;
	cocos2d::SpriteFrame* enemy3SpriteFrame_2;
};
#endif