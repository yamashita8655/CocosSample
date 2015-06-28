#include "CharacterSelectScene.h"
#include "GameScene.h"
#include "Utility.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CharacterSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = CharacterSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("res/CharacterSelect/CharacterSelectScene.csb");

    addChild(rootNode);
    
	// 
	auto charabutton1 = dynamic_cast<ui::Button*>(rootNode->getChildByName("Button_1"));
	struct callBackFunctor1 {
        void operator() (Ref* sender) const {
			GlobalValue::getInstance().SetCharaId(1);
//			Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, GameScene::createScene()));
			Director::getInstance()->replaceScene(GameScene::createScene());
        }
    };
    
	ui::Widget::ccWidgetClickCallback callback1 = callBackFunctor1();
	charabutton1->addClickEventListener(callback1);

	// 
	auto charabutton2 = dynamic_cast<ui::Button*>(rootNode->getChildByName("Button_2"));
	struct callBackFunctor2 {
		void operator() (Ref* sender) const {
			GlobalValue::getInstance().SetCharaId(2);
//			Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, GameScene::createScene()));
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	};

	ui::Widget::ccWidgetClickCallback callback2 = callBackFunctor2();
	charabutton2->addClickEventListener(callback2);

	// 
	auto charabutton3 = dynamic_cast<ui::Button*>(rootNode->getChildByName("Button_3"));
	struct callBackFunctor3 {
		void operator() (Ref* sender) const {
			GlobalValue::getInstance().SetCharaId(3);
//			Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, GameScene::createScene()));
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	};

	ui::Widget::ccWidgetClickCallback callback3 = callBackFunctor3();
	charabutton3->addClickEventListener(callback3);

	// 
	auto charabutton4 = dynamic_cast<ui::Button*>(rootNode->getChildByName("Button_4"));
	struct callBackFunctor4 {
		void operator() (Ref* sender) const {
			GlobalValue::getInstance().SetCharaId(4);
//			Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, GameScene::createScene()));
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	};

	ui::Widget::ccWidgetClickCallback callback4 = callBackFunctor4();
	charabutton4->addClickEventListener(callback4);

    return true;
}
