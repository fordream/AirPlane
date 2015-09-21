#include "UFOLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
UFOLayer::UFOLayer(){}

UFOLayer::~UFOLayer(){}

bool UFOLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	this->schedule(schedule_selector(UFOLayer::AddMutiBullets), 20.0);
	this->schedule(schedule_selector(UFOLayer::AddBigBoom), 20.0, kRepeatForever, 5.0);

	return true;;
}

void UFOLayer::AddMutiBullets(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("out_porp.mp3");
	auto mutiBullets = Sprite::createWithSpriteFrameName("ufo1.png");

	auto mutiBlletsSize = mutiBullets->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int minX = mutiBlletsSize.width / 2;
	int maxX = visibleSize.width - mutiBlletsSize.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	mutiBullets->setPosition(Point(actualX, visibleSize.height + mutiBlletsSize.height / 2));
	this->addChild(mutiBullets);
	allMutiBullets.pushBack(mutiBullets);

	//模拟降落伞的动作
	auto move1 = MoveBy::create(0.5f, Point(0, -150));
	auto move2 = MoveBy::create(0.3f, Point(0, 100));
	auto move3 = MoveBy::create(1.0f, Point(0, 0 - visibleSize.height - mutiBlletsSize.height / 2));
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::mutiBulletsMoveFinished, this));

	auto sequence = Sequence::create(move1, move2, move3, moveDone, nullptr);
	mutiBullets->runAction(sequence);
}

void UFOLayer::mutiBulletsMoveFinished(Node* pSender)
{
	auto mutiBullets = (Sprite*)pSender;
	this->removeChild(mutiBullets, true);
	allMutiBullets.eraseObject(mutiBullets);
}

void UFOLayer::AddBigBoom(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("out_porp.mp3");
	auto bigBoom = Sprite::createWithSpriteFrameName("ufo2.png");

	auto bigBoomSize = bigBoom->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int minX = bigBoomSize.width / 2;
	int maxX = visibleSize.width - bigBoomSize.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	bigBoom->setPosition(Point(actualX, visibleSize.height + bigBoomSize.height / 2));
	this->addChild(bigBoom);
	allBigBoom.pushBack(bigBoom);

	//模拟降落伞的动作
	auto move1 = MoveBy::create(0.5, Point(0, -150));
	auto move2 = MoveBy::create(0.3, Point(0, 100));
	auto move3 = MoveBy::create(1.0, Point(0, 0 - visibleSize.height - bigBoomSize.height / 2));
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::bigBoomMoveFinished, this));

	auto sequence = Sequence::create(move1, move2, move3, moveDone, nullptr);
	bigBoom->runAction(sequence);
}

void UFOLayer::bigBoomMoveFinished(Node* pSender)
{
	auto bigBoom = (Sprite*)pSender;
	this->removeChild(bigBoom, true);
	allBigBoom.eraseObject(bigBoom);
}

void UFOLayer::RemoveMutiBullets(Sprite* mutiBullets)
{
	this->removeChild(mutiBullets, true);
	allMutiBullets.eraseObject(mutiBullets);
}

void UFOLayer::RemoveBigBoom(Sprite* bigBoom)
{
	this->removeChild(bigBoom, true);
	allBigBoom.eraseObject(bigBoom);
}