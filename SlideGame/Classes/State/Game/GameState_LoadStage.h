// ============================================================
//!		@file		GameState_LoadStage.h
//!		@brief		ゲーム開始時の処理
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __GAMESTATE_LOADSTAGE_H__
#define __GAMESTATE_LOADSTAGE_H__

#include "cocos2d.h"
#include "../../Utility/StateBase.h"


// ============================================================
//!		@brief		
//!		@note		
//!		@attention	
//!		@warning	
// ============================================================
class GameState_LoadStage : public StateBase
{
private:

protected:	
	virtual void afterInit();
	virtual void updateMain(float delta);
	virtual void afterEnd();
	
	virtual void release();

public:
	virtual void onAfterInit();
	virtual void onUpdateMain(float delta);
	virtual void onAfterEnd();
	
	virtual void onRelease();

	virtual ~GameState_LoadStage(){};
};

#endif // __GAMESTATE_STARTUP_H__

