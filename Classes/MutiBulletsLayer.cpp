#include "MutiBulletsLayer.h"
#include "PlaneLayer.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
#include "Plane.h"
USING_NS_CC;
MutiBulletsLayer::MutiBulletsLayer(){}

MutiBulletsLayer::~MutiBulletsLayer(){}

bool MutiBulletsLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	return true;
}

void MutiBulletsLayer::startShoot()
{
	this->schedule(schedule_selector(MutiBulletsLayer::addMutiBullets), 0.2f, 30, 0.0f);
}

void MutiBulletsLayer::stopShoot()
{
	this->unschedule(schedule_selector(MutiBulletsLayer::addMutiBullets));
}

void MutiBulletsLayer::addMutiBullets(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BULLET_EFFECT_MUSIC.c_str());

	auto bulletLeft = Sprite::createWithSpriteFrameName(BULLET2_IMAGE);
	auto bulletRight = Sprite::createWithSpriteFrameName(BULLET2_IMAGE);
	this->addChild(bulletLeft);
	this->addChild(bulletRight);
	this->_allMutiBullets.pushBack(bulletLeft);
	this->_allMutiBullets.pushBack(bulletRight);

	auto planePosition = PlaneLayer::getPlane()->getPlaneSprite()->getPosition();
	auto bulletLeftPosition = Point(planePosition.x - 33, planePosition.y + 35);
	auto bulletRightPosition = Point(planePosition.x + 33, planePosition.y + 35);
	bulletLeft->setPosition(bulletLeftPosition);
	bulletRight->setPosition(bulletRightPosition);

	float length = Director::getInstance()->getVisibleSize().height + bulletLeft->getContentSize().height / 2 - bulletLeftPosition.y;
	float velocity = 420 / 1;//420pixel/sec
	float realMoveDuration = length / velocity;

	auto actionLeftMove = MoveTo::create(realMoveDuration, Point(bulletLeftPosition.x, Director::getInstance()->getWinSize().height + bulletLeft->getContentSize().height / 2));
	auto actionLeftDone = CallFuncN::create(CC_CALLBACK_1(MutiBulletsLayer::mutiBulletsMoveFinished, this));
	auto sequenceLeft = Sequence::create(actionLeftMove, actionLeftDone, nullptr);

	auto actionRightMove = MoveTo::create(realMoveDuration, Point(bulletRightPosition.x, Director::getInstance()->getWinSize().height + bulletRight->getContentSize().height / 2));
	auto actionRightDone = CallFuncN::create(CC_CALLBACK_1(MutiBulletsLayer::mutiBulletsMoveFinished, this));
	auto sequenceRight = Sequence::create(actionRightMove, actionRightDone, nullptr);

	bulletLeft->runAction(sequenceLeft);
	bulletRight->runAction(sequenceRight);
}

void MutiBulletsLayer::mutiBulletsMoveFinished(Node* pSender)
{
	auto mutiBullets = (Sprite*)pSender;
	_allMutiBullets.eraseObject(mutiBullets);
	this->removeChild(mutiBullets, true);
}

void MutiBulletsLayer::removeMutiBullets(Sprite* mutiBullets)
{
	if (mutiBullets != nullptr)
	{
		_allMutiBullets.eraseObject(mutiBullets);
		this->removeChild(mutiBullets, true);
	}
}
