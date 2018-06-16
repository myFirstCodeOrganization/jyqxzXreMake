#include "role.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
Role* Role::createWithSprite(cocos2d::Sprite * s)
{
	auto p = new(std::nothrow) Role();
	if (p && p->init()) {
		p->_sprite = s;
		s->setAnchorPoint({ 0,0 });
		p->addChild(s, 0);
		p->autorelease();
	}
	else
	{
		delete p;
		p = nullptr;
	}
	return p;
}

Role * Role::createWithRoleInfo(const Tools::roleInfo & ri)
{
	auto role = createWithSprite(
		Sprite::create(std::string("heads/")+ri.Attribute.at("head")+".png")
	);
	role->Name=ri.Attribute.at("name");
    role->Animation=ri.Attribute.at("animation");
	role->Head=ri.Attribute.at("head");
	role->MaxHp=stoi( ri.Attribute.at("maxhp"));
	role->MaxMp=stoi(ri.Attribute.at("maxmp"));
	return role;
}


