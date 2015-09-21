#ifndef __MutiBullets_LAYER_H__
#define __MutiBullets_LAYER_H__
#include "cocos2d.h"
class MutiBulletsLayer : public cocos2d::Layer
{
public:
	MutiBulletsLayer();

	~MutiBulletsLayer();

	CREATE_FUNC(MutiBulletsLayer);

	virtual bool init();

	void addMutiBullets(float dt);

	void mutiBulletsMoveFinished(cocos2d::Node* pSender);

	void removeMutiBullets(cocos2d::Sprite* mutiBullets);

	void startShoot();

	void stopShoot();

public:

	cocos2d::Vector<cocos2d::Node*> _allMutiBullets;

};
#endif
