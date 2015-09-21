#include "GameOverLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
int GameOverLayer::_highestHistoryScore = 0;

GameOverLayer::GameOverLayer()
{
	_score = 0;
	_highestScore = nullptr;
}

GameOverLayer::~GameOverLayer()
{
}

GameOverLayer* GameOverLayer::create(int passScore)
{
	GameOverLayer *pRet = new GameOverLayer();
	pRet->_score = passScore;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool GameOverLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("game_over.mp3");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::createWithSpriteFrameName("gameover.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto normalBackToGame = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto pressedBackToGame = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto backItem = MenuItemSprite::create(normalBackToGame,
		pressedBackToGame,
		nullptr,
		CC_CALLBACK_1(GameOverLayer::menuBackCallback, this));

	backItem->setPosition(Point(visibleSize.width - normalBackToGame->getContentSize().width / 2 - 10, normalBackToGame->getContentSize().height / 2 + 10));
	auto menuBack = Menu::create(backItem, nullptr);
	menuBack->setPosition(Point::ZERO);
	this->addChild(menuBack);

	Value strScore(_score);
	auto finalScore = Label::createWithBMFont("font.fnt", strScore.asString());
	finalScore->setColor(Color3B(143, 146, 147));
	finalScore->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(finalScore);

	auto delay = DelayTime::create(1.0f);
	auto scalebig = ScaleTo::create(1.0f, 3.0f);
	auto scalelittle = ScaleTo::create(0.3f, 2.0f);
	auto sequence = Sequence::create(delay, scalebig, scalelittle, nullptr);
	finalScore->runAction(sequence);

	Value strHighestScore(_highestHistoryScore);
	_highestScore = Label::createWithBMFont("font.fnt", strHighestScore.asString());
	_highestScore->setColor(Color3B(143, 146, 147));
	_highestScore->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	_highestScore->setPosition(Point(140, visibleSize.height - 30));
	this->addChild(_highestScore);

	if (_score > _highestHistoryScore)
	{
		UserDefault::getInstance()->setIntegerForKey("HighestScore", _score);
		_highestHistoryScore = _score;
		auto delayChange = DelayTime::create(1.3f);
		auto moveOut = MoveBy::create(0.1f, Point(0, 100));
		auto beginChange = CallFuncN::create(CC_CALLBACK_1(GameOverLayer::beginChangeHighestScore, this));
		auto moveIn = MoveBy::create(0.1f, Point(0, -100));
		auto sequence = Sequence::create(delayChange, moveOut, beginChange, moveIn, nullptr);
		_highestScore->runAction(sequence);
	}

	return true;
	
}

void GameOverLayer::menuBackCallback(Ref* pSender)
{
	auto pScene = GameScene::create();
	auto animateScene = TransitionSlideInL::create(1.0f, pScene);
	Director::getInstance()->replaceScene(animateScene);
}

void GameOverLayer::beginChangeHighestScore(Node* pNode)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("achievement.mp3");
	Value changeScore(_score);
	_highestScore->setString(changeScore.asString());
}
