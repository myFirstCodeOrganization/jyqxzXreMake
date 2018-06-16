#pragma once
#ifndef _GAME_MAIN_SCENE_H
#define _GAME_MAIN_SCENE_H
#include"tools.h"
_MGE_BEGIN
class gameMainScene :public cocos2d::Scene {
public:
	CREATE_FUNC(gameMainScene);
	virtual bool init() override;
	~gameMainScene();
	static
		std::vector<std::string> getTextureResource();
	static
		std::vector<std::string> getListResource();
private:
	
};






_MGE_END



#endif // !_GAME_MAIN_SCENE_H
