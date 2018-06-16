#pragma once
#ifndef _UI_OPERATOR_LAYER_H
#define _UI_OPERATOR_LAYER_H
#include "dialogUI.h"
#include"selectUI.h"
#include"MainMenuUI.h"
#include"UIInfo.h"
#include<memory>
_MGE_BEGIN
_UI_BEGIN

class UIoperatorLayer:public cocos2d::Layer {
private:
	std::queue<cocos2d::Layer*>UIqueue;
/*	static 
	std::unique_ptr<
		std::map < const std::string, std::function<cocos2d::Layer* (
			std::unique_ptr<UI::UICreateInfo>& 
			)>>
		>functionCallMap;
		*/
public:
	virtual bool init()override;
	CREATE_FUNC(UIoperatorLayer);
	/*
	static 
	void registerFuction(const std::string& UIname,
		const std::function<cocos2d::Layer*(std::unique_ptr<UI::UICreateInfo>&)>&func);
	void createUI(const std::string& UIname, std::unique_ptr<UI::UICreateInfo>&);

	*/
	void createSelectUI(const std::string& head,
		const std::string& titile,
		std::vector<std::string>&& selectCases,
		std::map<const std::string, std::map<const std::string, const std::string> >&& resultMap);
	void createDialogUI(const Tools::storyInfo& si );
	void createMainMenu(const cocos2d::Point& point,
		std::vector<cocos2d::Sprite*>& spriteVec,
		std::vector<std::function<void(cocos2d::Node*, cocos2d::EventMouse*)>>& callBackVec
	);
	void touchCheck(float f);
	bool IsQueueEmpty() { return UIqueue.empty(); }
	~UIoperatorLayer() {
		while (!UIqueue.empty()) {
			UIqueue.front()->release();
			UIqueue.pop();
		}
	}
};

_UI_END
_MGE_END
#endif // !_UI_OPERATOR_LAYER_H
