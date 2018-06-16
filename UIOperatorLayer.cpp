#include "UIOperatorLayer.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
USING_NS_UI;
/*std::unique_ptr<std::map < const std::string, std::function<cocos2d::Layer* (std::unique_ptr<UI::UICreateInfo>&)
	>>>
UIoperatorLayer::functionCallMap (new
	std::map < const std::string, 
	std::function<cocos2d::Layer* (std::unique_ptr<UI::UICreateInfo>&)>
	>());
	*/
bool UIoperatorLayer::init()
{
	if(!Layer::init())
	return false;
	this->schedule(
		CC_CALLBACK_1(UIoperatorLayer::touchCheck, this),
		"touchCheck"
	);
	return true;
}
/*
void UIoperatorLayer::registerFuction(const std::string& UIname, const std::function<cocos2d::Layer*(std::unique_ptr<UI::UICreateInfo>&)>& func)
{
	functionCallMap->insert(std::make_pair(UIname, func));
}

void UIoperatorLayer::createUI(const std::string & UIname, std::unique_ptr<UI::UICreateInfo>&  pUI)
{
  UIqueue.push(functionCallMap->at(UIname)(pUI));
}


*/
void UIoperatorLayer::createSelectUI(const std::string & head, const std::string & titile, std::vector<std::string>&& selectCases, std::map<const std::string, std::map<const std::string, const std::string>>&& resultMap)
{
	auto sui = selectUI::createWithCases(
		head,
		titile,
		std::move(selectCases),
		std::move(resultMap)
	);
	sui->retain();
	UIqueue.push(sui);

}

void UIoperatorLayer::createDialogUI(const Tools::storyInfo & si)
{
	auto dui = DialogUI::createWithStoryInfo(si);
	dui->retain();
	UIqueue.push(dui);
}

void UIoperatorLayer::createMainMenu(const cocos2d::Point & point,  std::vector<cocos2d::Sprite*>& spriteVec,std::vector<std::function<void(cocos2d::Node*, cocos2d::EventMouse*)>>& callBackVec)
{
	auto mui = MainMenuUI::createWithPoint(point,spriteVec,callBackVec);
	mui->retain();
	UIqueue.push(mui);
}

void UIoperatorLayer::touchCheck(float f)
{
	if (this->getParent()->getChildByName("UI")==nullptr && !UIqueue.empty()) {
		this->getParent()->addChild(UIqueue.front(), 10,"UI");
		UIqueue.front()->release();
		UIqueue.pop();
	}
}
