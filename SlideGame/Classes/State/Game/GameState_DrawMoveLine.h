// ============================================================
//!		@file		GameState_DrawMoveLine.h
//!		@brief		オブジェクト出現演出
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __GAMESTATE_DRAW_MOVE_LINE__
#define __GAMESTATE_DRAW_MOVE_LINE__

#include "cocos2d.h"
#include "../../Utility/StateBase.h"


// ============================================================
//!		@brief		
//!		@note		
//!		@attention	
//!		@warning	
// ============================================================
class GameState_DrawMoveLine : public StateBase
{
	enum STATE{
		WAIT,
		DRAW_MOVE_LINE,
	};

private:
	bool mStartPointCheck;
	bool mGoalPointCheck;
	STATE mState;

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

	virtual ~GameState_DrawMoveLine(){};
};

#endif // __GAMESTATE_DRAW_MOVE_LINE__

