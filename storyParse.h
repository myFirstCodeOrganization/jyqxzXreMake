#pragma once
#ifndef _STORY_PARSE_H
#define _STORY_PARSE_H
#include"mapLayer.h"
#include"selectUI.h"
#include<algorithm>
_MGE_BEGIN
_TOOLS_BEGIN

class storyParse {
private:
	std::set<std::string> doneStory;
	std::map<const std::string,
		std::function<void (cocos2d::Layer*,const std::string&)>> storyTypeCallBack;
public:
	static std::unique_ptr<storyParse>& getInstance();
	void dialog(cocos2d::Layer* dui,const std::string& dialogText);
	void map(cocos2d::Layer* dui,const std::string& mapName);
	void backGround(cocos2d::Layer* dui,const std::string& backGroundName);
	void story(cocos2d::Layer* dui,const std::string& storyName);
	void leave(cocos2d::Layer* dui, const std::string& value);
	void select(cocos2d::Layer* dui, const std::string& value);
	void default_type(cocos2d::Layer* dui,const std::string& str) { return dialog(dui,str); }

	//Action和result 没有区别写在一起的
	void storyActionParse(cocos2d::Layer* dui,const std::string& type,const std::string& value);
	
	void storyResultParse(cocos2d::Layer* sui, const std::string&type, const std::string& value);
	
	void has_done_story(const std::string& storyName);
	bool is_story_done(const std::string& storyName);
	void init();
	storyParse(const storyParse  &) = delete;
	storyParse  operator=(const storyParse &) = delete;
	~storyParse() {};

private:
	storyParse() :storyTypeCallBack(), doneStory() {}







};


//没有用,延迟释放类
class delayRelease :public cocos2d::Node {
private:
	cocos2d::Node* node;
public:
	CREATE_FUNC(delayRelease);
	static delayRelease* createWithNode(cocos2d::Node* _node, float f) {
		auto dr = delayRelease::create();
		dr->node = _node;
		dr->scheduleOnce(schedule_selector(delayRelease::destroy), f);
		return dr;
	}
	void destroy(float f) {

		node->removeFromParent();
		this->removeFromParent();
	}
};





_TOOLS_END
_MGE_END
#endif


