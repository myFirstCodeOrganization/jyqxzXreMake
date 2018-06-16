#include "xmlParse.h"
USING_NS_CC;
USING_NS_TL;

std::unique_ptr<xmlCache>& xmlCache::getInstance()
{
	static std::once_flag oc;
	static std::unique_ptr<xmlCache>_instance;
	std::call_once(oc, [&] {
	//	_instance = std::make_unique<xmlCache>();
		_instance.reset( new xmlCache);
		_instance->init();
	});
	return _instance;
}

void xmlCache::loadFile(const std::string & str)
{
	if (mapDoc.find(str) == mapDoc.end()) {
		 mapDoc.insert({ str,std::make_unique<tinyxml2::XMLDocument>() });
		 std::string path = FileUtils::getInstance()->fullPathForFilename(std::string("scripts/")+str);
		 if (FileUtils::getInstance()->isFileExist(path))
		     CCLOG("success: %s exist", path.c_str());
		 else
			 CCLOG("error: %s not exist file ", path.c_str());
		auto id= mapDoc[str]->LoadFile(path.c_str());
		if (id != 0) {
			CCLOG("%s  Load error", str.c_str());
		}
	}
}

void xmlCache::makeFileCache(const std::string & sourceFile,const std::string& key)
{
	auto doc = getFileRoot(sourceFile);
	if (doc == nullptr) {
		CCLOG("not load this file");
		return;
	}
	if(xmlcache.find(sourceFile)==xmlcache.end()){
		std::map<const std::string, std::unique_ptr< xmlInfo >> xmlParse;
		for (auto chdMap = doc->FirstChildElement();chdMap;chdMap = chdMap->NextSiblingElement())
		{
			std::unique_ptr<xmlInfo> pMI(new xmlInfo(chdMap));
			for (auto chdMapAttribute = chdMap->FirstAttribute();chdMapAttribute;chdMapAttribute = chdMapAttribute->Next())
			{
				pMI->Attribute.insert(std::make_pair(chdMapAttribute->Name(), chdMapAttribute->Value()));
			}
			std::string name = pMI->Attribute[key];
			if (name == "") {
				CCLOG("%s not this key,please check that is the key right");
			}
			xmlParse.insert(std::make_pair(name, std::move(pMI)));
		}
		xmlcache.insert(std::make_pair(
			sourceFile,std::move(xmlParse)
		));
	}
	else {
		CCLOG("file %s had been in cache ,you can't load again",sourceFile.c_str());
	}
	CCLOG("file load success!");
}
//此函数取消参数检查并自动插入,如果self为nullptr 则不存在
const xmlInfo& xmlCache::getXmlInfo(const std::string & xmlName, const std::string & keyName)
{
	if (xmlcache.at(xmlName).find(keyName) != (xmlcache.at(xmlName).end()))
		return *(xmlcache[xmlName][keyName]);
	else
	{
		static  xmlInfo __xmlFalseInfo;
		return __xmlFalseInfo;
	}
}

tinyxml2::XMLElement* xmlCache::getFileRoot(const std::string & sourceFile)
{
	loadFile(sourceFile);
	return mapDoc[sourceFile]->RootElement();
}

const xmlInfo& xmlCache::getXmlInfo(const std::string & xmlName, const std::wstring & keyName)
{
	return 	getXmlInfo(xmlName, Tools::to_uft8(keyName));
}

void xmlCache::init()
{
	std::vector<std::string> xmlName = {
	"maps.xml","storys.xml"
	};
	for (const auto& str : xmlName) {
		loadFile(str);
		makeFileCache(str, "name");
	}
	std::vector<std::string> xmlName2 = {
		"resource.xml","roles.xml"
	};
	for (const auto& str : xmlName2) {
		loadFile(str);
		makeFileCache(str, "key");
	}
}

xmlCache::~xmlCache()
{
	CCLOG("xmlCache destory");
}

