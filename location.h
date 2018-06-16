#pragma once
#ifndef _LOCATION_H
#define _LOCATION_H
#include"config.h"
_MGE_BEGIN
class location: public std::pair<int,int> {
public:
	first_type& x=first;
	second_type& y=second;
	location(const int _x, const int _y) :std::pair<int,int>(_x,_y) {};
};

_MGE_END
#endif // !LOCATION_H
