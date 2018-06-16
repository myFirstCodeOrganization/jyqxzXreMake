#pragma once
#ifndef _DIALOG_UI_H
#define _DIALOG_UI_H
#include"tools.h"
#include"storyParse.h"
#include<queue>
_MGE_BEGIN
_UI_BEGIN
class DialogUI: public cocos2d::Layer {
public:
	DialogUI():backGroundImage("UI/dialog.png"),listenerMouse(nullptr),textContent(Tools::to_uft8(L"Ä¬ÈÏÌî³ä×Ö¶Î")),title() {};
	~DialogUI();
	friend class  Tools::storyParse;
private:
	cocos2d::EventListenerMouse* listenerMouse;
	std::string backGroundImage;
	std::string textContent;
	std::queue<std::map<const std::string, const std::string> > actionQueue;
	std::map<const std::string,std::map<const std::string, const std::string> > resultMap;
	std::string title;
public:
	virtual bool init() override;
	CREATE_FUNC(DialogUI);
	static DialogUI* createWithStoryInfo(const Tools::storyInfo& si);
	void setBackGroundImage(const std::string& _backGroundImage= "UI/dialog.png");
	void setText(const std::string&_text);
	void setHead(const std::string& headName);
	void setTitle(const std::string& _title);
	void okMenuItemCallBack(Ref* pSender);
	void cancelMenuItemCallBack(Ref* pSender);
	void nextVisibleAction();

	virtual void onEnter() override;
	virtual void onExit() override;
	void show();


};


_UI_END
_MGE_END

#endif // !_DIALOG_UI_H
