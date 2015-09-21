#include "WelcomeLayer.h"
#include "GameScene.h"
#include "GameOverLayer.h"
USING_NS_CC;
WelcomeLayer::WelcomeLayer(){}

WelcomeLayer::~WelcomeLayer(){}

bool WelcomeLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto loading = Sprite::createWithSpriteFrameName("game_loading1.png");
	loading->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 40));
	this->addChild(loading);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));

	auto animate = Animate::create(animation);
	auto repeat = Repeat::create(animate, 2);
	auto repeatdone = CallFuncN::create(CC_CALLBACK_1(WelcomeLayer::loadingDone, this));
	auto sequence = Sequence::create(repeat, repeatdone, nullptr);
	loading->runAction(sequence);

	getHighestHistorySorce();
	return true;
}

void WelcomeLayer::loadingDone(Node* pNode)
{
	auto pScene = GameScene::create();
	auto animateScene = TransitionMoveInB::create(0.5f, pScene);
	Director::getInstance()->replaceScene(animateScene);
}

bool WelcomeLayer::isHaveSaveFile()
{
	if (!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
	{
		UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
		UserDefault::getInstance()->setIntegerForKey("HighestScore", 0);
		UserDefault::getInstance()->flush();
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		GameOverLayer::_highestHistoryScore = UserDefault::getInstance()->getIntegerForKey("HighestScore", 0);
	}
}