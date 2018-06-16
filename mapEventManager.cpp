#include "mapEventManager.h"

USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;

std::unique_ptr<mapEventManager>& mapEventManager::getInstance()
{
	static std::once_flag oc;
	static std::unique_ptr<mapEventManager> MEM_instance;
	std::call_once(oc, [&] {
		//	_instance = std::make_unique<xmlCache>();
		MEM_instance.reset(new mapEventManager);
		MEM_instance->init();
	});
	return MEM_instance;
}

bool mapEventManager::in_team(const std::string & teamer)
{
	return true;
}

bool mapEventManager::should_not_finish(const std::string & storyName)
{
	return !storyParse::getInstance()->is_story_done(storyName);
}

bool mapEventManager::should_finish(const std::string & storyName)
{
	return storyParse::getInstance()->is_story_done(storyName);
}

bool mapEventManager::not_in_team(const std::string & teamer)
{
	return true;
}

bool mapEventManager::is_condition_true(const std::string & type, const std::string& value)
{
	if (eventTypeCallBack.find(type) == eventTypeCallBack.end())
    {
		eventTypeCallBack.insert(std::make_pair(
			type, std::bind(&mapEventManager::default_type, this, std::placeholders::_1)
		));
	}
	return eventTypeCallBack[type](value);
}

void mapEventManager::init()
{
	eventTypeCallBack.insert(std::make_pair(
		"in_team", std::bind(&mapEventManager::in_team, this, std::placeholders::_1)
	));
	eventTypeCallBack.insert(std::make_pair(
		"should_not_finish", std::bind(&mapEventManager::should_not_finish, this, std::placeholders::_1)
	));
	eventTypeCallBack.insert(std::make_pair(
		"should_finish", std::bind(&mapEventManager::should_finish, this, std::placeholders::_1)
	));
	eventTypeCallBack.insert(std::make_pair(
		"not_in_team", std::bind(&mapEventManager::not_in_team, this, std::placeholders::_1)
	));
}
