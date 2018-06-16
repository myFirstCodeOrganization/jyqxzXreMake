 #include "gameMainScene.h"
#include"battleFieldLayer.h"
#include"mapLayer.h"
USING_NS_CC;
USING_NS_MGE;
bool gameMainScene::init()
{
	if (!Scene::init()) {
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*auto tr = getTextureResource();
	auto cache = Director::getInstance()->getTextureCache();
	auto tf = Label::createWithTTF(Tools::to_uft8(L"开始游戏"), "fonts/myfont.ttf", 30);
	tf->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(tf);

	auto image = Sprite::createWithTexture(cache->getTextureForKey(tr[0]+".png"));
	addChild(image);
	auto role = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("Sha000_00.png")
	);
	role->setPosition({ origin.x + visibleSize.width / 2,origin.y + visibleSize.height });
	addChild(role);
	*/
	// auto bf=  battleFieldLayer::create();
	const auto& mi = Tools::xmlCache::getInstance()->getXmlInfo("maps.xml",L"大地图");
	auto ml = mapLayer::createWithMapInfo(mi);
	addChild(ml);
	return true;
}

gameMainScene::~gameMainScene()
{
	
}

std::vector<std::string> gameMainScene::getTextureResource()
{
	return std::vector<std::string>{
	"HelloWorld"
	};
}

std::vector<std::string> gameMainScene::getListResource()
{
	return std::vector<std::string>{
	"testxiana"
	};
}
