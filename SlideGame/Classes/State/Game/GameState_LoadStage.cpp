// ============================================================
//!		@file		GameState_LoadStage.cpp
//!		@brief		
//!		@note		
//!		@warning	
// ============================================================
#include "GameState_LoadStage.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../../GameScene.h"
#include "../../Utility.h"
#include "../../Utility/SceneManager.h"
#include "../../Utility/StateMachineManager.h"
#include "../../Utility/StateMachineManager_define.h"


USING_NS_CC;

using namespace cocostudio::timeline;

void GameState_LoadStage::afterInit()
{
	GlobalValue::getInstance().setStartPointCheck(false);
	GlobalValue::getInstance().setGoalPointCheck(false);
	GlobalValue::getInstance().setTimeCounter(0.0f);
	GlobalValue::getInstance().setMaxTime(5.0f);
	
	GlobalValue::getInstance().SetExpValue(0);

	auto stageString = StringUtils::format("res/GameScene/Stage%d/Stage%d_%d.csb", GlobalValue::getInstance().GetStageId(), GlobalValue::getInstance().GetStageId(), GlobalValue::getInstance().GetAreaId());

	auto stageNode = CSLoader::createNode(stageString);
	GlobalValue::getInstance().setStageNode(stageNode);

	auto scene = SceneManager::getInstance().getNowScene();
	scene->addChild(stageNode, (int)GAME_LAYER::STAGE_LAYER);

	StateMachineManager::getInstance().changeState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::DISPLAY_AREA_TEXT);
}

void GameState_LoadStage::updateMain(float delta)
{
}

void GameState_LoadStage::afterEnd()
{
	
}

void GameState_LoadStage::release()
{
	
}
	
void GameState_LoadStage::onAfterInit()
{
	afterInit();
}

void GameState_LoadStage::onUpdateMain(float delta)
{
	updateMain(delta);
}

void GameState_LoadStage::onAfterEnd()
{
	afterEnd();
}

void GameState_LoadStage::onRelease()
{
	release();
}

