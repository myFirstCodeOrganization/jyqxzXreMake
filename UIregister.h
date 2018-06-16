#pragma once
#ifndef UIREGISTER_H
#define UIREGISTER_H
#include"UIOperatorLayer.h"
#include"dialogUI.h"
#include"selectUI.h"
#include"MainMenuUI.h"
#include"UIInfo.h"
_MGE_BEGIN
_UI_BEGIN
/*
class UIregister {
public:
	cocos2d::Layer* createDialog(std::unique_ptr<UI::UICreateInfo>& uii1);
	cocos2d::Layer* createSelect(std::unique_ptr<UI::UICreateInfo>&  uii4);
	cocos2d::Layer* createMainMenueUI(std::unique_ptr<UI::UICreateInfo>&  uii3);
	UIregister() {
	UI::UIoperatorLayer::registerFuction("DialogUI", 
		std::bind(&UI::UIregister::createDialog,this,std::placeholders::_1)
    );
	UI::UIoperatorLayer::registerFuction("SelectUI",
		std::bind(&UI::UIregister::createSelect, this, std::placeholders::_1)
	);
	UI::UIoperatorLayer::registerFuction("MainMenuUI",
		std::bind(&UI::UIregister::createMainMenueUI, this, std::placeholders::_1)
	);
}
};


static UIregister __function_register;
/*
@param1 the pointer of stroyInfo 
*/
/*
std::unique_ptr<UI::UICreateInfo>  createUIInfo(Any p1) {
	std::unique_ptr<UI::UICreateInfo>p(new  UI::UIInfo_one);
	any_cast<array_one>(p->getParams())[0] = p1;
	return p;
}
std::unique_ptr<UI::UICreateInfo>  createUIInfo(Any p1, Any p2) {
	std::unique_ptr<UI::UICreateInfo>p(new  UI::UIInfo_two);
	any_cast<array_one>(p->getParams())[0] = p1;
	any_cast<array_one>(p->getParams())[1] = p2;
	return p;
}
std::unique_ptr<UI::UICreateInfo>  createUIInfo(Any p1, Any p2, Any p3) {
	std::unique_ptr<UI::UICreateInfo>p(new  UI::UIInfo_three);
	any_cast<array_one>(p->getParams())[0] = p1;
	any_cast<array_one>(p->getParams())[1] = p2;
	any_cast<array_one>(p->getParams())[2] = p3;
	return p;
}
std::unique_ptr<UI::UICreateInfo>  createUIInfo(Any p1, Any p2, Any p3, Any p4) {
	std::unique_ptr<UI::UICreateInfo>p(new  UI::UIInfo_four);
	any_cast<array_one>(p->getParams())[0] = p1;
	any_cast<array_one>(p->getParams())[1] = p2;
	any_cast<array_one>(p->getParams())[2] = p3;
	any_cast<array_one>(p->getParams())[3] = p4;
	return p;
}
std::unique_ptr<UI::UICreateInfo>  createUIInfo(Any p1, Any p2, Any p3, Any p4, Any p5) {
	std::unique_ptr<UI::UICreateInfo>p(new  UI::UIInfo_five);
	any_cast<array_one>(p->getParams())[0] = p1;
	any_cast<array_one>(p->getParams())[1] = p2;
	any_cast<array_one>(p->getParams())[2] = p3;
	any_cast<array_one>(p->getParams())[3] = p4;
	any_cast<array_one>(p->getParams())[4] = p5;
	return p;
}
std::unique_ptr<UI::UICreateInfo>  createDialogCreateInfo(const Tools::storyInfo& psi) {
	return createUIInfo(Any(const_cast<Tools::storyInfo*>(&psi)));
}
std::unique_ptr<UI::UICreateInfo>  createSelectCreateInfo
(   std::string& _headName,
	std::string& _title,
	std::vector<std::string>&& _selectCases,
	std::map<const std::string, std::map<const std::string, const std::string> >&& _resultMap) {
	return createUIInfo(
		Any(&_headName),
		Any(&_title),
		Any(&_selectCases),
		Any(&_resultMap)
	);
}
std::unique_ptr<UI::UICreateInfo>  createMainMenuCreateInfo
(   cocos2d::Point& point,
	std::vector<cocos2d::Sprite*>& spriteVec,
	std::vector<std::function<void(cocos2d::Node*, cocos2d::EventMouse*)>>& callBackVec) {
	return createUIInfo(
		Any(& point),
		Any(& spriteVec),
		Any(& callBackVec)
	);
}



*/
_UI_END
_MGE_END



#endif