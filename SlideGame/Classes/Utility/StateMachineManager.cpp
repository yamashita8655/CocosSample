// ============================================================
//!		@file		StateMachineManager.cpp
//!		@brief		ステートマシンの管理
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#include "StateMachineManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StateBase.h"
#include "StateMachine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// ============================================================
//!		@brief		インスタンス取得関数
//!		@note		
//!		@return		シーンマネージャインスタンス
//!		@retval		instance
// ============================================================
StateMachineManager &StateMachineManager::getInstance() {
	static StateMachineManager instance;
	return instance;
}

// ============================================================
//!		@brief		初期化
//!		@note		
//!		@return		
// ============================================================
void StateMachineManager::init()
{
}
	
// ============================================================
//!		@brief		ステートマシン作成
//!		@note		
//!		@return		
// ============================================================
void StateMachineManager::createStateMachineMap()
{
	mStateMachineMap.insert(std::make_pair(STATEMACHINE_NAME::GAME,	new StateMachine()));
}
	
// ============================================================
//!		@brief		ステートマシン解放
//!		@note		
//!		@return		
// ============================================================
void StateMachineManager::release(STATEMACHINE_NAME machineName)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;
	
	machine->release();
}
	
void StateMachineManager::addState(STATEMACHINE_NAME machineName, int stateType, StateBase* state)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;
	
	machine->addState(stateType, state);
}

void StateMachineManager::changeState(STATEMACHINE_NAME machineName, int stateType)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;
	
	machine->changeState(stateType);
}

void StateMachineManager::changeStateNowStatePause(STATEMACHINE_NAME machineName, int stateType)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;

	machine->changeStateNowStatePause(stateType);
}

void StateMachineManager::update(STATEMACHINE_NAME machineName, float delta)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;
	
	machine->update(delta);
}

int StateMachineManager::getPrevState(STATEMACHINE_NAME machineName)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;

	return machine->getPrevState();
}

int StateMachineManager::getState(STATEMACHINE_NAME machineName)
{
	auto it = mStateMachineMap.find(machineName);
	auto machine = it->second;

	return machine->getState();
}


