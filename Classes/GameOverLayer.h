#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__
#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer
{
public:
	GameOverLayer();

	~GameOverLayer();

	virtual bool init();

	static GameOverLayer* create(int);

	void menuBackCallback(cocos2d::Ref*);

	void beginChangeHighestScore(cocos2d::Node*);

public:

	int _score;

	static int _highestHistoryScore;

	cocos2d::Label* _highestScore;
};
#endif
