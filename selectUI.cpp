#include "selectUI.h"
USING_NS_CC;
USING_NS_MGE;
USING_NS_UI;
USING_NS_TL;
USING_NS_CC_EXT;

selectUI::~selectUI()
{
}

selectUI * selectUI::createWithCases(const std::string & _headName, const std::string & _title, std::vector<std::string>&& _selectCases, std::map<const std::string, std::map<const std::string, const std::string>>&& _resultMap)
{
	auto sui = selectUI::create();
	auto visibleSize = Director::getInstance()->getVisibleSize();
/*	auto background = Sprite::create("UI/selectBackGround.png");
	sui->addChild(background, 0);
	background->setPosition({ visibleSize.width / 2.0f,visibleSize.height / 2.0f });
	background->setScale(
		(visibleSize.width / 2.0f) / background->getContentSize().width,
		(visibleSize.height / 2.0f) / background->getContentSize().height
		);
		*/

	auto head = trimImage("UI/trimTemplate.png",
		xmlCache::getInstance()->getXmlInfo("resource.xml",
			xmlCache::getInstance()->getXmlInfo("roles.xml", _headName).Attribute.at("head")
			).Attribute.at("value")+".png"
	);
	head->setPosition(
		visibleSize.width*2.0f / 8.0f,
		visibleSize.height*6.0f / 8.0f
	);
	sui->addChild(head);



	auto title = Label::createWithTTF(_title, "fonts/myfont.ttf", 24);
	title->setDimensions(visibleSize.width*3.5f/8.0f,visibleSize.height*1.5f/8.0f);
	title->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
	title->setAnchorPoint({ 0,0 });
	title->setPosition(visibleSize.width*3.0f / 8.0f,
		visibleSize.height*5.0f / 8.0f);
	title->setColor({ 255, 255, 255 });
	sui->addChild(title);








	sui->selectCases.swap(_selectCases);
	sui->resultMap.swap(_resultMap);
	auto tableView = TableView::create(sui, { visibleSize.width / 4.0f,visibleSize.height / 4.0f });
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition({ visibleSize.width*3.0f / 8.0f,visibleSize.height* 3.0f/ 8.0f });
	//this作为代理
	tableView->setDelegate(sui);
	//填充顺序,从上到下
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder
		::TOP_DOWN);
	sui->addChild(tableView);
	//加载Data
	tableView->reloadData();
	//tableView->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	tableView->setTouchEnabled(true);





	return sui;
}

bool selectUI::init()
{
	if(!Layer::init())
	return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	//this作为数据源
	listenerMouse = nullptr;

	schedule(CC_CALLBACK_1(selectUI::destory, this), "destroy");
	return true;
}
/*
void selectUI::scrollViewDidScroll(cocos2d::extension::ScrollView * view)
{
}

void selectUI::scrollViewDidZoom(cocos2d::extension::ScrollView * view)
{
}
*/
void selectUI::tableCellTouched(cocos2d::extension::TableView * table, cocos2d::extension::TableViewCell * cell)
{
	CCLOG("%d", cell->getIdx());
	const auto& re = resultMap.at(std::to_string(cell->getIdx()));
	storyParse::getInstance()->storyResultParse(this,
		re.at("type"),
		re.at("value")
	);
	status = destroy::DESTROY;
	//table->removeFromParentAndCleanup(true);
}

cocos2d::Size selectUI::tableCellSizeForIndex(cocos2d::extension::TableView * table, ssize_t idx)
{
	return cocos2d::Size(200,30);
}

cocos2d::extension::TableViewCell * selectUI::tableCellAtIndex(cocos2d::extension::TableView * table, ssize_t idx)
{
	//从重用队列中获取cell
	auto cell = table->dequeueCell();
	if (!cell) {
	//创建新的cell
		//cell = new(std::nothrow) TableViewCell();
		cell = TableViewCell::create();
	/*	auto sprite = Sprite::create("UI/labelUI.png");
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
		cell->addChild(sprite);
		*/
		auto label = Label::createWithTTF(selectCases[idx], "fonts/myfont.ttf", 24);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	} {
		auto label = dynamic_cast<Label*>(cell->getChildByTag(123));
		label->setString(selectCases[idx]);
	}
	return cell;

}

ssize_t selectUI::numberOfCellsInTableView(cocos2d::extension::TableView * table)
{
	return selectCases.size();
}
