#include "WelcomeScene.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
WelcomeScene::WelcomeScene()
{
	_welcomeLayer = nullptr;
}

WelcomeScene::~WelcomeScene()
{
}

bool WelcomeScene::init()
{
	if (!Scene::init()){
		return false;
	}
	_welcomeLayer = WelcomeLayer::create();
	this->addChild(_welcomeLayer);
	PreloadMusic();
	return true;

}

void WelcomeScene::PreloadMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bullet.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy2_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy3_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("game_over.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("use_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("out_porp.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");


	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3", true);
}