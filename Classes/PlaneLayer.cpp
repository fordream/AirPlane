#include "PlaneLayer.h"
#include "Global.h"
#include "Plane.h"
USING_NS_CC;
Plane* PlaneLayer::_plane = nullptr;
bool PlaneLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_plane = Plane::getInstance();
	_plane->getPlaneSprite()->setPosition(Vec2(origin.x + visibleSize.width / 2, 
		_plane->getPlaneSprite()->getContentSize().height / 2));//飞机放置在底部中央  
	this->addChild(_plane, 0, AIRPLANE);//添加精灵，AIRPLANE是tag

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlaneLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlaneLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlaneLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool PlaneLayer::onTouchBegan(Touch* touch, Event *event){
	return true;
}

void PlaneLayer::onTouchMoved(Touch* touch, Event *event){
	if (_plane->isAlive)
	{
		Vec2 curPoint = touch->getLocation();
		//juggle the area of drag 
		Rect planeRect = _plane->getPlaneSprite()->getBoundingBox();
		//扩大拉拽区域
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;
		if (planeRect.containsPoint(this->getParent()->convertTouchToNodeSpace(touch)))
		{
			Vec2 lastPoint = touch->getPreviousLocation();

			Vec2 offSet = curPoint - lastPoint;
			Vec2 des = _plane->getPlaneSprite()->getPosition() + offSet;
			_plane->moveTo(des);
		}
	}
}

void PlaneLayer::onTouchEnded(Touch* touch, Event *event){

}