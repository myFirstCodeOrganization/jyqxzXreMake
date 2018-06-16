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
	//����һ������������߿�  
	Tools::loadBackGround(this, "background/scenetransition.jpg");
	auto progressbgSprite = Sprite::create("UI/sliderTrack.png");
	progressbgSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(progressbgSprite, 1);

	//����һ������������ 
	auto progressSprite = Sprite::create("UI/sliderProgress.png");
	progress1 = ProgressTimer::create(progressSprite);
	progress1->setType(ProgressTimer::Type::BAR);
	progress1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
	progress1->setMidpoint(Vec2(0, 0));
	//��������߱仯  
	progress1->setBarChangeRate(Vec2(1, 0));
	progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
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
			numsTTF->setString(str1->getCString());  //���ñ�ǩ��ʾ����
		}
		else {
			nextscene = NextScene::create();
			percent = 100;
			progress1->setPercentage(percent);
			unschedule("progress");//ֹͣĬ�ϵ�����
			Director::getInstance()->replaceScene(nextscene);
		}

	}, "progress");  //Ĭ�ϵ�����������update()����
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

