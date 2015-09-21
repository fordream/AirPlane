#include "GameLayer.h"
#include "Global.h"
#include "Plane.h"
USING_NS_CC;
Level GameLayer::_level = EASY;
bool GameLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	_level = EASY;
	_score = 0;
	_bigBoomCount = 0;

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

	//enemy1 & bullet CheckCollosion
	for (int i = 0; i < _bulletLayer->getAllBullet().size(); i++){
		auto bullet = _bulletLayer->getAllBullet().at(i);
		Vector<Node*> enemy1sToDelete;
		for (int j = 0; j < _enemyLayer->_allEnemy1.size(); j++){
			auto enemy1 = static_cast<Enemy*>(_enemyLayer->_allEnemy1.at(j));
			if (bullet->getBoundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					enemy1sToDelete.pushBack(enemy1);
					_score += ENEMY1_SCORE;
					_controlLayer->updateScore(_score);
					bulletsToDelete.pushBack(bullet);
				}
			}
		}
		for (int j = 0; j < enemy1sToDelete.size(); j++){
			auto enemy1 = static_cast<Enemy*>(enemy1sToDelete.at(j));
			_enemyLayer->enemy1Blowup(enemy1);
		}
	}
	for (auto bullet : bulletsToDelete){
		_bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete.clear();

	//enemy2 & bullet CheckCollosion
	for (int i = 0; i < _bulletLayer->getAllBullet().size(); i++){
		auto bullet = _bulletLayer->getAllBullet().at(i);
		Vector<Node*> enemy2sToDelete;
		for (int j = 0; j < _enemyLayer->_allEnemy2.size(); j++){
			auto enemy2 = static_cast<Enemy*>(_enemyLayer->_allEnemy2.at(j));
			if (bullet->getBoundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1){
					enemy2->loseLife();
					bulletsToDelete.pushBack(bullet);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					enemy2sToDelete.pushBack(enemy2);
					_score += ENEMY2_SCORE;
					_controlLayer->updateScore(_score);
					bulletsToDelete.pushBack(bullet);
				}
			}
		}
		for (int j = 0; j < enemy2sToDelete.size(); j++){
			auto enemy2 = static_cast<Enemy*>(enemy2sToDelete.at(j));
			_enemyLayer->enemy2Blowup(enemy2);
		}
	}
	for (auto bullet : bulletsToDelete){
		_bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete.clear();

	//enemy3 & bullet CheckCollosion
	for (int i = 0; i < _bulletLayer->getAllBullet().size(); i++){
		auto bullet = _bulletLayer->getAllBullet().at(i);
		Vector<Node*> enemy3sToDelete;
		for (int j = 0; j < _enemyLayer->_allEnemy3.size(); j++){
			auto enemy3 = static_cast<Enemy*>(_enemyLayer->_allEnemy3.at(j));
			if (bullet->getBoundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				if (enemy3->getLife()>1){
					enemy3->loseLife();
					bulletsToDelete.pushBack(bullet);
				}
				else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					enemy3sToDelete.pushBack(enemy3);
					_score += ENEMY3_SCORE;
					_controlLayer->updateScore(_score);
					bulletsToDelete.pushBack(bullet);
				}
			}
		}
		for (int j = 0; j < enemy3sToDelete.size(); j++){
			auto enemy3 = static_cast<Enemy*>(enemy3sToDelete.at(j));
			_enemyLayer->enemy3Blowup(enemy3);
		}
	}
	for (auto bullet : bulletsToDelete){
		_bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete.clear();


	Vector<Sprite*> mutiBulletsToDelete;

	////enemy1 & mutiBullets CheckCollosion
	for (auto mutibullet : _mutiBulletsLayer->_allMutiBullets){
		Vector<Node*> enemy1sToDelete;
		for (auto enemy1 : _enemyLayer->_allEnemy1){
			auto enemy = static_cast<Enemy*>(enemy1);
			if (mutibullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				if (enemy->getLife() == 1)
				{
					enemy->loseLife();
					enemy1sToDelete.pushBack(enemy);
					_score += ENEMY1_SCORE;
					mutiBulletsToDelete.pushBack(static_cast<Sprite*>(mutibullet));
					_controlLayer->updateScore(_score);
				}
				
			}
		}
		for (auto enemy : enemy1sToDelete){
			_enemyLayer->enemy1Blowup(static_cast<Enemy*>(enemy));
		}
		enemy1sToDelete.clear();
	}
	for (auto bullet : mutiBulletsToDelete){
		_mutiBulletsLayer->removeMutiBullets(bullet);
	}
	mutiBulletsToDelete.clear();

	//enemy2 & mutiBullets CheckCollosion
	for (auto mutibullet : _mutiBulletsLayer->_allMutiBullets){
		Vector<Node*> enemy2sToDelete;
		for (auto enemy2 : _enemyLayer->_allEnemy2){
			auto enemy = static_cast<Enemy*>(enemy2);
			if (mutibullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				if (enemy->getLife() > 1)
				{
					enemy->loseLife();
					mutiBulletsToDelete.pushBack(static_cast<Sprite*>(mutibullet));
				}
				else if (enemy->getLife() == 1){
					enemy->loseLife();
					enemy2sToDelete.pushBack(enemy);
					_score += ENEMY2_SCORE;
					mutiBulletsToDelete.pushBack(static_cast<Sprite*>(mutibullet));
					_controlLayer->updateScore(_score);
				}
			}
		}
		for (auto enemy : enemy2sToDelete){
			_enemyLayer->enemy2Blowup(static_cast<Enemy*>(enemy));
		}
		enemy2sToDelete.clear();
	}
	for (auto bullet : mutiBulletsToDelete){
		_mutiBulletsLayer->removeMutiBullets(bullet);
	}
	mutiBulletsToDelete.clear();

	//enemy3 & mutiBullets CheckCollosion
	for (auto mutibullet : _mutiBulletsLayer->_allMutiBullets){
		Vector<Node*> enemy3sToDelete;
		for (auto enemy3 : _enemyLayer->_allEnemy3){
			auto enemy = static_cast<Enemy*>(enemy3);
			if (mutibullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				if (enemy->getLife() > 1)
				{
					enemy->loseLife();
					mutiBulletsToDelete.pushBack(static_cast<Sprite*>(mutibullet));
				}
				else if (enemy->getLife() == 1){
					enemy->loseLife();
					enemy3sToDelete.pushBack(enemy);
					_score += ENEMY3_SCORE;
					mutiBulletsToDelete.pushBack(static_cast<Sprite*>(mutibullet));
					_controlLayer->updateScore(_score);
				}
				
			}
		}
		for (auto enemy : enemy3sToDelete){
			_enemyLayer->enemy3Blowup(static_cast<Enemy*>(enemy));
		}
		enemy3sToDelete.clear();
	}
	for (auto bullet : mutiBulletsToDelete){
		_mutiBulletsLayer->removeMutiBullets(bullet);
	}
	mutiBulletsToDelete.clear();


	auto planeRect = PlaneLayer::getPlane()->getPlaneSprite()->getBoundingBox();
	//planeRect.origin.x += 30;
	//planeRect.size.width -= 60;


	//enemy1 & airplane CheckCollosion
	for (auto enemy1 : _enemyLayer->_allEnemy1){
		auto enemy = static_cast<Enemy*>(enemy1);
		if (enemy->getLife() > 0){
			if (planeRect.intersectsRect(enemy->getBoundingBox()))
			{
				unscheduleAllSelectors();
				_bulletLayer->stopShoot();
				_mutiBulletsLayer->stopShoot();
				_planeLayer->getPlane()->blowUp(_score);
				return;
			}
		}
	}

	//enemy2 & airplane CheckCollosion
	for (auto enemy2 : _enemyLayer->_allEnemy2){
		auto enemy = static_cast<Enemy*>(enemy2);
		if (enemy->getLife() > 0){
			if (planeRect.intersectsRect(enemy->getBoundingBox()))
			{
				unscheduleAllSelectors();
				_bulletLayer->stopShoot();
				_mutiBulletsLayer->stopShoot();
				_planeLayer->getPlane()->blowUp(_score);
				return;
			}
		}
	}

	//enemy3 & airplane CheckCollosion
	for (auto enemy3 : _enemyLayer->_allEnemy3){
		auto enemy = static_cast<Enemy*>(enemy3);
		if (enemy->getLife() > 0){
			if (planeRect.intersectsRect(enemy->getBoundingBox()))
			{
				unscheduleAllSelectors();
				_bulletLayer->stopShoot();
				_mutiBulletsLayer->stopShoot();
				_planeLayer->getPlane()->blowUp(_score);
				return;
			}
		}
	}

	//mutiBullets & airplane CheckCollision
	for (auto mutibullet : _UFOLayer->allMutiBullets){
		if (PlaneLayer::getPlane()->getPlaneSprite()->getBoundingBox().intersectsRect(mutibullet->getBoundingBox()))
		{
			
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
			_UFOLayer->removeMutiBullets(static_cast<Sprite*>(mutibullet));
			_bulletLayer->stopShoot();
			_mutiBulletsLayer->startShoot();
			_bulletLayer->startShoot(6.2f);
			//必须break掉，在循环中删除产生错误
			break;;
		}
	}

	//bigBoom & airplane CheckCollision
	for (auto bigBoom : _UFOLayer->allBigBoom){
		if (PlaneLayer::getPlane()->getPlaneSprite()->getBoundingBox().intersectsRect(bigBoom->getBoundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_bomb.mp3");
			_UFOLayer->removeBigBoom(static_cast<Sprite*>(bigBoom));
			_bigBoomCount++;
			updateBigBoomItem();
			//必须break掉，在循环中删除产生错误
			break;
		}
	}
}

void GameLayer::updateBigBoomItem()
{
	auto normalBomb = Sprite::createWithSpriteFrameName("bomb.png");
	auto pressedBomb = Sprite::createWithSpriteFrameName("bomb.png");
	if (_bigBoomCount < 0)
	{
		return;
	}
	else if (_bigBoomCount == 0)
	{
		if (this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			this->removeChildByTag(TAG_BIGBOOM_MENUITEM, true);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL, true);
		}
	}
	else if (_bigBoomCount == 1)
	{
		if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			auto bigBoomItem = MenuItemSprite::create(normalBomb, pressedBomb, nullptr, CC_CALLBACK_1(GameLayer::menuBigBoomCallback, this));
			bigBoomItem->setPosition(Point(normalBomb->getContentSize().width / 2 + 10, normalBomb->getContentSize().height / 2 + 10));
			_menuBigBoom = Menu::create(bigBoomItem, nullptr);
			_menuBigBoom->setPosition(Point::ZERO);
			this->addChild(_menuBigBoom, 0, TAG_BIGBOOM_MENUITEM);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL, true);
		}
	}
	else
	{
		if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			auto pBigBoomItem = MenuItemSprite::create(normalBomb, pressedBomb, nullptr, CC_CALLBACK_1(GameLayer::menuBigBoomCallback, this));
			pBigBoomItem->setPosition(Point(normalBomb->getContentSize().width / 2 + 10, normalBomb->getContentSize().height / 2 + 10));
			_menuBigBoom = Menu::create(pBigBoomItem, nullptr);
			_menuBigBoom->setPosition(Point::ZERO);
			this->addChild(_menuBigBoom, 0, TAG_BIGBOOM_MENUITEM);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL, true);
		}
		if (_bigBoomCount >= 0 && _bigBoomCount <= MAX_BIGBOOM_COUNT)
		{
			auto strScore = StringUtils::format("X%d", _bigBoomCount);
			_bigBoomCountItem = Label::createWithBMFont("font.fnt", strScore);
			_bigBoomCountItem->setColor(Color3B(143, 146, 147));
			_bigBoomCountItem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			_bigBoomCountItem->setPosition(Point(normalBomb->getContentSize().width + 15, normalBomb->getContentSize().height / 2 + 5));
			this->addChild(_bigBoomCountItem, 0, TAG_BIGBOOMCOUNT_LABEL);
		}
	}
}

void GameLayer::menuBigBoomCallback(Ref* pSender)
{
	if (_bigBoomCount > 0 && !Director::getInstance()->isPaused())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("use_bomb.mp3");
		_bigBoomCount--;
		_score += _enemyLayer->_allEnemy1.size() * ENEMY1_SCORE;
		_score += _enemyLayer->_allEnemy2.size() * ENEMY2_SCORE;
		_score += _enemyLayer->_allEnemy3.size() * ENEMY3_SCORE;
		_enemyLayer->removeAllEnemy();
		updateBigBoomItem();
		_controlLayer->updateScore(_score);
	}
}