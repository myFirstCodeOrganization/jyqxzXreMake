#include "battleSprite.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
bool battleSprite::init()
{
	if(!Sprite::init())
	return false;

	return true;
}
battleSprite * battleSprite::createWithRole(Role * r)
{
	auto pbS = battleSprite::create();
	pbS->addChild(r);
	pbS->setRole(r);
	pbS->setMoveAbility(r->getMoveAbility());
	pbS->setName(r->Name);
	pbS->setHp(r->MaxHp);
	pbS->setMp(r->MaxMp);
	


	return pbS;
}
