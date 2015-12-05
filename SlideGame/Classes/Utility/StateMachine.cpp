// ============================================================
//!		@file		StateMachine.cpp
//!		@brief		ステート管理
//!		@note		
//!		@warning	
// ============================================================
#include "StateMachine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

StateMachine::StateMachine()
{
	init();
}

// ============================================================
//!		@brief		初期化
//!		@note		
//!		@return		
// ============================================================
void StateMachine::init()
{
	mNowState       = nullptr;
	mManageState	= MACHINE_STATE::NONE;
	mState			= 0;
	mNextState 		= 0;
	mPrevState 		= 0;
}

// ============================================================
//!		@brief		更新
//!		@note		
//!		@param[in]	delta	
//!		@return		
// ============================================================
void StateMachine::update(float delta)
{
	if(mNowState == nullptr)
	{
		return;
	}

	switch(mManageState)
	{
	case MACHINE_STATE::BEFORE_INIT:
		if (mNowState->isPause() == true)
		{
			// ポーズ状態だったら、即メインのアップデート処理状態にする
			mManageState = MACHINE_STATE::UPDATE_MAIN;
			mNowState->pauseDisable();
		}
		else
		{
			mManageState = MACHINE_STATE::UPDATE_INIT;
			mNowState->_onBeforeInit();
		}
		break;
	
	case MACHINE_STATE::UPDATE_INIT:
		{
			bool isEnd = mNowState->onUpdateInit(delta);
			if(isEnd == true)
			{
				mManageState = MACHINE_STATE::AFTER_INIT;
			}
		}
		break;
	
	case MACHINE_STATE::AFTER_INIT:
		mManageState = MACHINE_STATE::BEFORE_MAIN;
		mNowState->onAfterInit();
		break;
	
	case MACHINE_STATE::BEFORE_MAIN:
		mManageState = MACHINE_STATE::UPDATE_MAIN;
		mNowState->onBeforeMain();
		break;
	
	case MACHINE_STATE::UPDATE_MAIN:
		mNowState->onUpdateMain(delta);
		break;
	
	case MACHINE_STATE::AFTER_MAIN:
		mManageState = MACHINE_STATE::BEFORE_END;
		mNowState->onAfterMain();
		break;
	
	case MACHINE_STATE::BEFORE_END:
		mManageState = MACHINE_STATE::UPDATE_END;
		mNowState->onBeforeEnd();
		break;
	
	case MACHINE_STATE::UPDATE_END:
		{
			bool isEnd = mNowState->onUpdateEnd(delta);
			if(isEnd == true)
			{
				mManageState = MACHINE_STATE::AFTER_END;
			}
		}
		break;
	
	case MACHINE_STATE::AFTER_END:
		mManageState = MACHINE_STATE::RELEASE;
		mNowState->onAfterEnd();
		break;
	
	case MACHINE_STATE::RELEASE:
		{
			mManageState = MACHINE_STATE::BEFORE_INIT;
			if (mNowState->isPause() != true)
			{
				mNowState->_onRelease();
			}
			mPrevState = mState;
			mState = mNextState;
			auto it = mStateMap.find(mState);
			mNowState = it->second;
			break;
		}
	}
}

void StateMachine::changeState(int stateType)
{
	if (mManageState != MACHINE_STATE::AFTER_INIT &&
		mManageState != MACHINE_STATE::UPDATE_MAIN		)
	{
		log("StateMachine::changeState");
		log("%d state isnt use changeState", (int)mManageState);
		CCASSERT(true, "changeState assert");
	}

	if(mNowState != nullptr)
	{
		mNextState = stateType;
		mManageState = MACHINE_STATE::AFTER_MAIN;
	}
	else
	{
		auto it = mStateMap.find(stateType);
		mNowState = it->second;
		mManageState = MACHINE_STATE::BEFORE_INIT;
	}
}

// ============================================================
//!		@brief		今のステート状態を保持(onEndと次に有効になった時のonInitを呼び出さないようにする)して、ステート変更
//!		@note		
//!		@param[in]	stateType	変更後のステート
//!		@return		
// ============================================================
void StateMachine::changeStateNowStatePause(int stateType)
{
	if (mManageState != MACHINE_STATE::AFTER_INIT &&
		mManageState != MACHINE_STATE::UPDATE_MAIN)
	{
		log("StateMachine::changeState");
		log("%d state isnt use changeState", (int)mManageState);
		CCASSERT(true, "changeState assert");
	}

	if(mNowState != nullptr)
	{
		mNowState->pauseEnable();
		mNextState = stateType;
		mManageState = MACHINE_STATE::RELEASE;// 即リリース状態にしているが、PAUSEをかけているので、リリースの処理は呼び出されない
	}
	else
	{
		auto it = mStateMap.find(stateType);
		mNowState = it->second;
		mManageState = MACHINE_STATE::BEFORE_INIT;
	}
}
	
// ============================================================
//!		@brief		ステート追加
//!		@note		ステート管理にステートを追加する
//!		@param[in]	stateValue	ステートタイプ
//!		@param[in]	state		変更後のステート
//!		@return		
// ============================================================
void StateMachine::addState(int stateType, StateBase* state)
{
	auto findIt = mStateMap.find(stateType);
	if(findIt != mStateMap.end())
	{
		return;
	}

	mStateMap.insert(std::make_pair(stateType, state));
}

// ============================================================
//!		@brief		今のステート取得
//!		@note		
//!		@return		int
// ============================================================
int StateMachine::getState()
{
	return mState;
}

// ============================================================
//!		@brief		前のステート取得
//!		@note		
//!		@return		int
// ============================================================
int StateMachine::getPrevState()
{
	return mPrevState;
}

void StateMachine::release()
{
	auto it = mStateMap.begin();

	for(it; it != mStateMap.end(); it++)
	{
		if(it->second->isInitCalled() == true)
		{
			it->second->_onRelease();
		}
		delete it->second;
	}

	mStateMap.clear();
	mNowState = nullptr;
}


