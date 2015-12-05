#include "StageSelectScene.h"
#include "CharacterSelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "Utility.h"
#include "ui/CocosGUI.h"
#include "Utility/SceneManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* StageSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = StageSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("res/StageSelect/StageSelectScene.csb");

    addChild(rootNode);

	auto buttonValue = dynamic_cast<ui::Text*>(rootNode->getChildByName("maxButtonValue"));
	int maxButtonValue = std::atoi(buttonValue->getString().c_str());

	struct callBackFunctor {
		void operator() (Ref* sender) const {
			ui::Button* btn = (ui::Button*)sender;
			auto stageNumber = dynamic_cast<ui::Text*>(btn->getChildByName("stageNo"));
			int num = std::atoi(stageNumber->getString().c_str());

			GlobalValue::getInstance().SetStageId(num);
			//Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, CharacterSelectScene::createScene()));
			SceneManager::getInstance().replaceScene(SCENE_NAME::CHARACTER_SELECT);
			SceneManager::getInstance().pushLayer(LAYER_NAME_CHARACTER_SELECT);
		}
	};

	for (int i = 0; i < maxButtonValue; i++)
	{
		auto key = StringUtils::format("stage_button_1_%d", i+1);
		auto button = dynamic_cast<ui::Button*>(rootNode->getChildByName(key));

		ui::Widget::ccWidgetClickCallback callback = callBackFunctor();
		button->addClickEventListener(callback);
	}

    return true;
}
