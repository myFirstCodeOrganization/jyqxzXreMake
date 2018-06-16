#pragma once
#ifndef ROLE_H
#define ROLE_H
#include "tools.h"
#include"location.h"

_MGE_BEGIN
enum class battlestatus{MOVE,ON_MOVE,ATTACK,ON_ATTACK,REST,UP_SP};
using moveAbility = int;

class Role :public cocos2d::Sprite {
public:
	//CREATE_FUNC(Role);
	Role() :_sprite(nullptr), _moveAblity(3) {}
    static Role* createWithSprite(cocos2d::Sprite* s);
	static Role* createWithRoleInfo(const Tools::roleInfo& ri);
	moveAbility getMoveAbility() { return _moveAblity; }
	cocos2d::Sprite* getSprite() { return _sprite; }
	void setMoveAbility(moveAbility M_A) { _moveAblity = M_A; }
	std::string getName() { return Name; }
	void setName(const std::wstring& wstr) { Name = Tools::to_uft8(wstr); }
	void setName(const std::string& str) { Name = str; }

public:
	std::string Name;
	std::string Animation;
	std::string Head;
	int MaxHp;
	int MaxMp;
private:
	cocos2d::Sprite* _sprite;
	moveAbility _moveAblity;

};




_MGE_END
#endif