// ============================================================
//!		@file		StateBase.cpp
//!		@brief		ステート基盤
//!		@note		
//!		@warning	
// ============================================================
#include "StateBase.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

StateBase::StateBase()
{
	mIsPause = false;
}

bool StateBase::isPause()
{
	return mIsPause;
}

void StateBase::pauseEnable()
{
	mIsPause = true;
}

void StateBase::pauseDisable()
{
	mIsPause = false;
}

void StateBase::_onBeforeInit()
{
	mInitCalled = true;
	onBeforeInit();
}

void StateBase::_onRelease()
{
	mInitCalled = false;
	onRelease();
}

bool StateBase::isInitCalled()
{
	return mInitCalled;
}

void StateBase::beforeInit()
{
	
}
bool StateBase::updateInit(float delta)
{
	return true;
}
void StateBase::afterInit()
{
	
}

void StateBase::beforeMain()
{
	
}
void StateBase::updateMain(float delta)
{
}
void StateBase::afterMain()
{
	
}

void StateBase::beforeEnd()
{
	
}
bool StateBase::updateEnd(float delta)
{
	return true;
}
void StateBase::afterEnd()
{
	
}
void StateBase::release()
{
	
}
	
void StateBase::onBeforeInit()
{
	beforeInit();
}
bool StateBase::onUpdateInit(float delta)
{
	return updateInit(delta);
}
void StateBase::onAfterInit()
{
	afterInit();
}

void StateBase::onBeforeMain()
{
	beforeMain();
}
void StateBase::onUpdateMain(float delta)
{
	updateMain(delta);
}
void StateBase::onAfterMain()
{
	afterMain();
}

void StateBase::onBeforeEnd()
{
	beforeEnd();
}
bool StateBase::onUpdateEnd(float delta)
{
	return updateEnd(delta);
}
void StateBase::onAfterEnd()
{
	afterEnd();
}

void StateBase::onRelease()
{
	release();
}
