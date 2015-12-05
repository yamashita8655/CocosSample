#ifndef __CHARACTER_SCENE_H__
#define __CHARACTER_SCENE_H__

#include "cocos2d.h"
#include <ui/CocosGUI.h>

class CharacterSelectScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onExit();

    // implement the "static create()" method manually
	CREATE_FUNC(CharacterSelectScene);

	void pageviewCallBack(cocos2d::Ref* psender, cocos2d::ui::PageViewEventType type);

	cocos2d::ui::PageView* mPageView;
};

#endif // __CHARACTER_SCENE_H__
