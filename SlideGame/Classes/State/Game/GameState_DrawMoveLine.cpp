// ============================================================
//!		@file		GameState_DrawMoveLine.cpp
//!		@brief		
//!		@note		
//!		@warning	
// ============================================================
#include "../../GameScene.h"
#include "GameState_DrawMoveLine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../../Utility/StateMachineManager.h"
#include "../../Utility.h"
#include "../../DrawMoveLineManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

void GameState_DrawMoveLine::afterInit()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](Touch* touch, Event* event){
		GlobalValue::getInstance().setStartPointCheck(false);
		GlobalValue::getInstance().setGoalPointCheck(false);

		if (mState == STATE::WAIT)
		{
			GlobalValue::getInstance().setNowDistance(0.0f);
			mPrevPoint = touch->getLocation();
			mMovePointVector.push_back(mPrevPoint);
			mTimeConter = 0.0f;

			mState = STATE::DRAW_MOVE_LINE;
		}
		else if (mState == STATE::DRAW_MOVE_LINE)
		{
			for (int i = 1; i < this->mMovePointVector.size(); i++)
			{
				auto name = StringUtils::format("%d", i);
				this->removeChildByName(name.c_str());
			}
			this->mMovePointVector.clear();

			GlobalValue::getInstance().setNowDistance(0.0f);
			mPrevPoint = touch->getLocation();
			mMovePointVector.push_back(mPrevPoint);
		}

		log("TouchBegan");

		return true;
	};

	listener->onTouchMoved = [this](Touch* touch, Event* event){
		if (mState != STATE::DRAW_MOVE_LINE)
		{
			return;
		}

		if (GlobalValue::getInstance().getNowDistance() >= GlobalValue::getInstance().getMaxDistance())
		{
			return;
		}

		float distance = std::abs(mPrevPoint.getDistance(touch->getLocation()));

		if (distance >= 5.0f)
		{
			mNowDistance += distance;
			auto drawNode = DrawNode::create();
			drawNode->drawSegment(mPrevPoint, touch->getLocation(), 1.0f, Color4F::GREEN);
			mPrevPoint = touch->getLocation();
			mMovePointVector.push_back(mPrevPoint);
			auto name = StringUtils::format("%d", mMovePointVector.size()-1);
			this->addChild(drawNode, (int)GAME_LAYER::LINE_LAYER, name.c_str());
		}

	};

	listener->onTouchEnded = [this](Touch* touch, Event* event){
		log("TouchEnded");
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameState_DrawMoveLine::updateMain(float delta)
{
	//mTimeConter += delta;
	//auto text = StringUtils::format("%f", mMaxTime - mTimeConter);
	//mCountDownTimeText->setString(text);

	//if ((mMaxTime - mTimeConter) < 0.0f)
	//{
	//	mGameState = GAME_STATE::DELETE_CLOUD_INIT;
	//}
}
void GameState_DrawMoveLine::afterEnd()
{
	
}
void GameState_DrawMoveLine::release()
{
	
}
	
void GameState_DrawMoveLine::onAfterInit()
{
	afterInit();
}
void GameState_DrawMoveLine::onUpdateMain(float delta)
{
	updateMain(delta);
}
void GameState_DrawMoveLine::onAfterEnd()
{
	afterEnd();
}

void GameState_DrawMoveLine::onRelease()
{
	release();
}

