// ============================================================
//!		@file		StateMachineManager.h
//!		@brief		ステートマシンの管理
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __STATEMACHINE_MANAGER_H__
#define __STATEMACHINE_MANAGER_H__

#include "cocos2d.h"
#include "StateMachine.h"
#include "StateMachineManager_define.h"


// ============================================================
//!		@brief		ステートマシンマネージャ
//!		@note		シングルトン。ステートマシンの作成、実行、管理
//!		@attention	
//!		@warning	
// ============================================================
class StateMachineManager 
{
public:
	static StateMachineManager &getInstance();

private:
	StateMachineManager(){};
	StateMachineManager(const StateMachineManager &other){}
	StateMachineManager &operator=(const StateMachineManager &other){}

private:
	std::map<STATEMACHINE_NAME, StateMachine*> mStateMachineMap;	//< ステートマシンのマップ

public:
	void init();
	void createStateMachineMap();
	void release(STATEMACHINE_NAME machineName);
	
	void addState(STATEMACHINE_NAME machineName, int stateType, StateBase* state);
	void changeState(STATEMACHINE_NAME machineName, int stateType);
	void changeStateNowStatePause(STATEMACHINE_NAME machineName, int stateType);
	void update(STATEMACHINE_NAME machineName, float delta);
	int  getPrevState(STATEMACHINE_NAME machineName);
	int  getState(STATEMACHINE_NAME machineName);
};

#endif // __STATEMACHINE_MANAGER_H__

