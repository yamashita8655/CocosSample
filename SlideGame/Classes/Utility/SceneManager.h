// ============================================================
//!		@file		SceneManager.h
//!		@brief		シーンの管理
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
#include "SceneManager_define.h"


// ============================================================
//!		@brief		シーンマネージャ
//!		@note		シングルトン。シーンの切り替えと、レイヤーの管理をする
//!		@attention	
//!		@warning	
// ============================================================
class SceneManager 
{
public:
	static SceneManager &getInstance();

private:
	SceneManager(){};
	SceneManager(const SceneManager &other){}
	SceneManager &operator=(const SceneManager &other){}

private:
	cocos2d::Scene*		mNowScene;
	std::map<SCENE_NAME, cocos2d::Scene*> mSceneMap;	//< シーンのマップ
	std::vector<std::stack<cocos2d::Layer*>*> mLayerStack;	//< レイヤー管理するスタック

public:
	void init();
	void runScene(SCENE_NAME name);
	void replaceScene(SCENE_NAME name);
	void pushLayer(std::string name, int zOrder = 0);
	void popLayer(std::string name);
	void popLayer();
	void popLayer(int zOrder);

	cocos2d::Scene* getNowScene();
};

#endif // __SCENE_MANAGER_H__

