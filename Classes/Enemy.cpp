#include "Enemy.h"
USING_NS_CC;
Enemy::Enemy() :_sprite(nullptr), _life(0){}

Enemy::~Enemy(){}

Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy();
	if (pRet != nullptr) {
		pRet->autorelease();
		return pRet;
	}
	else
		return nullptr;
}

void Enemy::bindSprite(Sprite* sprite, int life)
{
	_sprite = sprite;
	_life = life;
	addChild(_sprite);
}

Sprite* Enemy::getSprite()
{
	return _sprite;
}

int Enemy::getLife()
{
	return _life;
}

void Enemy::loseLife()
{
	_life--;
}

Rect Enemy::getBoundingBox()
{
	auto rect = _sprite->getBoundingBox();
	auto pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}