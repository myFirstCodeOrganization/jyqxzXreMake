#include "storyParse.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
std::unique_ptr<storyParse>& storyParse::getInstance()
{
	static std::once_flag oc;
	static std::unique_ptr<storyParse> SP_instance;
	std::call_once(oc, [&] {
		//	_instance = std::make_unique<xmlCache>();
		SP_instance.reset(new storyParse);
		SP_instance->init();
	});
	return SP_instance;
}

void storyParse::dialog(cocos2d::Layer* dui, const std::string & dialogText)
{
	dynamic_cast<UI::DialogUI*>(dui)->setText(dialogText);
}

void storyParse::map(cocos2d::Layer* dui, const std::string & mapName)
{
	const auto & mi = xmlCache::getInstance()->getXmlInfo("maps.xml", mapName);
	if (mi.self != nullptr) {
		auto nextMap = mapLayer::createWithMapInfo(mi);
		auto maplayer=  dui->getParent();
		maplayer->getParent()->addChild(nextMap);
		maplayer->removeFromParent();
	}
}

void storyParse::backGround(cocos2d::Layer*dui, const std::string & backGroundName)
{
	const auto& ri=xmlCache::getInstance()->getXmlInfo("resource.xml", backGroundName);
	dynamic_cast<mapLayer*>(dui->getParent())->setBackGround(ri.Attribute.at("value")+".jpg");
}

void storyParse::story(cocos2d::Layer* dui, const std::string & storyName)
{
	const auto& si=xmlCache::getInstance()->getXmlInfo("storys.xml", storyName);
	auto maplayer= dynamic_cast<mapLayer*>(dui->getParent());
	maplayer->getUIPL()->createDialogUI(si);
}

void storyParse::storyActionParse(cocos2d::Layer* dui,const std::string& type, const std::string & value)
{
	if (storyTypeCallBack.find(type) == storyTypeCallBack.end())
	{
		storyTypeCallBack.insert(std::make_pair(
			type, std::bind(&storyParse::default_type, this, std::placeholders::_1,std::placeholders::_2)
		));
	}
	return storyTypeCallBack[type](dui,value);
}

void storyParse::storyResultParse(cocos2d::Layer * dui, const std::string & type, const std::string & value)
{
	if (storyTypeCallBack.find(type) == storyTypeCallBack.end())
	{
		storyTypeCallBack.insert(std::make_pair(
			type, std::bind(&storyParse::default_type, this, std::placeholders::_1, std::placeholders::_2)
		));
	}
	return storyTypeCallBack[type](dui, value);
}

void storyParse::leave(cocos2d::Layer*dui, const std::string & value)
{
}

void storyParse::select(cocos2d::Layer * dui, const std::string & value)
{
	std::vector<std::string> vec;
	auto it1 = std::find(value.begin(), value.end(), '#');
	std::string head(value.begin(), it1);
	it1++;
	auto it2= std::find(it1, value.end(), '#');
	std::string title(it1, it2);
	auto it = it2+1;
	while (it != value.end())
	{
	it2= std::find(it, value.end(), '#');
	vec.emplace_back(it, it2);
	if (it2 == value.end())
		break;
	it = it2+1;
	}
	auto UIPL = dynamic_cast<mapLayer*> (dui->getParent())->getUIPL();
	auto dui2 = dynamic_cast<UI::DialogUI*>(dui);
	UIPL->createSelectUI(head,title,std::move(vec),
		std::move(dui2->resultMap)
		);
	dui2->removeFromParent();
}
void storyParse::has_done_story(const std::string & storyName)
{
	doneStory.insert(storyName);
}

bool storyParse::is_story_done(const std::string & storyName)
{
	return doneStory.find(storyName) == doneStory.end();
}

void storyParse::init()
{

	storyTypeCallBack.insert(std::make_pair(
		"DIALOG", std::bind(&storyParse::dialog, this, std::placeholders::_1, std::placeholders::_2)
	));
	storyTypeCallBack.insert(std::make_pair(
		"map", std::bind(&storyParse::map, this, std::placeholders::_1, std::placeholders::_2)
	));
	storyTypeCallBack.insert(std::make_pair(
		"BACKGROUND", std::bind(&storyParse::backGround, this, std::placeholders::_1, std::placeholders::_2)
	));
	storyTypeCallBack.insert(std::make_pair(
		"story", std::bind(&storyParse::story, this, std::placeholders::_1, std::placeholders::_2)
	));
	storyTypeCallBack.insert(std::make_pair(
		"leave", std::bind(&storyParse::leave, this, std::placeholders::_1, std::placeholders::_2)
	));
	storyTypeCallBack.insert(std::make_pair(
		"SELECT", std::bind(&storyParse::select, this, std::placeholders::_1, std::placeholders::_2)
	));
}
