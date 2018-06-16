#pragma once
#ifndef _CONFIG_H
#define _CONFIG_H
#include"cocos2d.h"
#include<iostream>

#define _MGE_BEGIN namespace mygame{
#define _MGE_END }
#define USING_NS_MGE using namespace mygame
#define _MGE mygame::
#define _TOOLS_BEGIN namespace Tools {
#define _TOOLS_END }
#define _TOOLS mygame::Tools::
#define USING_NS_TL using namespace mygame::Tools
#define _UI_BEGIN namespace UI{
#define _UI_END }
#define _UI mygame::UI::
#define USING_NS_UI using namespace mygame::UI
#define USING_NS_TXML using namespace tinyxml2

class HelloWorld;
class  AppDelegate;
_MGE_BEGIN

class startLayer;
class role;
class battleSprite;
class location;
class mapLayer;
class gameMainScene;
class battleFieldLayer;
_TOOLS_BEGIN
inline
bool not_nullptr(cocos2d::Node* node);
inline
const  std::string to_uft8(std::wstring str);
inline
void  loadBackGround(cocos2d::Node* node, const std::string& str);
inline
cocos2d::Sprite*
trimImage(const std::string& templateImage, const std::string& sourceImage);
class xmlCache;
class xmlInfo;
class xmlnode;
class storyParse;
class mapEventManager;
_TOOLS_END

_UI_BEGIN
class DialogUI;
class selectUI;
class UIoperatorLayer;
_UI_END

_MGE_END





#endif // !_CONFIG_H
