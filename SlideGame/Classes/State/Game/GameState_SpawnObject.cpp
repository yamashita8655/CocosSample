// ============================================================
//!		@file		GameState_SpawnObject.cpp
//!		@brief		
//!		@note		
//!		@warning	
// ============================================================
#include "../../GameScene.h"
#include "GameState_SpawnObject.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../../Utility/StateMachineManager.h"
#include "../../Utility.h"
#include "../../SpawnObjectManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

void GameState_SpawnObject::afterInit()
{
	auto stageNode = GlobalValue::getInstance().getStageNode();

	auto expCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("exp_value"));
	int expCount = 0;
	if (expCountText != nullptr)
	{
		expCount = std::atoi(expCountText->getString().c_str());
	}
	
	auto trapCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("trap_value"));
	int trapCount = 0;
	if (trapCountText != nullptr)
	{
		trapCount = std::atoi(trapCountText->getString().c_str());
	}

	auto redTrapCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("red_trap_value"));
	int redTrapCount = 0;
	if (redTrapCountText != nullptr)
	{
		redTrapCount = std::atoi(redTrapCountText->getString().c_str());
	}
	
	auto greenTrapCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("green_trap_value"));
	int greenTrapCount = 0;
	if (greenTrapCountText != nullptr)
	{
		greenTrapCount = std::atoi(greenTrapCountText->getString().c_str());
	}
	
	auto blueTrapCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("blue_trap_value"));
	int blueTrapCount = 0;
	if (blueTrapCountText != nullptr)
	{
		blueTrapCount = std::atoi(blueTrapCountText->getString().c_str());
	}
	
	auto redTrapBreakCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("red_trap_break_value"));
	int redTrapBreakCount = 0;
	if (redTrapBreakCountText != nullptr)
	{
		redTrapBreakCount = std::atoi(redTrapBreakCountText->getString().c_str());
	}
	
	auto greenTrapBreakCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("green_trap_break_value"));
	int greenTrapBreakCount = 0;
	if (greenTrapBreakCountText != nullptr)
	{
		greenTrapBreakCount = std::atoi(greenTrapBreakCountText->getString().c_str());
	}
	
	auto blueTrapBreakCountText = dynamic_cast<ui::Text*>(stageNode->getChildByName("blue_trap_break_value"));
	int blueTrapBreakCount = 0;
	if (blueTrapBreakCountText != nullptr)
	{
		blueTrapBreakCount = std::atoi(blueTrapBreakCountText->getString().c_str());
	}


	for (int i = 0; i < expCount; i++)
	{
		auto expName = StringUtils::format("exp_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(expName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::EXP);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}

	for (int i = 0; i < trapCount; i++)
	{
		auto trapName = StringUtils::format("trap1_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < redTrapCount; i++)
	{
		auto trapName = StringUtils::format("trap2_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_RED_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < greenTrapCount; i++)
	{
		auto trapName = StringUtils::format("trap3_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < blueTrapCount; i++)
	{
		auto trapName = StringUtils::format("trap4_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < redTrapBreakCount; i++)
	{
		auto trapName = StringUtils::format("trap5_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_RED_SPIKE_BREAK);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < greenTrapBreakCount; i++)
	{
		auto trapName = StringUtils::format("trap6_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE_BREAK);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < blueTrapBreakCount; i++)
	{
		auto trapName = StringUtils::format("trap7_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(stageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE_BREAK);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}

	cocos2d::CallFunc* func = cocos2d::CallFunc::create([](){
//		StateMachineManager::getInstance().changeState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::STARTUP);
		log("test");
	});
	func->retain();

	SpawnObjectManager::getInstance().setEndSpawnObjectCallback(func);
	SpawnObjectManager::getInstance().CreateSpawnObjectAction(0);
}
void GameState_SpawnObject::updateMain(float delta)
{
}
void GameState_SpawnObject::afterEnd()
{
	
}
void GameState_SpawnObject::release()
{
	
}
	
void GameState_SpawnObject::onAfterInit()
{
	afterInit();
}
void GameState_SpawnObject::onUpdateMain(float delta)
{
	updateMain(delta);
}
void GameState_SpawnObject::onAfterEnd()
{
	afterEnd();
}

void GameState_SpawnObject::onRelease()
{
	release();
}

