#include "ControlLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
ControlLayer::ControlLayer()
{
	_scoreItem = nullptr;
	_pauseItem = nullptr;
}

ControlLayer::~ControlLayer(){}

bool ControlLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto normalPause = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto pressedPause = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	_pauseItem = MenuItemSprite::create(normalPause, pressedPause, CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));
	_pauseItem->setPosition(Point(normalPause->getContentSize().width / 2 + 10, visibleSize.height - normalPause->getContentSize().height / 2 - 10));
	auto menuPause = Menu::create(_pauseItem, nullptr);
	menuPause->setPosition(Point::ZERO);
	this->addChild(menuPause, 101);

	_scoreItem = Label::createWithBMFont("font.fnt", "0");
	_scoreItem->setColor(Color3B(143, 146, 147));
	_scoreItem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	_scoreItem->setPosition(Point(_pauseItem->getPositionX() + normalPause->getContentSize().width / 2 + 5, _pauseItem->getPositionY()));
	this->addChild(_scoreItem);

	return true;
}

void ControlLayer::menuPauseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	if (!Director::getInstance()->isPaused())
	{
		_pauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png"));
		_pauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pause();
		_noTouchLayer = NoTouchLayer::create();
		this->addChild(_noTouchLayer);
	}
	else
	{
		_pauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png"));
		_pauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		this->removeChild(_noTouchLayer, true);
	}
}

void ControlLayer::updateScore(int score)
{
	if (score >= 0 && score <= MAX_SCORE)
	{
		Value strScore(score);
		_scoreItem->setString(strScore.asString());
	}
}
