#pragma once
#ifndef _SELECT_UI_H
#define _SELECT_UI_H
#include"storyParse.h"
#include"cocos-ext.h"
_MGE_BEGIN
_UI_BEGIN

enum class destroy {DESTROY,RUN};
class selectUI:public cocos2d::Layer,
	cocos2d::extension::TableViewDataSource,
    cocos2d::extension::TableViewDelegate{
private:
	cocos2d::EventListenerMouse* listenerMouse;
	std::map<const std::string, std::map<const std::string, const std::string> > resultMap;
	std::vector<std::string> selectCases;
	destroy status;
public:
	selectUI() :status(destroy::RUN),resultMap(),selectCases() {}
	~selectUI();
	CREATE_FUNC(selectUI);
	static selectUI* createWithCases(
		const std::string& _headName,
		const std::string& _titile,
		std::vector<std::string>&& _selectCases,
		std::map<const std::string, std::map<const std::string, const std::string> >&& _resultMap
	);
	virtual bool init()override;
/*	//当滑动tableview的时候触发的方法,参数为被触摸的 tableview
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override ;
	//当tableview 被缩放的时候触发该方法,参数为当前tableview
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
	*/
	//当cell 被点击的时候调用该方法,参数为当前的view对象与被点击cell对象
	virtual void tableCellTouched(cocos2d::extension::TableView*table,
		cocos2d::extension::TableViewCell* cell)override;
	//设置tableview的cell大小
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView * table,
		ssize_t idx)override;
	//当每一个被隐藏cell 显示出来的时候就会调用
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView* table,
		ssize_t idx)override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView* table)override;






	void destory(float) {
		if(status==destroy::DESTROY)
		this->removeFromParent();
	}
};







_UI_END
_MGE_END
#endif // !_SELECT_UI_H
