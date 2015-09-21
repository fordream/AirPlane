#include "Plane.h"
#include "Global.h"
#include "GameOverScene.h"
USING_NS_CC;
Plane* Plane::_instance = nullptr;
Plane* Plane::getInstance(){
	if (!_instance){
		_instance = create();
	}
	return _instance;
}

bool Plane::init(){
	_plane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HERO1_IMAGE));
	this->addChild(_plane);//添加精灵，AIRPLANE是tag

	Blink *blink = Blink::create(1, 3);//闪烁动画  

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HERO1_IMAGE));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HERO2_IMAGE));
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);//帧动画  

	_plane->runAction(blink);//执行闪烁动画
	_plane->runAction(RepeatForever::create(animate));// 执行帧动画  

	this->retain();
	return true;
}
void Plane::moveTo(Vec2 location){
	if (isAlive && !Director::getInstance()->isPaused())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto planeSize = _plane->getContentSize();
		if (location.x < planeSize.width / 2)
		{
			location.x = planeSize.width / 2;
		}
		if (location.x > visibleSize.width - planeSize.width / 2)
		{
			location.x = visibleSize.width - planeSize.width / 2;
		}
		if (location.y < planeSize.height / 2)
		{
			location.y = planeSize.width / 2 + 10;
		}
		if (location.y > visibleSize.height - planeSize.height / 2)
		{
			location.y = visibleSize.height - planeSize.height / 2;
		}
		_plane->setPosition(location);
	}
}
void Plane::blowUp(int score){
	if (isAlive)
	{
		isAlive = false;
		_score = score;
		log("blowUp%d", _score);
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));

		auto animate = Animate::create(animation);
		auto removePlane = CallFunc::create(CC_CALLBACK_0(Plane::remove, this));
		auto sequence = Sequence::create(animate, removePlane, nullptr);
		
		this->getPlaneSprite()->stopAllActions();
		this->getPlaneSprite()->runAction(sequence);
	}
}
void Plane::remove(){
	//还原
	_plane->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HERO1_IMAGE));
	this->removeFromParent();
	auto over = GameOverScene::create(_score);
	auto animateScene = TransitionMoveInT::create(0.8f, over);
	Director::getInstance()->replaceScene(animateScene);
}
Plane* Plane::create()
{
	Plane *pRet = new Plane();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		_instance = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}