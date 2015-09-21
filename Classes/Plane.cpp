#include "Plane.h"
#include "Global.h"
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
	this->addChild(_plane);//Ìí¼Ó¾«Áé£¬AIRPLANEÊÇtag

	Blink *blink = Blink::create(1, 3);//ÉÁË¸¶¯»­  

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HERO1_IMAGE));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HERO2_IMAGE));
	auto animate = Animate::create(animation);//Ö¡¶¯»­  

	_plane->runAction(blink);//Ö´ÐÐÉÁË¸¶¯»­
	_plane->runAction(RepeatForever::create(animate));// Ö´ÐÐÖ¡¶¯»­  

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
void Plane::blowUp(){

}
void Plane::remove(){

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