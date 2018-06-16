#pragma once
#ifndef MAP_LAYER_H
#define MAP_LAYER_H
#include"tools.h"
#include"location.h"
#include"mapEventManager.h"
#include"UIregister.h"
#include<chrono>
_MGE_BEGIN
class mapLayer:public cocos2d::Layer {
private:
	cocos2d::Layer* mapNodeLayer;
	cocos2d::Size visibleSize;
	cocos2d::EventListenerMouse* listenerMouse;
	UI::UIoperatorLayer* UIPL;
	int xBlockNum;
	int yBlockNum;
	bool is_on_touch;
	cocos2d::Point TouchedPoint;
	std::chrono::time_point<std::chrono::steady_clock> TouchTime;
	std::map<const location, const Tools::eventInfo > mapVec;
	bool conditionParse(const std::unique_ptr<Tools::xmlnode>& pCondition);
	bool MapEventParse(cocos2d::Label* eventNode, const location& loc , const std::unique_ptr<Tools::xmlnode>& pEvent);
public:
	CREATE_FUNC(mapLayer);
	static mapLayer* createWithMapInfo(const Tools::mapInfo&mi);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	cocos2d::Layer* getMapNodeLayer() { return mapNodeLayer; }
	void setBackGround(const std::string& backGround);
	//返回分块的位置
	const location getNodeVec2(const float x, const float y);
	//返回真实坐标
	cocos2d::Vec2 getNodePosition(const  location& vec);
	UI::UIoperatorLayer* getUIPL() { return UIPL; };
	mapLayer() :xBlockNum(25), yBlockNum(25),listenerMouse(nullptr),mapVec(),
	visibleSize(cocos2d::Director::getInstance()->getVisibleSize()){};
	void longTouch(float);





};








_MGE_END
#endif