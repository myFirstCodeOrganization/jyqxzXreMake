#pragma once
#ifndef _NORMAL_TOOLS_H
#define _NORMAL_TOOLS_H
#include"config.h"
#include<string>
#include<locale>
#include<codecvt>
_MGE_BEGIN
_TOOLS_BEGIN
bool not_nullptr(cocos2d::Node* node) {
	if (node == nullptr) {
		printf("bad load");
		return false;
	}
	return true;
}
/*
作者：Gomo Psivarh
链接：https ://www.zhihu.com/question/39186934/answer/80443490
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
const std::string to_uft8(std::wstring str) {
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(str);
}
void loadBackGround(cocos2d::Node* node, const std::string& str) {
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	auto bg_image = cocos2d::Sprite::create(str);
	if (Tools::not_nullptr(bg_image)) {
		bg_image->setScale(visibleSize.width / bg_image->getContentSize().width,
			visibleSize.height / bg_image->getContentSize().height);
		bg_image->setAnchorPoint({ 0, 0 });
		bg_image->setPosition(origin);
		node->addChild(bg_image, 0, "bg_image");
	}

}
/*
作者：forestsenlin
链接：https://blog.csdn.net/forestsenlin/article/details/50100089
来源：csdn
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
cocos2d::Sprite* trimImage(const std::string& templateImage, const std::string& sourceImage)
{
	auto sprite = cocos2d::Sprite::create();
	cocos2d::ClippingNode* c_node = cocos2d::ClippingNode::create();
	cocos2d::Sprite* stencil = cocos2d::Sprite::create(templateImage);
	c_node->setStencil(stencil);
	c_node->setInverted(false);
	c_node->setAlphaThreshold(0.0f);
	c_node->setIgnoreAnchorPointForPosition(false);
//	c_node->setAnchorPoint({ 0.5f, 0.5f });
	//需要剪裁的节点
	cocos2d::Sprite* sp = cocos2d::Sprite::create(sourceImage);
	auto scX = stencil->getContentSize().width / sp->getContentSize().width;
	//auto scY= stencil->getContentSize().height / sp->getContentSize().height;
	stencil->setScale(1.0f/scX, 1.0f/scX);
	c_node->addChild(sp, 10, "headSprite");
//	c_node->setAnchorPoint({ 0.0f, 0.0f });
	//sprite->setIgnoreAnchorPointForPosition(false);
	//sprite->setAnchorPoint({ 0.5f, 0.5f });
	sprite->setContentSize(sp->getContentSize());
	sprite->setAnchorPoint({ 0.5f, 0.5f });
	sprite->setIgnoreAnchorPointForPosition(false);
	sprite->addChild(c_node,10,"c_node");
	return sprite;
}
     



_TOOLS_END
_MGE_END

#endif // !_NORMAL_TOOLS_H
