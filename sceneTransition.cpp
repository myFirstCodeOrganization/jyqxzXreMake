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
		float cu = progress1->getPercentage();  //��ȡ�ٷֱ�     
		cu = cu + 1.0f;  //���������� ÿ�μ�1%      
		progress1->setPercentage(cu);

		if (cu <= 100)    //�������С�ڵ���100%  
		{
			auto str1 = String::createWithFormat("%.2f%%", cu);
			numsTTF->setString(str1->getCString());  //���ñ�ǩ��ʾ����
		}
		//����������ﵽ100%����ֹͣ
		else
		{
			unschedule("progress");//ֹͣĬ�ϵ�����
			Director::getInstance()->replaceScene(nextscene);
		}

	}, "progress");  //Ĭ�ϵ�����������update()����
	return true;
}
*/