// ============================================================
//!		@file		GameState_DisplayAreaText.cpp
//!		@brief		
//!		@note		
//!		@warning	
// ============================================================
#include "../../GameScene.h"
#include "GameState_DisplayAreaText.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../../Utility.h"
#include "../../Utility/StateMachineManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

void GameState_DisplayAreaText::afterInit()
{
	auto spriteName = StringUtils::format("area%dsprite", GlobalValue::getInstance().GetAreaId());
	auto rootNode = GlobalValue::getInstance().getRootNode();
	auto areaSprite = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName(spriteName));
	areaSprite->setOpacity(0);
	areaSprite->setVisible(true);

	auto endAction = CallFuncN::create([this](Ref* obj){
		StateMachineManager::getInstance().changeState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::SPAWN_OBJECT);
	});

	auto startSpawnAction = Sequence::create(
		FadeIn::create(1.0f),
		FadeTo::create(1.0f, 255),
		FadeOut::create(1.0f),
		endAction,
		nullptr
	);

	areaSprite->runAction(startSpawnAction);
}
void GameState_DisplayAreaText::updateMain(float delta)
{
}
void GameState_DisplayAreaText::afterEnd()
{
	
}
void GameState_DisplayAreaText::release()
{
	
}
	
void GameState_DisplayAreaText::onAfterInit()
{
	afterInit();
}
void GameState_DisplayAreaText::onUpdateMain(float delta)
{
	updateMain(delta);
}
void GameState_DisplayAreaText::onAfterEnd()
{
	afterEnd();
}

void GameState_DisplayAreaText::onRelease()
{
	release();
}
