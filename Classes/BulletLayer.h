#ifndef __BULLET_LAYER_H__
#define __BULLET_LAYER_H__
#include "cocos2d.h"
class BulletLayer :public cocos2d::Layer{
public:
	BulletLayer();

	~BulletLayer();

	CREATE_FUNC(BulletLayer);

	virtual bool init();

	void addBullet(float dt);

	void bulletMoveFinished(cocos2d::Node* pSender);

	void removeBullet(cocos2d::Sprite* bullet);

	void startShoot(float delay = 0.0f);

	void stopShoot();

	cocos2d::Vector<cocos2d::Sprite*> getAllBullet(){ return _allBullet; }
private:
	cocos2d::Vector<cocos2d::Sprite*> _allBullet;
};
#endif