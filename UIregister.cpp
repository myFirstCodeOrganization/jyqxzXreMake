#include "UIregister.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
USING_NS_UI;
/*
cocos2d::Layer * UIregister::createDialog(std::unique_ptr<UI::UICreateInfo>&  uii1)
{
	return DialogUI::createWithStoryInfo(any_cast<storyInfo> (
		any_cast<array_one>(
			dynamic_cast<UIInfo_one*>(uii1.get())->getParams()
			)[0]
		)
	);
}

cocos2d::Layer * UIregister::createSelect(std::unique_ptr<UI::UICreateInfo>& uii4)
{
	auto& params=
		any_cast<array_four>
		(dynamic_cast<UIInfo_four*>(uii4.get())->getParams());
	return selectUI::createWithCases(
		any_cast<const std::string>(params[0]),
		any_cast<const std::string>(params[1]),
		std::move(any_cast<std::vector<std::string>>(params[2])),
		std::move(any_cast<std::map<const std::string, std::map<const std::string, const std::string> >>(params[3]))
		);
}

cocos2d::Layer * UIregister::createMainMenueUI(std::unique_ptr<UI::UICreateInfo>&  uii3)
{
	auto& params =
		any_cast<array_three>
		(dynamic_cast<UIInfo_four*>(uii3.get())->getParams());
	return MainMenuUI::createWithPoint(
		any_cast<const cocos2d::Point>(params[0]),
		any_cast<std::vector<cocos2d::Sprite*>>(params[1]),
		any_cast<
		std::vector<std::function<void(cocos2d::Node*, cocos2d::EventMouse*)>>>(params[2])
	);
}
*/