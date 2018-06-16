#pragma once
#ifndef _MAIN_MENU_UI_H
#define _MAIN_MENU_UI_H
#include"tools.h"
_MGE_BEGIN
_UI_BEGIN
//clockWise,Anti-clockwise
class MainMenuUI :public cocos2d::Layer{
private:
	cocos2d::EventListenerMouse* listenerMouse;
	bool is_on_touched;
	cocos2d::Point touchedPoint;
	std::vector<cocos2d::Sprite*> SpriteVec;
	std::vector<std::function<void(cocos2d::Node*, cocos2d::EventMouse*)>> CallBackVec;
	float lastAngle;
	float lastTime;
	bool is_stop;
public:
	CREATE_FUNC(MainMenuUI);
	virtual bool init() override;
	static MainMenuUI* createWithPoint(const cocos2d::Point& point,
	std::vector<cocos2d::Sprite*>& spriteVec,
	std::vector<std::function<void(cocos2d::Node*,cocos2d::EventMouse*)>>& callBackVec
	);
	void checkTouch(float);
	void InertialSliding(cocos2d::Node* node, float init_angle,float);


	virtual void onEnter() override;
	virtual void onExit() override;


};




_UI_END
_MGE_END
#endif // !_MAIN_MENU_UI_H
