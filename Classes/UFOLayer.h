#ifndef __UFO_LAYER_H__
#define __UFO_LAYER_H__
#include "cocos2d.h"

class UFOLayer : public cocos2d::Layer
{
public:

	UFOLayer(void);

	~UFOLayer(void);

	virtual bool init();

	CREATE_FUNC(UFOLayer);

	void AddMutiBullets(float dt);

	void mutiBulletsMoveFinished(cocos2d::Node* pSender);

	void RemoveMutiBullets(cocos2d::Sprite* mutiBullets);

	void AddBigBoom(float dt);

	void bigBoomMoveFinished(cocos2d::Node* pSender);

	void RemoveBigBoom(cocos2d::Sprite* bigBoom);

public:

	cocos2d::Vector<cocos2d::Node*> allMutiBullets;

	cocos2d::Vector<cocos2d::Node*> allBigBoom;

};
#endif

