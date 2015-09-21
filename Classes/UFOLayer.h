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

	void addMutiBullets(float dt);

	void mutiBulletsMoveFinished(cocos2d::Node* pSender);

	void removeMutiBullets(cocos2d::Sprite* mutiBullets);

	void addBigBoom(float dt);

	void bigBoomMoveFinished(cocos2d::Node* pSender);

	void removeBigBoom(cocos2d::Sprite* bigBoom);

public:

	cocos2d::Vector<cocos2d::Node*> allMutiBullets;

	cocos2d::Vector<cocos2d::Node*> allBigBoom;

};
#endif

