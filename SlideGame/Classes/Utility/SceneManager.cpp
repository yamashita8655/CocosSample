// ============================================================
//!		@file		SceneManager.cpp
//!		@brief		シーンの管理
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../GameScene.h"
#include "../CharacterSelectScene.h"
#include "../StageSelectScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// ============================================================
//!		@brief		インスタンス取得関数
//!		@note		
//!		@return		シーンマネージャインスタンス
//!		@retval		instance
// ============================================================
SceneManager &SceneManager::getInstance() {
	static SceneManager instance;
	return instance;
}

// ============================================================
//!		@brief		初期化
//!		@note		
//!		@return		
// ============================================================
void SceneManager::init()
{
	mNowScene = nullptr;

	for(int i = 0; i < (int)ZORDER::MAX; i++)
	{
		auto stack = new std::stack<cocos2d::Layer*>();
		mLayerStack.push_back(stack);
	}
}
	
void SceneManager::runScene(SCENE_NAME name)
{
	// 仮 あとで、Sceneを継承か内包して、SCENE_NAME毎の差別化されたクラスインスタンスに変更する
    mNowScene = Scene::create();
	Director::getInstance()->runWithScene(mNowScene);
}

void SceneManager::replaceScene(SCENE_NAME name)
{
	// 仮 あとで、Sceneを継承か内包して、SCENE_NAME毎の差別化されたクラスインスタンスに変更する
	mNowScene = Scene::create();
	Director::getInstance()->replaceScene(mNowScene);
}

void SceneManager::pushLayer(std::string name, int zOrder)
{
	cocos2d::Node* ret = mNowScene->getChildByName(name);
	if (ret != nullptr)
	{
		return;
	}


	cocos2d::Layer* layer = nullptr;
	if(name == LAYER_NAME_GAME)
	{
		layer = GameScene::create();
	}
	else if (name == LAYER_NAME_STAGE_SELECT)
	{
		layer = StageSelectScene::create();
	}
	else if (name == LAYER_NAME_CHARACTER_SELECT)
	{
		layer = CharacterSelectScene::create();
	}

	mNowScene->addChild(layer, zOrder, name);

	mLayerStack.at(zOrder)->push(layer);
}

void SceneManager::popLayer(std::string name)
{
	mNowScene->removeChildByName(name);
	
	for(int i = 0; i < (int)ZORDER::MAX; i++)
	{
		auto stack = mLayerStack.at(i);
		if (stack->empty() != true)
		{
			auto layer = stack->top();
			if (layer->getName() == name)
			{
				stack->pop();
				break;
			}
		}
	}
}

void SceneManager::popLayer()
{
	cocos2d::Layer* layer = nullptr;
	for (int i = 0; i < (int)ZORDER::MAX; i++)
	{
		auto stack = mLayerStack.at(i);
		if (stack->empty() != true)
		{
			layer = stack->top();
			stack->pop();
			break;
		}
	}

	if (layer != nullptr)
	{
		mNowScene->removeChild(layer);
	}
}

void SceneManager::popLayer(int zOrder)
{
	cocos2d::Layer* layer = nullptr;
	auto stack = mLayerStack.at(zOrder);
	if (stack->empty() != true)
	{
		layer = stack->top();
		stack->pop();
	}

	if (layer != nullptr)
	{
		mNowScene->removeChild(layer);
	}
}


cocos2d::Scene* SceneManager::getNowScene()
{
	return mNowScene;
}

