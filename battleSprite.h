#pragma once
#ifndef BATTLE_SPRITE_H
#define BATTLE_SPRITE_H
#include"role.h"
_MGE_BEGIN
class battleSprite :public cocos2d::Sprite {
public:
	CREATE_FUNC(battleSprite);
	battleSprite() :role(nullptr), _location({ 0,0 }), status(battlestatus::REST), _moveAbility(0), sp(0.0f), spbar(0.0f) {};
	virtual bool init() override;
	static battleSprite* createWithRole(Role *);
	location getlocation() { return _location; };
	void setLocation(const location& loc) {
		_location.x = loc.x;
		_location.y = loc.y;
	; };
	void setStatus(battlestatus bs) { status = bs; }
	battlestatus getStatus() { return status; }
	moveAbility getMoveAbility() { return _moveAbility; }
	void setMoveAbility(moveAbility M_A) { _moveAbility = M_A; }
	Role* getRole() { return role; }
	void setRole(Role* r) { role = r; }
	float getSp() { return sp; }
	void setSp(float _sp) { sp = _sp; }
	float getSpBar() { return spbar; }
	void setSpBar(float _spbar) { spbar = _spbar; }
	std::string getName() { return role->getName(); }
	void setName(const std::wstring& wstr) { role->setName(wstr); }
	void setName(const std::string& str) { role->setName(str); }
	int getHp() { return Hp; }
	int getMp() { return Mp; }
	void setHp(int hp) { Hp = hp; }
	void setMp(int mp) { Mp = mp; }
	int getAttack() { return attack; }
	int getDefence() { return defence; }
	void setAttack(int _attack) { attack = _attack; }
	void setDefence(int _defence) { defence = _defence; }

public:
	int Hp;
	int Mp;
	float sp;
	float spbar;
	int attack;
	int defence;
private:
	Role* role;
	location _location;
	battlestatus status;
	moveAbility _moveAbility;

};





_MGE_END
#endif // !BATTLE_SPRITE_H

