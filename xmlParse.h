#pragma once
#ifndef XML_PARSE_H
#define XML_PARSE_H
#include"normalTools.h"
#include"xmlinfo.h"
#include<memory>
#include<string>
#include<map>
#include<unordered_map>
#include<atomic>
_MGE_BEGIN
_TOOLS_BEGIN
class xmlCache {
private:
	std::map<const std::string, std::unique_ptr<tinyxml2::XMLDocument> > mapDoc;
	std::map< const std::string,
		std::map<const std::string,std::unique_ptr< xmlInfo >>> xmlcache;

public:
	static std::unique_ptr<xmlCache>& getInstance();
	void loadFile(const std::string& str);
	void makeFileCache(const std::string& sourceFile, const std::string& key);
	const xmlInfo& getXmlInfo(const std::string& xmlName, const std::string&keyName);
	tinyxml2::XMLElement* getFileRoot(const std::string& sourceFile);
	const xmlInfo& getXmlInfo(const std::string& xmlName, const std::wstring&keyName);


	void init();
	xmlCache(const xmlCache&) = delete;
	xmlCache& operator=(const xmlCache&) = delete;
	~xmlCache();
private:
	xmlCache() :mapDoc(),xmlcache() {}








};





_TOOLS_END
_MGE_END
#endif // !XML_PARSE_H
