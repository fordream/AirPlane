#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"

class Enemy : public cocos2d::Node
{
public:
	Enemy();
	~Enemy();
	static Enemy* create();
	void bindSprite(cocos2d::Sprite* sprite, int life);
	cocos2d::Sprite* getSprite();
	int getLife();
	void loseLife();
	cocos2d::Rect getBoundingBox();

private:
	cocos2d::Sprite* _sprite;
	int _life;
};

#endif