#pragma once
#ifndef _MAP_EVENT_MANAGER_H
#define	_MAP_EVENT_MANAGER_H
#include"storyParse.h"
_MGE_BEGIN
_TOOLS_BEGIN

class mapEventManager {
private:
	std::map<const std::string,
		std::function<bool(const std::string&)>> eventTypeCallBack;
public:
	static std::unique_ptr<mapEventManager>& getInstance();
	bool in_team(const std::string& teamer);
	bool should_not_finish(const std::string& storyName);
	bool should_finish(const std::string& storyName);
	bool not_in_team(const std::string& teamer);
	bool default_type(const std::string& ) { return false; }
	bool is_condition_true(const std::string& type,const std::string& value);

	void init();
	mapEventManager(const mapEventManager&) = delete;
	mapEventManager operator=(const mapEventManager&) = delete;
	~mapEventManager() {};

private:
	mapEventManager() :eventTypeCallBack() {}





};



_TOOLS_END
_MGE_END
#endif // !_MAP_EVENT_MANAGER_H
