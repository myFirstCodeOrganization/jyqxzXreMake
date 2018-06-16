#include "mapLayer.h"

USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;

bool mapLayer::conditionParse(const std::unique_ptr<Tools::xmlnode>& pCondition)
{
	auto attr = pCondition->toAtrributeMap();
	return Tools::mapEventManager::getInstance()->is_condition_true(attr.at("type"), attr.at("value"));
}

bool mapLayer::MapEventParse( cocos2d::Label* eventNode,const location& loc, const std::unique_ptr<Tools::xmlnode>& pEvent)
{
	auto eventMap=pEvent->toAtrributeMap();
	if ( stoi(eventMap.at("probability")) == 100) {
		auto eventConditions = pEvent->toChildElementVector();
		for (const auto & pCondition : eventConditions)
			if (!conditionParse(pCondition)) return false;
		if (eventMap.at("type") == std::string("map"))
		{
			mapVec.insert(std::make_pair(loc, eventInfo( eventType::map ,eventMap.at("value") )));
			eventNode->setPosition(getNodePosition(loc));
			mapNodeLayer->addChild(eventNode, 5);
			return true;
		}
		if (eventMap.at("type") == std::string("story")) {
			mapVec.insert(std::make_pair(loc, eventInfo(eventType::story, eventMap.at("value"))));
			eventNode->setPosition(getNodePosition(loc));
			mapNodeLayer->addChild(eventNode, 5);
			return true;
		
		}
	}
	return false;
}

mapLayer * mapLayer::createWithMapInfo(const Tools::mapInfo & mi)
{
	auto ml = create();
	
	if (ml) {
		loadBackGround(ml, xmlCache::getInstance()->getXmlInfo("resource.xml", mi.Attribute.at("pic")).Attribute.at("value")+".jpg");
		ml->mapNodeLayer = Layer::create();
		ml->addChild(ml->mapNodeLayer, 4, "mapNodeLayer");
		auto mapUnits = mi.self->toChildElementVector();
		for (const auto& c : mapUnits) {
			auto mapUnitAttr = c->toAtrributeMap();
			if (!mapUnitAttr.empty()) {
				auto Flb = Label::createWithTTF(mapUnitAttr.at("name"), "fonts/myfont.ttf", 15);
				auto vec2 = ml->getNodeVec2(stoi(mapUnitAttr.at("x")), stoi(mapUnitAttr.at("y")));
				int offsetX = 5;
				
				while (true) {	
					if (ml->mapVec.find(vec2) == ml->mapVec.end()) {
						auto events = c->toChildElementMultiMap("type");
						static std::vector<std::string> __mapEventTypeVec = { "story","map" };
						bool is_true = false;
						for (const auto &str : __mapEventTypeVec) {
							if (is_true)
								break;
							auto rangeStory = events.equal_range(str);
							for (auto it1 = rangeStory.first;it1 != rangeStory.second;it1++) {
								if (ml->MapEventParse(Flb, vec2, it1->second)) {
									is_true = true;
									break; 
								}
							}
						}

						break;
					}
					else
					{
						vec2.x+= offsetX;
						if (vec2.x> ml->xBlockNum)break;

					}
				}
			}



		}
	}
	return ml ;
}

bool mapLayer::init()
{
	if(!Layer::init())
	return false;
	UIPL = UI::UIoperatorLayer::create();
	this->addChild(UIPL,10);
	this->schedule(CC_CALLBACK_1(mapLayer::longTouch, this),"longTouch");
    is_on_touch = false;
	return true;
}

void mapLayer::onExit()
{
	Layer::onExit();
	if (listenerMouse) {
		_eventDispatcher->removeEventListener(listenerMouse);
		_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true);

	}
}

void mapLayer::setBackGround(const std::string & backGround)
{
	auto bc = this->getChildByName("bg_image");
	if (mapNodeLayer != nullptr) {
		mapNodeLayer->removeAllChildren();
	}
	if (bc) {
		bc->removeFromParent();
	}
	Tools::loadBackGround(this, backGround);

}

const location mapLayer::getNodeVec2(const float x, const float y)
{
	if (x > 0 && y > 0) {
		float xScale = x / visibleSize.width;
		float yScale = y / visibleSize.height;
		int _x = floor(xScale * xBlockNum);
		int _y = floor(yScale * yBlockNum);
		return { _x,_y };
	}
	else {
		return {3 ,static_cast<int>(floor(0.5f*yBlockNum)) };
	}
}
cocos2d::Vec2 mapLayer::getNodePosition(const location& vec)
{
	float xScale = visibleSize.width / static_cast<float>(xBlockNum);
	float yScale = visibleSize.height / static_cast<float>(yBlockNum);
	return { xScale*vec.x+visibleSize.width/static_cast<float>(xBlockNum*2),
		yScale*vec.y + visibleSize.height / static_cast<float>(yBlockNum*2)};
}

void mapLayer::longTouch(float)
{
	if (is_on_touch ) {
		if (this->getChildByName("UI") != nullptr) {
			is_on_touch = false;
			return;
		}
		auto end = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(end - TouchTime).count() > 700)
		{
			is_on_touch = false;
	  	    std::vector<cocos2d::Sprite*> sVec;
			for (int i = 0; i != 4; i++) {

				auto sprite= trimImage(CV::templateImage, "UI/mainMenuSprite.png");
				sprite->retain();
				sVec.push_back(sprite);
			}
			auto f = [](cocos2d::Node* node, cocos2d::EventMouse* event) {
				node->removeFromParent();
			};
			std::vector<std::function<void(cocos2d::Node*, cocos2d::EventMouse*)>>
				cbVec = {
				f,f,f,f
			};
			UIPL->createMainMenu(TouchedPoint,sVec,cbVec);
			return;

		}
	
	
	
	}
}




void mapLayer::onEnter()
{
	Layer::onEnter();
	if (listenerMouse == nullptr) {
		listenerMouse = EventListenerMouse::create();
		listenerMouse->onMouseUp = [this](EventMouse* event) {
			is_on_touch = false;
		};

		listenerMouse->onMouseDown= [this](EventMouse* event) {
			this->TouchedPoint = event->getLocationInView();
			TouchTime = std::chrono::steady_clock::now();
			is_on_touch = true;
			if (mapNodeLayer->getChildren().empty()
				&& this->getChildByName("UI") == nullptr
				&& this->getUIPL()->IsQueueEmpty()
				) {
				const auto & mi = xmlCache::getInstance()->getXmlInfo("maps.xml",
					Tools::to_uft8(L"´óµØÍ¼"));
				if (mi.self != nullptr) {
					auto nextMap = mapLayer::createWithMapInfo(mi);
					auto parent = this->getParent();
					parent->addChild(nextMap);
					this->removeFromParent();
					return;
				}
			}
			auto vec2=event->getLocationInView();
			auto glBlockVec2 = getNodeVec2(vec2.x,vec2.y);
			if (mapVec.find(glBlockVec2) != mapVec.end()) {
				auto ei= mapVec.at(glBlockVec2);
				if (ei.getType() == eventType::map) {
					const auto & mi = xmlCache::getInstance()->getXmlInfo("maps.xml",ei.getString());
					if (mi.self != nullptr) {
						auto nextMap = mapLayer::createWithMapInfo(mi);
						auto parent = this->getParent();
						parent->addChild(nextMap);
						this->removeFromParent();
					}
					return;
				}
				if (ei.getType() == eventType::story) {
					const auto& si = xmlCache::getInstance()->getXmlInfo("storys.xml", ei.getString());
					this->UIPL->createDialogUI(si);
					
					//auto duiInfo = UI::createDialogCreateInfo(si);
					//this->UIPL->createUI("DialogUI",duiInfo);
				}
			}


		};
	}
	if (listenerMouse) {
		_eventDispatcher->pauseEventListenersForTarget(this->getParent(), true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
	}
}

