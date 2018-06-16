#include "battleFieldLayer.h"

USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
USING_NS_TXML;
bool battleFieldLayer::init()
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bt_width = visibleSize.width*0.75f;
	bt_height = visibleSize.height*0.75f;
	ori_x = origin.x + (visibleSize.width - bt_width) / 2.0f;
	ori_y = origin.y + (visibleSize.height - bt_height) / 2.0f;
	eve_width = bt_width / max_x;
	eve_height = bt_height / max_y;
	for (int i = 0;i != max_x;i++) {
		battleField.push_back(std::vector<cocos2d::Point>());
		for (int j = 0;j != max_y;j++) {
			battleField.back().push_back(Point(ori_x + eve_width * (i + 0.5f), ori_y + eve_height * (j + 0.5f)));
		}
	}
	loadBackGround(this, "battleField/background/mybg.jpg");
	if (!roleInit())
		return false;
	operatorLayer = Layer::create();
	addChild(operatorLayer, 2);


	schedule(CC_CALLBACK_0(battleFieldLayer::runbf, this), "runbf");
	schedule(CC_CALLBACK_0(battleFieldLayer::update_everyone, this), "update_everyone");
	return true;
}

bool battleFieldLayer::roleInit()
{
	
	auto bs1 = battleSprite::createWithRole(
		Role::createWithRoleInfo(
			xmlCache::getInstance()->getXmlInfo("roles.xml", L"Ö÷½Ç")
		));

	bs1->setLocation({ 1,1 });
	bs1->setPosition(battleField[1][1]);
	bs1->setSp(15.0f);
	bs1->getRole()->getSprite()->setScale(0.5f,0.5f );
	battleSpriteVec.push_back(bs1);
	addChild(bs1, 3);

	auto bs2 = battleSprite::createWithRole(
		Role::createWithRoleInfo(
			(xmlCache::getInstance()->getXmlInfo("roles.xml",L"Ä¾Í·ÈË")
		)));
	bs2->setLocation({ 4,4 });
	bs2->setPosition(battleField[4][4]);
	bs2->setSp(15.0f);
	battleSpriteVec.push_back(bs2);
	bs2->getRole()->getSprite()->setScale(0.5f, 0.5f);
	addChild(bs2, 3);
	current = bs1;
	return true;
}

void battleFieldLayer::moveTo(location l, cocos2d::Ref *)
{
	current->setLocation(l);
	current->runAction(
		cocos2d::Sequence::create(
			cocos2d::CallFunc::create([this]() {
		operatorLayer->removeAllChildren();
	}),
			cocos2d::MoveTo::create(2.0f,
				battleField[l.x][l.y]),
		cocos2d::CallFunc::create([this]() {
		current->setStatus(battlestatus::ATTACK);
	}),
		nullptr
		));
}

void battleFieldLayer::attack(location l, cocos2d::Ref *)
{
	current->runAction(
		cocos2d::Sequence::create(
			cocos2d::CallFunc::create([this]() {
		operatorLayer->removeAllChildren();
	}),
			cocos2d::CallFunc::create([this,l] {
		showAttack(l);
	}),
		cocos2d::CallFunc::create([this]() {
		current->setStatus(battlestatus::REST);
	}),
		nullptr
		));

}

int battleFieldLayer::hurtResult(battleSprite * targetSprite)
{
	return current->getAttack()-targetSprite->getDefence();
}

void battleFieldLayer::showAttack(location l)
{
	auto targetSprite = getSprite(l);
	if (targetSprite != nullptr) {
		int hurt = hurtResult(targetSprite);
		targetSprite->setHp(targetSprite->getHp() - hurt);
		CCLOG("%s, -hp  %d", targetSprite->getName(), hurt);
	}
}

battleSprite * battleFieldLayer::getSprite(location l)
{
	for (auto & c : battleSpriteVec) {
		auto l1 = c->getlocation();
		if ( l1.x== l.x && l1.y==l.y)
			return c;
	}
	return nullptr;
}

void battleFieldLayer::runbf()
{
	if (current->getStatus() == battlestatus::MOVE) {
		auto l = current->getlocation();
		int n = current->getMoveAbility();
		int y = 0;
		std::vector<location> vec;
		while (n) {
			if (y > 0)
				for (int i = -(n - 1);i != n;i++)
					vec.push_back({ l.x + i,l.y + y });
			if ((-y) <= 0)
				for (int i = -(n - 1);i != n;i++)
					vec.push_back({ l.x + i,l.y - y });
			y++;
			n--;
		}

		for (auto& point : vec) {
			if (0 <= point.x  && point.x < static_cast<int>(battleField.size())
				&& 0 <= point.y && point.y < static_cast<int>(battleField[0].size())) {
				auto button1 = ui::Button::create("battleField/tukuai.png");
				button1->setPressedActionEnabled(true);
				button1->addClickEventListener(std::bind(&battleFieldLayer::moveTo, this, point, std::placeholders::_1));
				button1->setPosition(battleField[point.x][point.y]);
				button1->setScale(eve_width / (button1->getCustomSize().width),
					eve_height / (button1->getCustomSize().height));
				button1->setOpacity(128);
				operatorLayer->addChild(button1, 2);
			}
		}
		current->setStatus(battlestatus::ON_MOVE);
	}
	if (current->getStatus() == battlestatus::ATTACK) {
		auto l = current->getlocation();
		int n = current->getMoveAbility();
		int y = 0;
		std::vector<location> vec;
		while (n) {
			if (y > 0)
				for (int i = -(n - 1);i != n;i++)
					vec.push_back({ l.x + i,l.y + y });
			if ((-y) <= 0)
				for (int i = -(n - 1);i != n;i++)
					vec.push_back({ l.x + i,l.y - y });
			y++;
			n--;
		}

		for (auto& point : vec) {
			if (0 <= point.x  && point.x < static_cast<int>(battleField.size())
				&& 0 <= point.y && point.y < static_cast<int>(battleField[0].size())) {
				auto button1 = ui::Button::create("battleField/tukuai2.png");
				button1->setPressedActionEnabled(true);
				button1->addClickEventListener(std::bind(&battleFieldLayer::attack, this, point, std::placeholders::_1));

				button1->setPosition(battleField[point.x][point.y]);
				button1->setScale(eve_width / (button1->getCustomSize().width),
					eve_height / (button1->getCustomSize().height));
				button1->setOpacity(128);
				operatorLayer->addChild(button1, 2);
			}
		}
		current->setStatus(battlestatus::ON_ATTACK);
	}
}

void battleFieldLayer::update_everyone()
{
	if (current->getStatus() == battlestatus::REST)
	{
		float maxsp = 100.0f;
		for (auto p : battleSpriteVec) {
			p->setSpBar(p->getSpBar() + p->getSp());
			if (p->getSpBar() >= maxsp) {
				current = p;
				maxsp = p->getSpBar();
			}
		}
		if (current->getSpBar() >= maxsp) {
			current->setSpBar(maxsp - 100.0f);
			current->setStatus(battlestatus::MOVE);
		}
	}
}

battleFieldLayer::~battleFieldLayer()
{
}
