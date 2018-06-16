#pragma once
#ifndef BATTLE_FIELD_LAYER_H
#define BATTLE_FILED_LAYER_H
#include"tools.h"
#include"UI/CocosGUI.h"
#include"battleSprite.h"
#include<functional>
_MGE_BEGIN

class battleFieldLayer:public cocos2d::Layer{
public:
	CREATE_FUNC(battleFieldLayer);
	battleFieldLayer() :max_x(11), max_y(5), battleField(), battleButton(),battleSpriteVec(){};
	battleFieldLayer(const int x,const int y):max_x(x), max_y(y), battleField(), battleButton(){};
	virtual bool init() override;
	bool roleInit();
	void moveTo(location l, cocos2d::Ref*);
	void attack(location l, cocos2d::Ref*);
    int hurtResult(battleSprite* targetSprite);
	void showAttack(location l);
	battleSprite* getSprite(location l);
	void runbf();
	void update_everyone();
	~battleFieldLayer();
private:
	std::vector<std::vector<cocos2d::Point>> battleField;
	std::vector<std::vector<cocos2d::ui::Button*>> battleButton;
	std::vector<mygame::battleSprite*> battleSpriteVec;
	battleSprite* current;
	cocos2d::Layer* operatorLayer;
	int max_x;
	int max_y;
	float bt_width;
	float bt_height;
	float ori_x;
	float ori_y;
	float eve_width;
	float eve_height;
};







_MGE_END
#endif // !BATTLE_FIELD_LAYER_H
