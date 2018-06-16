#pragma once
#ifndef _TEMPLATE_TOOLS_H
#define _TEMPLATE_TOOLS_H
#include"config.h"
_MGE_BEGIN
_TOOLS_BEGIN
template<class T>
struct has_getTextureResource {

	using yes = char;
	using no = long;
	template <class C> static yes test(decltype(&C::getTextureResource));
	template <class C> static no test(...);
public:
	enum { value = sizeof(test<T>(nullptr)) == sizeof(yes) };
};
template<class T>
struct has_getListResource {
	using yes = char;
	using no = long;
	template <class C> static yes test(decltype(&C::getListResource));
	template <class C> static no test(...);
public:
	enum { value = sizeof(test<T>(nullptr)) == sizeof(yes) };
};


//基于SFINAE的模板编程
template<class NextScene, bool b>
struct LoadTexture {
	static  void doFunc(std::vector<std::string>& texture, float &percent, int &count, bool& com_t, float everycase, std::mutex& mtx) {
		texture.swap(std::move(NextScene::getTextureResource()));
		auto cache = cocos2d::Director::getInstance()->getTextureCache();
		float completeone = (1.0f *everycase) / texture.size();
		count = texture.size();
		for (auto &c : texture) {
			cache->addImageAsync((c + ".png"), [completeone, everycase, &count, &percent, &com_t, &mtx](Texture2D* t) {

				mtx.try_lock();
				count -= 1;
				if (count == 0) {
					com_t = true;
				}
				percent += completeone;
				mtx.unlock();

			});
		}

	}
};
template<class NextScene >
struct LoadTexture<NextScene, false> {
	static  void doFunc(std::vector<std::string>& texture, float &percent, int &count, bool& com_t, float everycase, std::mutex& mtx) {
		mtx.try_lock();
		percent += everycase;
		com_t = true;
		mtx.unlock();

	};
};
template<class NextScene, bool b>
struct LoadList {
	static  void doFunc(std::vector<std::string>& plist, float &percent, int& count, bool& com_p, float everycase, std::mutex& mtx) {
		plist.swap(std::move(NextScene::getListResource()));
		auto caches = cocos2d::SpriteFrameCache::getInstance();
		auto cachet = cocos2d::Director::getInstance()->getTextureCache();
		count = plist.size();
		float completeone = (1.0f *everycase) / plist.size();
		for (auto &c : plist) {
			cachet->addImageAsync((c + ".png"), [&c, caches, cachet, completeone, &count, &percent, &com_p, &mtx](Texture2D *t) {
				caches->addSpriteFramesWithFile((c + ".plist"), t);
				mtx.try_lock();
				count -= 1;
				percent += completeone;
				if (count == 0)
					com_p = true;
				mtx.unlock();

			});
		}
	};
};
template<class NextScene>
struct LoadList<NextScene, false> {
	static  void doFunc(std::vector<std::string>& plist, float &percent, int& count, bool& com_p, float everycase, std::mutex& mtx) {
		mtx.try_lock();
		percent += everycase;
		com_p = true;
		mtx.unlock();

	};
};
_TOOLS_END
_MGE_END


#endif // !_TEMPLATE_TOOLS_H
