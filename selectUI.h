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
/*	//������tableview��ʱ�򴥷��ķ���,����Ϊ�������� tableview
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override ;
	//��tableview �����ŵ�ʱ�򴥷��÷���,����Ϊ��ǰtableview
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
	*/
	//��cell �������ʱ����ø÷���,����Ϊ��ǰ��view�����뱻���cell����
	virtual void tableCellTouched(cocos2d::extension::TableView*table,
		cocos2d::extension::TableViewCell* cell)override;
	//����tableview��cell��С
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView * table,
		ssize_t idx)override;
	//��ÿһ��������cell ��ʾ������ʱ��ͻ����
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
