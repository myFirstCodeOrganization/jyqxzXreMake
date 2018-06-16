#pragma once
#ifndef UI_INFO
#define UI_INFO
#include"tools.h"
#include<array>
#include"Any.h"
_MGE_BEGIN
_UI_BEGIN
/*
struct UICreateInfo {
	virtual Any getParams()=0;
	virtual ~UICreateInfo() {};
};
template<size_t paramNumber>
struct UIInfo:public UICreateInfo {
private:
	std::array<Any, paramNumber> params;
public:
	virtual Any getParams() override{ return Any(&params); }
	


};
using UIInfo_one = UIInfo<1u>;
using UIInfo_two =UIInfo<2u>;
using UIInfo_three = UIInfo<3u>;
using UIInfo_four = UIInfo<4u> ;
using UIInfo_five = UIInfo<5u> ;



using array_one = std::array<Any, 1>;
using array_two = std::array<Any, 2>;
using array_three = std::array<Any, 3>;
using array_four = std::array<Any, 4>;
using array_five = std::array<Any, 5>;
*/
_UI_END
_MGE_END
#endif // !UI_INFO
