#include "EnemyLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
USING_NS_CC;
EnemyLayer::EnemyLayer()
{
	_enemy1SpriteFrame = nullptr;
	_enemy2SpriteFrame = nullptr;
	_enemy3SpriteFrame_1 = nullptr;
	_enemy3SpriteFrame_2 = nullptr;
}

EnemyLayer::~EnemyLayer(){}

bool EnemyLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	_enemy1SpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1.png");
	_enemy2SpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png");
	_enemy3SpriteFrame_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png");
	_enemy3SpriteFrame_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png");

	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1f);
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

	auto animation2 = Animation::create();
	animation2->setDelayPerUnit(0.1f);
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));

	auto animation3 = Animation::create();
	animation3->setDelayPerUnit(0.1f);
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));

	AnimationCache::getInstance()->addAnimation(animation1, "enemy1Blowup");
	AnimationCache::getInstance()->addAnimation(animation2, "enemy2Blowup");
	AnimationCache::getInstance()->addAnimation(animation3, "enemy3Blowup");

	schedule(schedule_selector(EnemyLayer::addEnemy1), 0.5f);
	schedule(schedule_selector(EnemyLayer::addEnemy2), 3.0f);
	schedule(schedule_selector(EnemyLayer::addEnemy3), 6.0f);

	return true;
}


void EnemyLayer::addEnemy1(float dt)
{
	auto enemy1 = Enemy::create();
	enemy1->bindSprite(Sprite::createWithSpriteFrame(_enemy1SpriteFrame), ENEMY1_MAXLIFE);

	auto enemy1Size = enemy1->getSprite()->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int minX = enemy1Size.width / 2;
	int maxX = visibleSize.width - enemy1Size.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	enemy1->setPosition(Point(actualX, visibleSize.height + enemy1Size.height / 2));
	this->addChild(enemy1);
	_allEnemy1.pushBack(enemy1);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 2.0f;
		maxDuration = 4.0f;
		break;
	case MIDDLE:
		minDuration = 1.8f;
		maxDuration = 3.6f;
		break;
	case HARD:
		minDuration = 1.6f;
		maxDuration = 3.2f;
		break;
	default:
		minDuration = 2.0f;
		maxDuration = 4.0f;
		break;
	}

	//敌机速度，持续actualDuration
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	auto actionMove = MoveTo::create(actualDuration, Point(actualX, 0 - enemy1->getSprite()->getContentSize().height / 2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy1MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	enemy1->runAction(sequence);

}

void EnemyLayer::enemy1MoveFinished(Node* pSender)
{
	auto enemy1 = (Enemy*)pSender;
	this->removeChild(enemy1, true);
	_allEnemy1.eraseObject(enemy1);
}

void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
	auto animation = AnimationCache::getInstance()->getAnimation("enemy1Blowup");
	auto animate = Animate::create(animation);
	auto removeEnemy1 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy1, this, enemy1));
	auto sequence = Sequence::create(animate, removeEnemy1, nullptr);
	enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy1(Node* pTarget)
{
	auto enemy1 = (Enemy*)pTarget;
	if (enemy1 != nullptr)
	{
		this->removeChild(enemy1, true);
		_allEnemy1.eraseObject(enemy1);
	}
}

void EnemyLayer::removeAllEnemy1()
{
	for (int i = 0; i < _allEnemy1.size(); i++){
		auto enemy1 = (Enemy*)_allEnemy1.at(i);
		if (enemy1->getLife() > 0)
		{
			enemy1Blowup(enemy1);
		}
	}
}

void EnemyLayer::addEnemy2(float dt)
{
	auto enemy2 = Enemy::create();
	enemy2->bindSprite(Sprite::createWithSpriteFrame(_enemy2SpriteFrame), ENEMY2_MAXLIFE);

	auto enemy2Size = enemy2->getSprite()->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int minX = enemy2Size.width / 2;
	int maxX = visibleSize.width - enemy2Size.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	enemy2->setPosition(Point(actualX, visibleSize.height + enemy2Size.height / 2));
	this->addChild(enemy2);
	_allEnemy2.pushBack(enemy2);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 3.0;
		maxDuration = 6.0;
		break;
	case MIDDLE:
		minDuration = 2.7;
		maxDuration = 5.4;
		break;
	case HARD:
		minDuration = 2.5;
		maxDuration = 5.0;
		break;
	default:
		minDuration = 3.0;
		maxDuration = 6.0;
		break;
	}

	//敌机速度，持续actualDuration
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	auto actionMove = MoveTo::create(actualDuration, Point(actualX, 0 - enemy2->getSprite()->getContentSize().height / 2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy2MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	enemy2->runAction(sequence);

}

void EnemyLayer::enemy2MoveFinished(Node* pSender)
{
	auto enemy2 = (Enemy*)pSender;
	this->removeChild(enemy2, true);
	_allEnemy2.eraseObject(enemy2);
}

void EnemyLayer::enemy2Blowup(Enemy* enemy2)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy2_down.mp3");
	auto animation = AnimationCache::getInstance()->getAnimation("enemy2Blowup");
	auto animate = Animate::create(animation);
	auto removeEnemy2 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy2, this, enemy2));
	auto sequence = Sequence::create(animate, removeEnemy2, nullptr);
	enemy2->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy2(Node* pTarget)
{
	auto enemy2 = (Enemy*)pTarget;
	if (enemy2 != nullptr)
	{
		this->removeChild(enemy2, true);
		_allEnemy2.eraseObject(enemy2);
	}
}

void EnemyLayer::removeAllEnemy2()
{
	for (int i = 0; i < _allEnemy2.size(); i++){
		auto enemy2 = (Enemy*)_allEnemy2.at(i);
		if (enemy2->getLife() > 0)
		{
			enemy2Blowup(enemy2);
		}
	}
}

void EnemyLayer::addEnemy3(float dt)
{
	auto enemy3 = Enemy::create();
	enemy3->bindSprite(Sprite::createWithSpriteFrame(_enemy3SpriteFrame_1), ENEMY3_MAXLIFE);

	auto enemy3Size = enemy3->getSprite()->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int minX = enemy3Size.width / 2;
	int maxX = visibleSize.width - enemy3Size.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	enemy3->setPosition(Point(actualX, visibleSize.height + enemy3Size.height / 2));
	this->addChild(enemy3);
	_allEnemy3.pushBack(enemy3);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 4.0;
		maxDuration = 8.0;
		break;
	case MIDDLE:
		minDuration = 3.6;
		maxDuration = 7.2;
		break;
	case HARD:
		minDuration = 3.2;
		maxDuration = 6.4;
		break;
	default:
		minDuration = 4.0;
		maxDuration = 8.0;
		break;
	}

	//敌机速度，持续actualDuration
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	auto actionMove = MoveTo::create(actualDuration, Point(actualX, 0 - enemy3->getSprite()->getContentSize().height / 2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy3MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	enemy3->runAction(sequence);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(_enemy3SpriteFrame_1);
	animation->addSpriteFrame(_enemy3SpriteFrame_2);
	auto animate = Animate::create(animation);
	enemy3->getSprite()->runAction(RepeatForever::create(animate));

}

void EnemyLayer::enemy3MoveFinished(Node* pSender)
{
	auto enemy3 = (Enemy*)pSender;
	this->removeChild(enemy3, true);
	_allEnemy3.eraseObject(enemy3);
}

void EnemyLayer::enemy3Blowup(Enemy* enemy3)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy3_down.mp3");
	auto animation = AnimationCache::getInstance()->getAnimation("enemy3Blowup");
	auto animate = Animate::create(animation);
	auto removeEnemy3 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy3, this, enemy3));
	auto sequence = Sequence::create(animate, removeEnemy3, nullptr);
	enemy3->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy3(Node* pTarget)
{
	auto enemy3 = (Enemy*)pTarget;
	if (enemy3 != nullptr)
	{
		this->removeChild(enemy3, true);
		_allEnemy3.eraseObject(enemy3);
	}
}

void EnemyLayer::removeAllEnemy3()
{
	for (int i = 0; i < _allEnemy3.size(); i++){
		auto enemy3 = (Enemy*)_allEnemy3.at(i);
		if (enemy3->getLife() > 0)
		{
			enemy3Blowup(enemy3);
		}
	}
}


void EnemyLayer::removeAllEnemy()
{
	removeAllEnemy1();
	removeAllEnemy2();
	removeAllEnemy3();
}
