#pragma once
#ifndef XML_INFO_H
#define XML_INFO_H
#include"config.h"
#include"tinyxml2\tinyxml2.h"
_MGE_BEGIN
_TOOLS_BEGIN

class xmlnode {
private:
	tinyxml2::XMLElement* pXML;
public:
	//对 节点指针的弱引用
	xmlnode(tinyxml2::XMLElement* pxml) :pXML(pxml) {};
	std::map<const std::string, const std::string> toAtrributeMap() {
		std::map<const std::string, const std::string>attribute;
		for (auto chd = pXML->FirstAttribute();chd;chd = chd->Next())
			attribute.insert(std::make_pair(chd->Name(), chd->Value()));
		return attribute;
	};
	std::vector<std::unique_ptr<xmlnode>> toChildElementVector() {
		std::vector<std::unique_ptr<xmlnode>> childElement;
		for (auto chd = pXML->FirstChildElement();chd;chd = chd->NextSiblingElement()) {
			childElement.emplace_back( new xmlnode(chd) );
		}
		return childElement;
	}
	std::multimap<const std::string, std::unique_ptr<xmlnode>>
		toChildElementMultiMap(const std::string& key) {
		std::multimap<const std::string, std::unique_ptr<xmlnode>> childElement;
		for (auto chd = pXML->FirstChildElement();chd;chd = chd->NextSiblingElement()) {
			for(auto chdAttr=chd->FirstAttribute();chdAttr;chdAttr=chdAttr->Next())
				if ( strcmp(chdAttr->Name(),key.c_str())==0) {
					childElement.insert(std::make_pair(chdAttr->Value(), new xmlnode(chd)));
				}
		}
		return childElement;


	}



	const tinyxml2::XMLElement *
		getPtr() { return pXML; }
};
class xmlInfo {
public:
	std::unique_ptr<xmlnode> self;
	std::map<const std::string, const std::string> Attribute;
	xmlInfo() :self(nullptr), Attribute() {};
	xmlInfo(tinyxml2::XMLElement* pxml) :self(new xmlnode(pxml)), Attribute() {};
};

using roleInfo = xmlInfo;
using mapInfo = xmlInfo;
using storyInfo = xmlInfo;

enum class eventType {map,story};
class  eventInfo :public std::pair<eventType, std::string> {
public:
const std::string& getString() { return second; }
const eventType& getType() { return first; }
eventInfo(const eventType& et, const std::string& str) : std::pair<eventType, std::string>(et, str) {};
};







_TOOLS_END
_MGE_END




#endif