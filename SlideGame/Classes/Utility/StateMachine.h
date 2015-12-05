// ============================================================
//!		@file		StateMachine.h
//!		@brief		ステートの管理
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "cocos2d.h"
#include "StateBase.h"

enum class MACHINE_STATE : int
{
	NONE,
	BEFORE_INIT,
	UPDATE_INIT,
	AFTER_INIT,
	BEFORE_MAIN,
	UPDATE_MAIN,
	AFTER_MAIN,
	BEFORE_END,
	UPDATE_END,
	AFTER_END,
	RELEASE	
};

// ============================================================
//!		@brief		ステートマネージャ
//!		@note		シングルトン。ステートの切り替え、管理をする
//!		@attention	
//!		@warning	
// ============================================================
class StateMachine 
{
public:
	StateMachine();

private:

private:
	StateBase* mNowState;
	MACHINE_STATE mManageState;
	int mState;
	int mNextState;
	int mPrevState;

	std::map<int, StateBase*> mStateMap;

public:
	void init();
	void update(float delta);
	void release();
	void changeState(int stateValue);
	void changeStateNowStatePause(int stateValue);

	void addState(int stateType, StateBase* state);
	
	int getState();
	int getPrevState();
};

#endif // __STATE_MANAGER_H__
