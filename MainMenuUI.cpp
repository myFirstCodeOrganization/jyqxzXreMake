#include "MainMenuUI.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
USING_NS_UI;
bool MainMenuUI::init()
{
	if(!Layer::init())
	return false;
	is_on_touched = false;
	return true;
}

MainMenuUI * MainMenuUI::createWithPoint(const cocos2d::Point & point,
	std::vector<cocos2d::Sprite*>& spriteVec, 
	std::vector<std::function<void(cocos2d::Node*,cocos2d::EventMouse*)>>& callBackVec)
{
	auto mui = create();
	auto rotateSprite = trimImage(CV::templateImage, "UI/mainMenuSprite.png");
	rotateSprite->setPosition(point);
	mui->addChild(rotateSprite, 10, "rotateSprite");
	//auto size = 100, 100
	if (spriteVec.size() != callBackVec.size())
	{
		CCLOG("size of spriteVec not equal size of callBackVec ");
	}
	int size = std::min(spriteVec.size(),callBackVec.size());
	//半径
	float r =100*1.5f;
	Vec2 vec = {r,0 };
	float angle = 2.0f*3.14159f / size;
	mui->SpriteVec.swap(std::move(spriteVec));
	mui->CallBackVec.swap(std::move(callBackVec));
	for (int i = 0; i != size; i++) {
		mui->SpriteVec[i]->setPosition(vec);
		vec.rotate(Vec2::ZERO, angle);
		rotateSprite->addChild(mui->SpriteVec[i], 10, "rotateSprite_n");
	}


	//	mui->schedule(CC_CALLBACK_1(MainMenuUI::checkTouch, mui), "checkTouch");

	return mui;
}


void MainMenuUI::checkTouch(float f)
{
	if (is_on_touched) {
		auto rotation = RotateBy::create(0.1f, 10);
		this->getChildByName("rotateSprite")->runAction(rotation);
	}

}

void MainMenuUI::InertialSliding(cocos2d::Node* node,float init_angle,float f )
{
	//角加速度
	if (is_stop) return;
	float a = 1;
	//角初速度
	auto init_v = abs(init_angle)/f;
	auto angle2 = init_v * (lastTime + f) - 0.5f*a*(lastTime + f)*(lastTime + f);
	if (angle2 < lastAngle) {
		is_stop = true;
		return;
	}
	auto angle = angle2 - lastAngle;
	lastAngle = angle2;
	lastTime += f;
	node->runAction(
		RotateBy::create(0,
			CC_RADIANS_TO_DEGREES(
		    init_angle>0?
				angle:
				(-angle)
			)
		)
	);




}

void MainMenuUI::onEnter()
{
	Layer::onEnter();
	if (listenerMouse == nullptr) {
		listenerMouse = EventListenerMouse::create();
		listenerMouse->onMouseDown = [this](EventMouse* event) {
			is_on_touched = true;
			this->touchedPoint= event->getLocationInView();
			this->unschedule("InertialSliding");
		//	CCLOG("%d,%d", touchedPoint.x, touchedPoint.y);
		};
		listenerMouse->onMouseMove=[this](EventMouse* event) {
			if (is_on_touched) {
				auto sprite = this->getChildByName("rotateSprite");
				//auto vec1 = touchedPoint - sprite->getPosition();
				//检测是否惯性滑动
				
				auto vec = event->getLocationInView() - touchedPoint;
				if (vec.getDistance(Vec2::ZERO)>20)
				{
					lastAngle = 0;
					lastTime = 0;
					is_stop = false;
					auto init_angle = event->getLocationInView().getAngle() - touchedPoint.getAngle();
					this->schedule(std::bind(&MainMenuUI::InertialSliding, this,
						this->getChildByName("rotateSprite")
						, init_angle, std::placeholders::_1),
						"InertialSliding");
					is_on_touched = false;
					return;
				}
				//普通滑动
				auto vec2 = event->getLocationInView() - sprite->getPosition();
				auto vec1 = touchedPoint - sprite->getPosition();
				auto angle =- CC_RADIANS_TO_DEGREES((vec2.getAngle()- vec1.getAngle()));
				touchedPoint = event->getLocationInView();
				//CCLOG("%f,%f", vec2.x, vec2.y);

				//sprite->setRotation(angle);
				sprite->runAction(
					RotateBy::create(0,angle)
				);
			}
			

		};
		listenerMouse->onMouseUp= [this](EventMouse* event) {
			if (is_on_touched == true) {
				for (int i = 0; i != SpriteVec.size(); i++) {
					if (SpriteVec[i]->getBoundingBox().containsPoint(
						this->getChildByName("rotateSprite")->convertToNodeSpace(
							event->getLocationInView()
						)
					)) 
					{
						return CallBackVec[i](this, event);
					}
					auto s = SpriteVec[i]->getBoundingBox();
					CCLOG("%f,%f,%f,%f", s.getMaxX(), s.getMaxY(), s.getMinX(), s.getMinY());
				}
			}
			is_on_touched = false;
		};
	}
	if (listenerMouse) {
		_eventDispatcher->pauseEventListenersForTarget(this->getParent(), true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
	}
}

void MainMenuUI::onExit()
{
	Layer::onExit();
	if (listenerMouse) {
		_eventDispatcher->removeEventListener(listenerMouse);
		_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true);

	}
}
