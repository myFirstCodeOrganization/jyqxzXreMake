#pragma once
#ifndef _SCENE_TRANSITION_H
#define _SCENE_TRANSITION_H
#include"tools.h"
#include<thread>
_MGE_BEGIN
template<class NextScene>
class sceneTransition:public cocos2d::Scene {
public:
	CREATE_FUNC(sceneTransition);
	sceneTransition() :progress1(nullptr), numsTTF(nullptr), nextscene(nullptr), percent(0),
		mtx(), texture(), com_t(false), plist(), com_p(false), spriteFrame(), com_s(false),everycase(50.0f),count_plist(0)
	,count_texture(0) {};
	//sceneTransition* setNextscene(cocos2d::Scene* node);
	~sceneTransition();
	virtual bool init() override;
	bool initWithResource();

private:
	cocos2d::ProgressTimer* progress1;
	cocos2d::Label* numsTTF;
	NextScene* nextscene;
	float percent;
	std::mutex mtx;
	std::vector<std::string> texture;
	bool com_t;
	std::vector<std::string> plist;
	bool com_p;
	std::vector<std::string> spriteFrame;
	bool com_s;
	float everycase;
	int count_texture;
	int count_plist;
};

template<class NextScene>
inline sceneTransition<NextScene>::~sceneTransition()
{
	//cocos2d::Director::getInstance()->getTextureCache()->removeUnusedTextures();

}

template<class NextScene>
bool
sceneTransition<NextScene>::init() {
	if (!Scene::init())
		return false;
	initWithResource();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//创建一个进度条精灵边框  
	Tools::loadBackGround(this, "background/scenetransition.jpg");
	auto progressbgSprite = Sprite::create("UI/sliderTrack.png");
	progressbgSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(progressbgSprite, 1);

	//创建一个进度条精灵 
	auto progressSprite = Sprite::create("UI/sliderProgress.png");
	progress1 = ProgressTimer::create(progressSprite);
	progress1->setType(ProgressTimer::Type::BAR);
	progress1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//进度动画运动方向，可以多试几个值，看看效果  
	progress1->setMidpoint(Vec2(0, 0));
	//进度条宽高变化  
	progress1->setBarChangeRate(Vec2(1, 0));
	progress1->setPercentage(0); //设置进度条百分比为0%     
	this->addChild(progress1, 1);
	numsTTF = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 18);
	numsTTF->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(numsTTF, 1);
	schedule([&](float f) {   
		float cu = progress1->getPercentage();
		if (!com_t || !com_p)    
		{
			progress1->setPercentage(percent);
			auto str1 = String::createWithFormat("%.2f%%", cu);
			numsTTF->setString(str1->getCString());  //设置标签显示内容
		}
		else {
			nextscene = NextScene::create();
			percent = 100;
			progress1->setPercentage(percent);
			unschedule("progress");//停止默认调度器
			Director::getInstance()->replaceScene(nextscene);
		}

	}, "progress");  //默认调度器，调用update()方法
	return true;


}

template<class NextScene>
inline bool sceneTransition<NextScene>::initWithResource()
{
	Tools::LoadTexture<NextScene,Tools::has_getTextureResource<NextScene>::value>::doFunc(
	texture,percent,count_texture,com_t,everycase,mtx);

	Tools::LoadList<NextScene,Tools::has_getListResource<NextScene>::value>::doFunc(
	plist,percent,count_plist,com_p,everycase,mtx);
  
	return true;
}


_MGE_END








#endif // !_SCENE_TRANSITION_H

