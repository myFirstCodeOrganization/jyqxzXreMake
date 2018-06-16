#include "sceneTransition.h"
USING_NS_CC;
USING_NS_MGE;
/*
sceneTransition * sceneTransition::setNextscene(cocos2d::Scene * node)
{
	nextscene = node;
	node->retain();
	return this;
}
*/
/*
bool sceneTransition::init()
{
	if(!Scene::init())
	return false;
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
		float cu = progress1->getPercentage();  //获取百分比     
		cu = cu + 1.0f;  //进度条进度 每次加1%      
		progress1->setPercentage(cu);

		if (cu <= 100)    //如果进度小于等于100%  
		{
			auto str1 = String::createWithFormat("%.2f%%", cu);
			numsTTF->setString(str1->getCString());  //设置标签显示内容
		}
		//如果进度条达到100%，则停止
		else
		{
			unschedule("progress");//停止默认调度器
			Director::getInstance()->replaceScene(nextscene);
		}

	}, "progress");  //默认调度器，调用update()方法
	return true;
}
*/