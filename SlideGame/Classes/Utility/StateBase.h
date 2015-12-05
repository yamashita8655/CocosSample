// ============================================================
//!		@file		StateBase.h
//!		@brief		ステートマシン用のベースクラス
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __STATE_BASE_H__
#define __STATE_BASE_H__

#include "cocos2d.h"


// ============================================================
//!		@brief		ステートベースクラス
//!		@note		
//!		@attention	
//!		@warning	
// ============================================================
class StateBase
{
private:
	bool mIsPause;// 今のステートが、次のChangeStateで有効になるまで動作させなくする。次の有効で、自動的にfalseにする
	bool mInitCalled;// 

protected:
	StateBase();
#if 1
	virtual void beforeInit();
	virtual bool updateInit(float delta);
	virtual void afterInit();

	virtual void beforeMain();
	virtual void updateMain(float delta);
	virtual void afterMain();
	
	virtual void beforeEnd();
	virtual bool updateEnd(float delta);
	virtual void afterEnd();
	
	virtual void release();
#endif

public:
	virtual void onBeforeInit();
	virtual bool onUpdateInit(float delta);
	virtual void onAfterInit();

	virtual void onBeforeMain();
	virtual void onUpdateMain(float delta);
	virtual void onAfterMain();
	
	virtual void onBeforeEnd();
	virtual bool onUpdateEnd(float delta);
	virtual void onAfterEnd();
	
	virtual void onRelease();

	void pauseEnable();
	void pauseDisable();
	bool isPause();
	bool isInitCalled();
	void _onBeforeInit();
	void _onRelease();

	virtual ~StateBase(){};
};

#endif // __STATE_BASE_H__

