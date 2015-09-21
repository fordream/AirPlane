#include "BulletLayer.h"
#include "Global.h"
#include "PlaneLayer.h"
#include "Plane.h"
USING_NS_CC;

BulletLayer::BulletLayer(){}

BulletLayer::~BulletLayer(){}
bool BulletLayer::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}
void BulletLayer::bulletMoveFinished(Node* pSender)
{
	auto* bullet = static_cast<Sprite*>(pSender);
	
	_allBullet.eraseObject(bullet);
	this->removeChild(bullet, true);//移除屏幕
}

void BulletLayer::startShoot(float delay)
{
	schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kRepeatForever, delay);
}

void BulletLayer::stopShoot()//卸载任务执行器  
{
	unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(Sprite* bullet)//一旦子弹和敌机碰撞，我们就要删掉这个子弹  
{
	if (bullet != nullptr)
	{
		this->removeChild(bullet, true);
		_allBullet.eraseObject(bullet);
	}
}

void BulletLayer::addBullet(float dt)
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BULLET_EFFECT_MUSIC.c_str());
	auto bullet = Sprite::createWithSpriteFrameName(BULLET1_IMAGE);
	addChild(bullet);
	_allBullet.pushBack(bullet);

	Vec2 planePosition = PlaneLayer::getPlane()->getPlaneSprite()->getPosition();
	Vec2 bulletPosition = Vec2(planePosition.x, planePosition.y + PlaneLayer::getPlane()->getPlaneSprite()->getContentSize().height / 2);
	bullet->setPosition(bulletPosition);

	float length = Director::getInstance()->getVisibleSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;
	float velocity = 320 / 1;//320pixel/sec
	float realMoveDuration = length / velocity;

	auto actionMove = MoveTo::create(realMoveDuration, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	bullet->runAction(sequence);
}