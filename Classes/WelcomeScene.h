#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__
#include "cocos2d.h"
#include "WelcomeLayer.h"

class WelcomeScene : public cocos2d::Scene
{
public:
	WelcomeScene();

	~WelcomeScene();

	virtual bool init();

	CREATE_FUNC(WelcomeScene);

	void PreloadMusic();

public:
	WelcomeLayer* _welcomeLayer;
};
#endif