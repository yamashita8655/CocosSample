// ============================================================
//!		@file		GameState_StartUp.cpp
//!		@brief		
//!		@note		
//!		@warning	
// ============================================================
#include "../../GameScene.h"
#include "GameState_StartUp.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../../Utility/StateMachineManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

void GameState_StartUp::afterInit()
{
	StateMachineManager::getInstance().changeState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::LOAD_STAGE);
}
void GameState_StartUp::updateMain(float delta)
{
}
void GameState_StartUp::afterEnd()
{
	
}
void GameState_StartUp::release()
{
	
}
	
void GameState_StartUp::onAfterInit()
{
	afterInit();
}
void GameState_StartUp::onUpdateMain(float delta)
{
	updateMain(delta);
}
void GameState_StartUp::onAfterEnd()
{
	afterEnd();
}

void GameState_StartUp::onRelease()
{
	release();
}
