#include "normalTools.h"
USING_NS_MGE;
USING_NS_CC;
USING_NS_TL;
bool not_nullptr(cocos2d::Node* node) {
	if (node == nullptr) {
		printf("bad load");
		return false;
	}
	return true;
}
const std::string to_uft8(std::wstring str) {
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(str);
}
void loadBackGround(cocos2d::Node * node, const std::string & str)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg_image = Sprite::create(str);
	if (Tools::not_nullptr(bg_image)) {
		bg_image->setScale(visibleSize.width / bg_image->getContentSize().width,
			visibleSize.height / bg_image->getContentSize().height);
		bg_image->setAnchorPoint({ 0, 0 });
		bg_image->setPosition(origin);
		node->addChild(bg_image, 0, "bg_image");
	}
}

cocos2d::ClippingNode * trimImage(const std::string & templateImage, const std::string & sourceImage)
{
	cocos2d::Sprite* stencil = cocos2d::Sprite::create(templateImage);
	cocos2d::ClippingNode* c_node = cocos2d::ClippingNode::create();
	c_node->setStencil(stencil);
	c_node->setInverted(false);
	c_node->setAlphaThreshold(0.0f);
	//需要剪裁的节点
	cocos2d::Sprite* sp = cocos2d::Sprite::create(sourceImage);
	c_node->addChild(sp);
	return c_node;
}
