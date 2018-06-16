#include "dialogUI.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_TL;
USING_NS_UI;
DialogUI::~DialogUI()
{
}
bool DialogUI::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto dialogBoxSize = Size{ visibleSize.width,visibleSize.height / 4 };
	if (!Layer::init())
		return false;
	this->setAnchorPoint(Vec2::ZERO);
	this->setPosition(Vec2::ZERO);

	if (!backGroundImage.empty()) {
		auto bci = Sprite::create(backGroundImage);
		bci->setAnchorPoint(Vec2::ZERO);
		bci->setPosition(Vec2::ZERO);
		bci->setContentSize(dialogBoxSize);
		this->addChild(bci, 0);
	}
	if (!textContent.empty()) {

		auto text = Label::createWithTTF(textContent, "fonts/myfont.ttf", 24);
		if (not_nullptr(text)) {
			text->setDimensions(0.6f*dialogBoxSize.width, 0.8f*dialogBoxSize.height);
			//text->setLineBreakWithoutSpace(true);
			//text->setMaxLineWidth(1000);
			text->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
			text->setAnchorPoint({ 0,0 });
			text->setPosition(0.2f*dialogBoxSize.width, 0.1f*dialogBoxSize.height);
			text->setColor({ 0, 0, 0 });
			this->addChild(text, 20, "text");
		}

	}
	auto head = trimImage("UI/trimTemplate.png",
		xmlCache::getInstance()->getXmlInfo("resource.xml",
			xmlCache::getInstance()->getXmlInfo(
				"roles.xml", Tools::to_uft8(L"Ö÷½Ç")
			).Attribute.at("head")
		).Attribute.at("value")+".png"
	);

	head->setPosition({ dialogBoxSize.height / 2.0f,dialogBoxSize.height / 2.0f });

	//	head->setContentSize(Size{ 0.25f*dialogBoxSize.width,0.9f* dialogBoxSize.height });
	this->addChild(head, 20, "head");
	return true;
}


DialogUI * DialogUI::createWithStoryInfo(const Tools::storyInfo & si)
{
	auto DUI = DialogUI::create();
	//DUI->setBackGroundImage();
	if (si.self != nullptr) {
		storyParse::getInstance()->has_done_story(si.Attribute.at("name"));
		auto storyVector=si.self->toChildElementVector();

		for (const auto& storyUnit : storyVector) {
			if (strcmp(storyUnit->getPtr()->Name(), "action") == 0) {
				auto acAttr = storyUnit->toAtrributeMap();
				DUI->actionQueue.push(std::move(acAttr));
			
			}
			if (strcmp(storyUnit->getPtr()->Name(), "result") == 0) {
				auto reAttr = storyUnit->toAtrributeMap();
				const std::string ret = reAttr.at("ret");
				DUI->resultMap.insert(std::make_pair( ret,std::move(reAttr)));
				
			}
		}

		if (DUI->resultMap.empty()) {
			std::map<const std::string, const std::string> reAttr = { {"value",""},{"type","leave"} };
			DUI->resultMap.insert(std::make_pair("0", std::move(reAttr)));

		}
	}
	return DUI;
}

void DialogUI::setBackGroundImage(const std::string & _backGroundImage)
{
	backGroundImage = _backGroundImage;
}

void DialogUI::setText(const std::string & _text)
{
	auto it2 = std::find(_text.begin(), _text.end(),'#');
	if (it2 != _text.end()) {
		const auto& role = xmlCache::getInstance()->getXmlInfo("roles.xml", std::string(_text.begin(), it2));
		if(role.self!=nullptr)
		setHead( xmlCache::getInstance()->getXmlInfo("resource.xml",
			role.Attribute.at("head")).Attribute.at("value")+std::string(".png"));
		else
			it2 = _text.begin();
	}
	else {
		it2 = _text.begin();
	}
	dynamic_cast<Label*>(this->getChildByName("text"))
		->setString(std::string(it2, _text.end()));
}

void DialogUI::setHead(const std::string & headName)
{
	auto head = dynamic_cast<cocos2d::ClippingNode*>(this->getChildByName("head"));
	if (head == nullptr) {
		//auto head = Tools::trimImage("UI/trimTemplate.png","Heads/zhujue2.png");
		
		//stencil->setAnchorPoint(Vec2::ZERO);
		//stencil->setPosition(Vec2::ZERO);
	}
	else {
		dynamic_cast<Sprite*>(head->getChildByName("headSprite"))
			->setTexture(Director::getInstance()->getTextureCache()->addImage(headName));
	}
//	head->setTexture(Director::getInstance()->getTextureCache()->addImage(headName));
}

void DialogUI::setTitle(const std::string & _title)
{
	title = _title;
}

void DialogUI::nextVisibleAction()
{
	std::string str;
	while (!this->actionQueue.empty()) {
		str = this->actionQueue.front().at("type");
		auto action = std::move(actionQueue.front());
		this->actionQueue.pop();
		storyParse::getInstance()->storyActionParse(
			this,action.at("type"),action.at("value"));
		if (str == "DIALOG" || str == "SELECT" || str == "BATTLE")
			return;


	}
}

void DialogUI::onEnter()
{
	Layer::onEnter();
	if (listenerMouse == nullptr) {
		listenerMouse = EventListenerMouse::create();
		listenerMouse->onMouseDown = [this](EventMouse* event) {
			if (!actionQueue.empty()) {
				nextVisibleAction();
			}
			else{
				this->retain();
				storyParse::getInstance()->storyResultParse(
					this, resultMap.begin()->second.at("type"), resultMap.begin()->second.at("value"));
				this->removeFromParent();
				this->release();
			}
		};
	}
	if (listenerMouse) {
		_eventDispatcher->pauseEventListenersForTarget(this->getParent(), true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse,this);
	}
	nextVisibleAction();

}

void DialogUI::onExit()
{
	Layer::onExit();
	if (listenerMouse) {
		_eventDispatcher->removeEventListener(listenerMouse);
		_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true);
	
	}
	

}

void DialogUI::show()
{
}


