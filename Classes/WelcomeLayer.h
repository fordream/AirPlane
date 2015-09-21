#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__
#include "cocos2d.h"


class WelcomeLayer : public cocos2d::Layer
{
public:

	WelcomeLayer();

	~WelcomeLayer();

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);

	void loadingDone(cocos2d::Node* pNode);

	bool isHaveSaveFile();

	void getHighestHistorySorce();
};
#endif