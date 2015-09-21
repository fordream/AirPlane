#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__
#include "cocos2d.h"
#include "GameOverLayer.h"

class GameOverScene : public cocos2d::Scene
{
public:

	GameOverScene();

	~GameOverScene();

	virtual bool init();

	static GameOverScene* create(int passScore);

public:

	GameOverLayer* _gameOverLayer;

	int _score;
};
#endif