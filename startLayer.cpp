#include "startLayer.h"
#include"ui/CocosGUI.h"

USING_NS_MGE;
USING_NS_CC;
startLayer::startLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg_image = Sprite::create("open/opengame.jpg");
	if (Tools::not_nullptr(bg_image)) {
		bg_image->setScale(visibleSize.width / bg_image->getContentSize().width,
			visibleSize.height / bg_image->getContentSize().height);
		bg_image->setAnchorPoint({ 0, 0 });
		bg_image->setPosition(origin);
		addChild(bg_image, 1,"bg_image");
	}

	auto title = Label::createWithTTF(Tools::to_uft8(L"测试游戏"), "fonts/myfont.ttf", 30);
	if (Tools::not_nullptr(title)) {
		title->setColor({ 0,0,0 });
		title->setAnchorPoint({ 0.5f,0.5f });
		title->setPosition(origin.x + visibleSize.width / 2,
			origin.y + 3.5f / 4.0f*visibleSize.height);
		addChild(title, 2,"title");
	}
	int tag = 0;
	auto menu = Menu::create(nullptr);
	float dtime = 1.0;
	std::wstring menu_txt[] = { L"开始游戏",L"载入游戏",L"系统设置",L"退出游戏" };
	for (auto &str : menu_txt) {
		auto botton_txt = Label::createWithTTF(Tools::to_uft8(str), "fonts/myfont.ttf", 20);
		if (Tools::not_nullptr(botton_txt)) {
			botton_txt->setColor({ 255,201,14 });
		}
		auto botton = MenuItemLabel::create(botton_txt);
		menu->addChild(botton,3,tag);
		tag++;
		botton->setOpacity(0);
		botton->runAction(
		  Sequence::create(	
			  DelayTime::create(dtime),
			  FadeIn::create(1),
			  nullptr
		  )
		);
		dtime += 0.5;

	}
	menu->alignItemsVertically();
	menu->setAnchorPoint({ 0.5f,0.5f });
	menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height *2.0f / 4.0f);
	auto startgame = menu->getChildByTag(0);
	dynamic_cast<MenuItemLabel*>(startgame)->setCallback(
		CC_CALLBACK_1(startLayer::startgameCallback, this)
	);
	auto endgame = menu->getChildByTag(3);
	dynamic_cast<MenuItemLabel*>(endgame)->setCallback(
		CC_CALLBACK_1(startLayer::endCallback,this)
	);
	dynamic_cast<MenuItemLabel*>(menu->getChildByTag(2))
		->setCallback(
			CC_CALLBACK_1(startLayer::systemCallback, this)
		);
	addChild(menu, 2,"menu");
}

void startLayer::endCallback(Ref*)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void startLayer::systemCallback(Ref*)
{
	dynamic_cast<LayerMultiplex*> (this->getParent())->switchTo(1, false);
}

void startLayer::startgameCallback(Ref *)
{
	
	Director::getInstance()->replaceScene(sceneTransition<gameMainScene>::create());
}


void systemSetLayer::soundCallback(Ref * psend)
{
}

void systemSetLayer::qualityCallback(Ref * psend)
{
}

void systemSetLayer::backCallback(Ref * psend)
{
	dynamic_cast<LayerMultiplex*>(this->getParent())
		->switchTo(0, false);
}

systemSetLayer::systemSetLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemFont::setFontName("fonts/myfont.ttf");
	MenuItemFont::setFontSize(24);
	auto title_sound = MenuItemFont::create(Tools::to_uft8(L"声音"));
	title_sound->setEnabled(false);
	auto content_sound = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(systemSetLayer::soundCallback, this),
		MenuItemFont::create(Tools::to_uft8(L"开")),
		MenuItemFont::create(Tools::to_uft8(L"关")),
		nullptr
	);

	auto title_quality = MenuItemFont::create(Tools::to_uft8(L"游戏画质"));
	title_quality->setEnabled(false);
	auto content_quality = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(systemSetLayer::qualityCallback, this),
		MenuItemFont::create(Tools::to_uft8(L"低")),
		MenuItemFont::create(Tools::to_uft8(L"中")),
		MenuItemFont::create(Tools::to_uft8(L"高")),
		nullptr
	);
	auto back = MenuItemFont::create(Tools::to_uft8(L"返回"));
	back->setCallback(CC_CALLBACK_1(systemSetLayer::backCallback, this));
	auto menu = Menu::create(
		title_sound, content_sound,
		title_quality, content_quality,
		back,
		nullptr
	);
	menu->alignItemsInColumns(2, 2,1);
	menu->setPosition({ origin.x + visibleSize.width*2.0f / 4.0f,
		origin.y + visibleSize.height*3.0f / 4.0f });

	back->setPosition({ origin.x + 3.5f / 8.0f*visibleSize.width,origin.y - visibleSize.height*5.5f / 8.0f });
	addChild(menu);

	auto sound_slider = ui::Slider::create();
	sound_slider->loadBarTexture("UI/sliderTrack.png");
	sound_slider->loadProgressBarTexture("UI/sliderProgress.png");
	sound_slider->loadSlidBallTextures(
		"UI/sliderThumb.png",
		"UI/sliderThumb.png", ""
	);
	sound_slider->setMaxPercent(100);
	sound_slider->addEventListener(
		[](Ref*psend, ui::Slider::EventType et) {
		if (et == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
			auto slider = dynamic_cast<ui::Slider*>(psend);
			int percent = slider->getPercent();
			log("%d\n", percent);
		}
	
	
	}
	);
	sound_slider->setScale(0.5f,0.5f);
	sound_slider->setPosition({ origin.x + visibleSize.width / 2.0f,origin.y + visibleSize.height*1.0f / 4.0f });
	this->addChild(sound_slider);

}

