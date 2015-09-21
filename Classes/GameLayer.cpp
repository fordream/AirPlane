#include "GameLayer.h"
#include "Global.h"
USING_NS_CC;
Level GameLayer::_level = EASY;
bool GameLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	_level = EASY;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SHOOT_BACKGROUND_LIST);

	//之后需要删掉
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SHOOT_LIST);

	_background1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(BACKGROUND_IMAGE));
	_background1->setAnchorPoint(Vec2(0, 0));
	_background1->setPosition(Vec2(0, 0));
	this->addChild(_background1);


	_background2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	_background2->setAnchorPoint(Vec2(0, 0));
	_background2->setPosition(Vec2(0, _background2->getContentSize().height - 2));

	this->addChild(_background2);

	//实现背景滚动
	schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);
	this->scheduleUpdate();
	return true;
}

//背景滚动
void GameLayer::backgroundMove(float dt)
{
	_background1->setPositionY(_background1->getPositionY() - 2);
	_background2->setPositionY(_background1->getPositionY() + _background1->getContentSize().height - 2);
	if (_background2->getPositionY() == 0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败
	{
		_background1->setPositionY(0);
	}
}

void GameLayer::update(float dt)
{
	if (_level == EASY && _score >= 1000000)
	{
		_level = MIDDLE;
	}
	else if (_level == MIDDLE && _score >= 2000000)
	{
		_level = HARD;
	}

	Vector<Sprite*> bulletsToDelete;
	Ref* bt, *et, *ut;

	//enemy1 & bullet CheckCollosion
	for (int i = 0; i < bulletLayer->getAllBullet().size(); i++){
		auto bullet = bulletLayer->getAllBullet().at(i);
	}
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		auto bullet = (Sprite*)bt;

		auto enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			auto enemy1 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete, et)
		{
			auto enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		auto bullet = (Sprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	//enemy2 & bullet CheckCollosion
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		auto bullet = (Sprite*)bt;

		auto enemy2sToDelete = __Array::create();
		enemy2sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
		{
			auto enemy2 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy2sToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy2sToDelete, et)
		{
			auto enemy2 = (Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		auto bullet = (Sprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	//enemy3 & bullet CheckCollosion
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		auto bullet = (Sprite*)bt;

		auto enemy3sToDelete = __Array::create();
		enemy3sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
		{
			auto enemy3 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				if (enemy3->getLife() > 1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy3sToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete, et)
		{
			auto enemy3 = (Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		auto bullet = (Sprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();
	bulletsToDelete->release();


	auto mutiBulletsToDelete = __Array::create();
	mutiBulletsToDelete->retain();
	Ref* mbt;

	////enemy1 & mutiBullets CheckCollosion
	CCARRAY_FOREACH(this->mutiBulletsLayer->m_pAllMutiBullets, mbt)
	{
		auto mutiBullets = (Sprite*)mbt;

		auto enemy1sToDelete = __Array::create();
		enemy1sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			auto enemy1 = (Enemy*)et;
			if (mutiBullets->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete, et)
		{
			auto enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete, mbt)
	{
		auto mutiBullets = (Sprite*)mbt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();

	//enemy2 & mutiBullets CheckCollosion
	CCARRAY_FOREACH(this->mutiBulletsLayer->m_pAllMutiBullets, mbt)
	{
		auto mutiBullets = (Sprite*)mbt;

		auto enemy2sToDelete = __Array::create();
		enemy2sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
		{
			auto enemy2 = (Enemy*)et;
			if (mutiBullets->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy2sToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy2sToDelete, et)
		{
			auto enemy2 = (Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2sToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete, mbt)
	{
		auto mutiBullets = (Sprite*)mbt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();

	//enemy3 & mutiBullets CheckCollosion
	CCARRAY_FOREACH(this->mutiBulletsLayer->m_pAllMutiBullets, mbt)
	{
		auto mutiBullets = (Sprite*)mbt;

		auto enemy3sToDelete = __Array::create();
		enemy3sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
		{
			auto enemy3 = (Enemy*)et;
			if (mutiBullets->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				if (enemy3->getLife() > 1)
				{
					enemy3->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
				}
				else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy3sToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete, et)
		{
			auto enemy3 = (Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3sToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete, mbt)
	{
		auto mutiBullets = (Sprite*)mbt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();
	mutiBulletsToDelete->release();


	auto airplaneRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	airplaneRect.origin.x += 30;
	airplaneRect.size.width -= 60;
	//enemy1 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
	{
		auto enemy1 = (Enemy*)et;
		if (enemy1->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy1->getBoundingBox()))
			{
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	//enemy2 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
	{
		auto enemy2 = (Enemy*)et;
		if (enemy2->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy2->getBoundingBox()))
			{
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	//enemy3 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
	{
		auto enemy3 = (Enemy*)et;
		if (enemy3->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy3->getBoundingBox()))
			{
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	//mutiBullets & airplane CheckCollision
	CCARRAY_FOREACH(this->ufoLayer->m_pAllMutiBullets, ut)
	{
		auto mutiBullets = (Sprite*)ut;
		if (this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(mutiBullets->boundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
			this->ufoLayer->RemoveMutiBullets(mutiBullets);
			this->bulletLayer->StopShoot();
			this->mutiBulletsLayer->StartShoot();
			this->bulletLayer->StartShoot(6.2f);
		}
	}

	//bigBoom & airplane CheckCollision
	CCARRAY_FOREACH(this->ufoLayer->m_pAllBigBoom, ut)
	{
		auto bigBoom = (Sprite*)ut;
		if (this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(bigBoom->boundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_bomb.mp3");
			this->ufoLayer->RemoveBigBoom(bigBoom);
			bigBoomCount++;
			updateBigBoomItem(bigBoomCount);
		}
	}
}