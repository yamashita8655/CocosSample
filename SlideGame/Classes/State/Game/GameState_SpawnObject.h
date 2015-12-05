// ============================================================
//!		@file		GameState_SpawnObject.h
//!		@brief		オブジェクト出現演出
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __GAMESTATE_SPAWNOBJECT__
#define __GAMESTATE_SPAWNOBJECT__

#include "cocos2d.h"
#include "../../Utility/StateBase.h"


// ============================================================
//!		@brief		
//!		@note		
//!		@attention	
//!		@warning	
// ============================================================
class GameState_SpawnObject : public StateBase
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

	virtual ~GameState_SpawnObject(){};
};

#endif // __GAMESTATE_SPAWNOBJECT__

