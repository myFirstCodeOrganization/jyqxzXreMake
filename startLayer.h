#pragma once
#ifndef _START_LAYER_H
#define _START_LAYER_H
#include"tools.h"
#include"gameMainScene.h"
#include"sceneTransition.h"
_MGE_BEGIN


class startLayer :public cocos2d::Layer {
public:
	startLayer();
	~startLayer() {};
	CREATE_FUNC(startLayer);

	void endCallback(Ref*);
	void systemCallback(Ref*);
	void startgameCallback(Ref*);
};

class systemSetLayer :public cocos2d::Layer {
public:
	systemSetLayer();
	~systemSetLayer() {};
	CREATE_FUNC(systemSetLayer);
	void soundCallback(Ref* psend);
	void qualityCallback(Ref* psend);
	void backCallback(Ref* psend);
};


_MGE_END



#endif // !_START_LAYER_H
