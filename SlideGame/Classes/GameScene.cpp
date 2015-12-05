#include "GameScene.h"
#include "Utility.h"
#include "SpawnObjectManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StageSelectScene.h"

#include "Utility/StateBase.h"
#include "Utility/StateMachine.h"
#include "Utility/StateMachineManager.h"
#include "Utility/StateMachineManager_define.h"
#include "Utility/SceneManager.h"

#include "State/Game/GameState_StartUp.h"
#include "State/Game/GameState_LoadStage.h"
#include "State/Game/GameState_DisplayAreaText.h"
#include "State/Game/GameState_SpawnObject.h"

USING_NS_CC;

using namespace cocostudio::timeline;

GAME_STATE GameScene::mGameState;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	GlobalValue::getInstance().SetCharaLife(5);
	GlobalValue::getInstance().SetExpValue(0);
	GlobalValue::getInstance().SetAreaId(1);


	scheduleUpdate();
	mGameState = GAME_STATE::LOAD_STAGE_INIT;
	GlobalValue::getInstance().setNowDistance(0.0f);
	GlobalValue::getInstance().setMaxDistance(3000.0f);
	mNowDistance = 0.0f;
	mMaxDistance = 3000.0f;

	//auto stageString = StringUtils::format("res/GameScene/Stage%d/Stage%dParameter.csb", GlobalValue::getInstance().GetStageId(), GlobalValue::getInstance().GetStageId());
	//auto stageParameter = CSLoader::createNode(stageString);
	//auto stageValue = dynamic_cast<ui::Text*>(stageParameter->getChildByName("StageValue"));
	//GlobalValue::getInstance().SetStageValue(std::atoi(stageValue->getString().c_str()));

	mRootNode = CSLoader::createNode("res/GameScene/GameScene.csb");
	GlobalValue::getInstance().setRootNode(mRootNode);
	auto nowScene = SceneManager::getInstance().getNowScene();
	nowScene->addChild(mRootNode, (int)GAME_LAYER::STAGE_FRONT_LAYER);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

/*	auto spriteName = StringUtils::format("GameScene/movecharacter%d.png", GlobalValue::getInstance().GetCharaId());
	mCharaSprite = Sprite::create(spriteName.c_str());
	mCharaSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mCharaSprite, (int)GAME_LAYER::MOVE_CHARA_LAYER);

	for (int i = 0; i < (int)GAME_CONST::MAX_LIFE; i++)
	{
		auto buttonName = StringUtils::format("life_%d", i + 1);
		auto button = dynamic_cast<ui::Button*>(mRootNode->getChildByName(buttonName));
		mCharacterLifeButton.push_back(button);
	}*/

/*	for (int i = 0; i < 20; i++)
	{
		int x = RandomCreator::getInstance().GetRandomMinToMax(-380, 380);
		int y = RandomCreator::getInstance().GetRandomMinToMax(-120, 220);

		SpawnObjectManager::getInstance().CreateSpawnObject(this, x, y);
	}*/


//	void (GameScene::*fpFunc)() = &GameScene::Endfunction;
//	(this->*fpFunc)();



/*	auto button1 = dynamic_cast<ui::Button*>(rootNode->getChildByName("stage_button_1_1"));
    
	struct callBackFunctor {
        void operator() (Ref* sender) const {
			Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, CharacterSelectScene::createScene()));
        }
    };
    
	ui::Widget::ccWidgetClickCallback callback = callBackFunctor();
    button1->addClickEventListener(callback);*/
#if 0
	mCountDownTimeText = dynamic_cast<ui::Text*>(mRootNode->getChildByName("Text_countdown"));

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](Touch* touch, Event* event){
		mStartPointCheck = false;
		mGoalPointCheck = false;

		if (this->mGameState == GAME_STATE::WAIT)
		{
			mNowDistance = 0.0f;
			mPrevPoint = touch->getLocation();
			mMovePointVector.push_back(mPrevPoint);
			mTimeConter = 0.0f;

			mGameState = GAME_STATE::DRAW_MOVE_LINE;
		}
		else if (this->mGameState == GAME_STATE::DRAW_MOVE_LINE)
		{
			for (int i = 1; i < this->mMovePointVector.size(); i++)
			{
				auto name = StringUtils::format("%d", i);
				this->removeChildByName(name.c_str());
			}
			this->mMovePointVector.clear();

			mNowDistance = 0.0f;
			mPrevPoint = touch->getLocation();
			mMovePointVector.push_back(mPrevPoint);
		}

		log("TouchBegan");

		return true;
	};

	listener->onTouchMoved = [this](Touch* touch, Event* event){
		if (this->mGameState != GAME_STATE::DRAW_MOVE_LINE)
		{
			return;
		}

		if (mNowDistance >= mMaxDistance)
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
#endif
	StateMachineManager::getInstance().init();
	
	StateMachineManager::getInstance().addState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::STARTUP,				new GameState_StartUp());
	StateMachineManager::getInstance().addState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::LOAD_STAGE,			new GameState_LoadStage());
	StateMachineManager::getInstance().addState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::DISPLAY_AREA_TEXT,	new GameState_DisplayAreaText());
	StateMachineManager::getInstance().addState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::SPAWN_OBJECT,		new GameState_SpawnObject());

	StateMachineManager::getInstance().changeState(STATEMACHINE_NAME::GAME, (int)GAME_STATE2::STARTUP);

    return true;
}

void GameScene::update(float delta)
{
	StateMachineManager::getInstance().update(STATEMACHINE_NAME::GAME, delta);
#if 0
	if (mGameState == GAME_STATE::LOAD_STAGE_INIT)
	{
		LoadStageInit();
	}
	else if (mGameState == GAME_STATE::LOAD_STAGE_UPDATE)
	{
		LoadStageUpdate(delta);
	}
	else if (mGameState == GAME_STATE::LOAD_STAGE_END)
	{
		LoadStageEnd();
	}
	else if (mGameState == GAME_STATE::AREA_EFFECT_INIT)
	{
		AreaEffectInit();
	}
	else if (mGameState == GAME_STATE::AREA_EFFECT_UPDATE)
	{
		AreaEffectUpdate(delta);
	}
	else if (mGameState == GAME_STATE::AREA_EFFECT_END)
	{
		AreaEffectEnd();
	}
	else if (mGameState == GAME_STATE::SPAWN_OBJECT_INIT)
	{
		SpawnObjectInit();
	}else if (mGameState == GAME_STATE::SPAWN_OBJECT_UPDATE)
	{
		SpawnObjectUpdate(delta);
	}else if (mGameState == GAME_STATE::SPAWN_OBJECT_END)
	{
		SpawnObjectEnd();
	}else if (mGameState == GAME_STATE::SPAWN_START_GOAL_INIT)
	{
		SpawnStartGoalInit();
	}else if (mGameState == GAME_STATE::SPAWN_START_GOAL_UPDATE)
	{
		SpawnStartGoalUpdate(delta);
	}else if (mGameState == GAME_STATE::SPAWN_START_GOAL_END)
	{
		SpawnStartGoalEnd();
	}
	else if (mGameState == GAME_STATE::SPAWN_CLOUD_INIT)
	{
		SpawnCloudInit();
	}
	else if (mGameState == GAME_STATE::SPAWN_CLOUD_UPDATE)
	{
		SpawnCloudUpdate(delta);
	}
	else if (mGameState == GAME_STATE::SPAWN_CLOUD_END)
	{
		SpawnCloudEnd();
	}
	else if (mGameState == GAME_STATE::DRAW_MOVE_LINE)
	{
		mTimeConter += delta;
		auto text = StringUtils::format("%f", mMaxTime - mTimeConter);
		mCountDownTimeText->setString(text);

		if ((mMaxTime - mTimeConter) < 0.0f)
		{
			mGameState = GAME_STATE::DELETE_CLOUD_INIT;
		}
	}
	else if (mGameState == GAME_STATE::DELETE_CLOUD_INIT)
	{
		DeleteCloudInit();
	}
	else if (mGameState == GAME_STATE::DELETE_CLOUD_UPDATE)
	{
		DeleteCloudUpdate(delta);
	}
	else if (mGameState == GAME_STATE::DELETE_CLOUD_END)
	{
		DeleteCloudEnd();
	}
	else if (mGameState == GAME_STATE::MOVE_CHARACTER_INIT)
	{
		MoveCharacterInit();
	}
	else if (mGameState == GAME_STATE::MOVE_CHARACTER_UPDATE)
	{
		MoveCharacterUpdate(delta);
	}
	else if (mGameState == GAME_STATE::MOVE_CHARACTER_END)
	{
		MoveCharacterEnd();
	}
	else if (mGameState == GAME_STATE::FAILED_INFORMATION_INIT)
	{
		FailedInformationInit();
	}
	else if (mGameState == GAME_STATE::FAILED_INFORMATION_UPDATE)
	{
		FailedInformationUpdate(delta);
	}
	else if (mGameState == GAME_STATE::FAILED_INFORMATION_END)
	{
		FailedInformationEnd();
	}
	else if (mGameState == GAME_STATE::CLEAR_INFORMATION_INIT)
	{
		ClearInformationInit();
	}
	else if (mGameState == GAME_STATE::CLEAR_INFORMATION_UPDATE)
	{
		ClearInformationUpdate(delta);
	}
	else if (mGameState == GAME_STATE::CLEAR_INFORMATION_END)
	{
		ClearInformationEnd();
	}
#endif
}

void GameScene::UpdateLifePointButton()
{
	for (int i = 0; i < (int)GAME_CONST::MAX_LIFE; i++)
	{
		mCharacterLifeButton.at(i)->setBright(false);
	}

	int life = GlobalValue::getInstance().GetCharaLife();

	for (int i = 0; i < life; i++)
	{
		mCharacterLifeButton.at(i)->setBright(true);
	}
}

void GameScene::CreateStartGoalAction()
{

}


void GameScene::Endfunction()
{
	if (mGameState == GAME_STATE::SPAWN_OBJECT_UPDATE)
	{
		mGameState = GAME_STATE::SPAWN_OBJECT_END;
	}
	else if (mGameState == GAME_STATE::SPAWN_START_GOAL_UPDATE)
	{
		mGameState = GAME_STATE::SPAWN_START_GOAL_END;
	}
	else if (mGameState == GAME_STATE::DELETE_CLOUD_UPDATE)
	{
		mGameState = GAME_STATE::DELETE_CLOUD_END;
	}
	else if (mGameState == GAME_STATE::AREA_EFFECT_UPDATE)
	{
		mGameState = GAME_STATE::AREA_EFFECT_END;
	}

}

void GameScene::AreaEffectInit()
{
	auto spriteName = StringUtils::format("area%dsprite", GlobalValue::getInstance().GetAreaId());
	auto areaSprite = dynamic_cast<cocos2d::Sprite*>(mRootNode->getChildByName(spriteName));
	areaSprite->setOpacity(0);
	areaSprite->setVisible(true);

	auto endAction = CallFuncN::create([this](Ref* obj){
		GameScene::Endfunction();
	});

	auto startSpawnAction = Sequence::create(
		FadeIn::create(1.0f),
		FadeTo::create(1.0f, 256),
		FadeOut::create(1.0f),
		endAction,
		nullptr
	);

	areaSprite->runAction(startSpawnAction);

	mGameState = GAME_STATE::AREA_EFFECT_UPDATE;
}
void GameScene::AreaEffectUpdate(float delta)
{

}
void GameScene::AreaEffectEnd()
{
	mGameState = GAME_STATE::SPAWN_OBJECT_INIT;
}

void GameScene::SpawnObjectInit()
{
	auto expCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("exp_value"));
	int expCount = 0;
	if (expCountText != nullptr)
	{
		expCount = std::atoi(expCountText->getString().c_str());
	}
	
	auto trapCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("trap_value"));
	int trapCount = 0;
	if (trapCountText != nullptr)
	{
		trapCount = std::atoi(trapCountText->getString().c_str());
	}

	auto redTrapCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("red_trap_value"));
	int redTrapCount = 0;
	if (redTrapCountText != nullptr)
	{
		redTrapCount = std::atoi(redTrapCountText->getString().c_str());
	}
	
	auto greenTrapCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("green_trap_value"));
	int greenTrapCount = 0;
	if (greenTrapCountText != nullptr)
	{
		greenTrapCount = std::atoi(greenTrapCountText->getString().c_str());
	}
	
	auto blueTrapCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("blue_trap_value"));
	int blueTrapCount = 0;
	if (blueTrapCountText != nullptr)
	{
		blueTrapCount = std::atoi(blueTrapCountText->getString().c_str());
	}
	
	auto redTrapBreakCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("red_trap_break_value"));
	int redTrapBreakCount = 0;
	if (redTrapBreakCountText != nullptr)
	{
		redTrapBreakCount = std::atoi(redTrapBreakCountText->getString().c_str());
	}
	
	auto greenTrapBreakCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("green_trap_break_value"));
	int greenTrapBreakCount = 0;
	if (greenTrapBreakCountText != nullptr)
	{
		greenTrapBreakCount = std::atoi(greenTrapBreakCountText->getString().c_str());
	}
	
	auto blueTrapBreakCountText = dynamic_cast<ui::Text*>(mStageNode->getChildByName("blue_trap_break_value"));
	int blueTrapBreakCount = 0;
	if (blueTrapBreakCountText != nullptr)
	{
		blueTrapBreakCount = std::atoi(blueTrapBreakCountText->getString().c_str());
	}


	for (int i = 0; i < expCount; i++)
	{
		auto expName = StringUtils::format("exp_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(expName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::EXP);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}

	for (int i = 0; i < trapCount; i++)
	{
		auto trapName = StringUtils::format("trap1_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < redTrapCount; i++)
	{
		auto trapName = StringUtils::format("trap2_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_RED_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < greenTrapCount; i++)
	{
		auto trapName = StringUtils::format("trap3_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < blueTrapCount; i++)
	{
		auto trapName = StringUtils::format("trap4_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < redTrapBreakCount; i++)
	{
		auto trapName = StringUtils::format("trap5_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_RED_SPIKE_BREAK);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < greenTrapBreakCount; i++)
	{
		auto trapName = StringUtils::format("trap6_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE_BREAK);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}
	
	for (int i = 0; i < blueTrapBreakCount; i++)
	{
		auto trapName = StringUtils::format("trap7_%d", i);
		auto sprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName(trapName));

		SpawnObject* obj = new SpawnObject();
		sprite->setVisible(false);
		obj->SetSprite(sprite);
		obj->SetType(SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE_BREAK);
		SpawnObjectManager::getInstance().AddSpawnObject(obj);
	}

	SpawnObjectManager::getInstance().CreateSpawnObjectAction(0);

	mGameState = GAME_STATE::SPAWN_OBJECT_UPDATE;
}
void GameScene::SpawnObjectUpdate(float delta)
{

}
void GameScene::SpawnObjectEnd()
{
	mGameState = GAME_STATE::SPAWN_START_GOAL_INIT;
}


void GameScene::SpawnStartGoalInit()
{
	mStartSprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName("startpoint"));
	mStartSprite->setVisible(true);
	mStartSprite->setScale(0.1f, 0.1f);

	Vector<FiniteTimeAction*> startactions;

	auto startSpawnAction = Spawn::create(
		ScaleTo::create(0.1f, 1.0f),
		JumpTo::create(0.5f, mStartSprite->getPosition(), 30.0f, 1),
		nullptr
	);
	startactions.pushBack(startSpawnAction);

	auto startSequenceVec = Sequence::create(startactions);
	mStartSprite->runAction(startSequenceVec);

	mGoalSprite = dynamic_cast<cocos2d::Sprite*>(mStageNode->getChildByName("goalpoint"));
	mGoalSprite->setVisible(true);
	mGoalSprite->setScale(0.1f, 0.1f);

	Vector<FiniteTimeAction*> goalactions;

	auto endAction = CallFuncN::create([this](Ref* obj){
		GameScene::Endfunction();
	});

	auto goalSpawnAction = Spawn::create(
		ScaleTo::create(0.1f, 1.0f),
		JumpTo::create(0.5f, mGoalSprite->getPosition(), 30.0f, 1),
		nullptr
	);
	goalactions.pushBack(goalSpawnAction);
	goalactions.pushBack(endAction);

	auto goalSequenceVec = Sequence::create(goalactions);
	mGoalSprite->runAction(goalSequenceVec);

	mGameState = GAME_STATE::SPAWN_START_GOAL_UPDATE;
}
void GameScene::SpawnStartGoalUpdate(float delta)
{

}
void GameScene::SpawnStartGoalEnd()
{
	mGameState = GAME_STATE::SPAWN_CLOUD_INIT;
}

void GameScene::SpawnCloudInit()
{
	for (int i = 0; i < 40; i++)
	{
		int x = RandomCreator::getInstance().GetRandomMinToMax(-480, 480);
		int y = RandomCreator::getInstance().GetRandomMinToMax(-120, 220);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto spriteName = StringUtils::format("GameScene/cloud.png");
		auto sprite = Sprite::create(spriteName.c_str());
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x + x, visibleSize.height / 2 + origin.y + y));
		this->addChild(sprite, (int)GAME_LAYER::CLOUD_LAYER);

		auto startSpawnAction = Sequence::create(
			ScaleTo::create(1.0f, 0.9f, 1.1f),
			ScaleTo::create(1.0f, 1.1f, 0.9f),
			nullptr
		);

		auto repeatAction = RepeatForever::create(startSpawnAction);
		sprite->runAction(repeatAction);

		mCloudVector.push_back(sprite);
	}

	mGameState = GAME_STATE::SPAWN_CLOUD_END;
}
void GameScene::SpawnCloudUpdate(float delta)
{

}
void GameScene::SpawnCloudEnd()
{
	mGameState = GAME_STATE::WAIT;
}

void GameScene::DeleteCloudInit()
{
	for (int i = 0; i < mCloudVector.size(); i++)
	{
		auto startDeleteAction = Spawn::create(
			FadeOut::create(1.0f),
			ScaleTo::create(1.0f, 0.1f, 10.0f),
			nullptr
		);

		if (i == (mCloudVector.size() - 1))
		{
			auto endFunc = CallFuncN::create([this](Ref* obj){
				for (int i = 0; i < this->mCloudVector.size(); i++)
				{
					this->removeChild(this->mCloudVector.at(i));
				}
				this->mCloudVector.clear();
				GameScene::Endfunction();
			});

			auto lastDeleteAction = Sequence::create(
				startDeleteAction,
				endFunc,
				nullptr
			);
			mCloudVector.at(i)->runAction(lastDeleteAction);
		}
		else
		{
			mCloudVector.at(i)->runAction(startDeleteAction);
		}
	}

	mGameState = GAME_STATE::DELETE_CLOUD_UPDATE;

}
void GameScene::DeleteCloudUpdate(float delta)
{

}
void GameScene::DeleteCloudEnd()
{
	mGameState = GAME_STATE::MOVE_CHARACTER_INIT;
}


void GameScene::MoveCharacterInit()
{
	this->mCharaSprite->setPosition(this->mMovePointVector.at(0));

	auto startpoint = dynamic_cast<Sprite*>(mStageNode->getChildByName("startpoint"));
	Rect charaRect = mCharaSprite->getBoundingBox();
	if (charaRect.intersectsRect(startpoint->getBoundingBox()) == true)
	{
		log("start");
		mStartPointCheck = true;
	}
	else
	{
		GlobalValue::getInstance().AddCharaLife(-1);
		UpdateLifePointButton();
	}

	Vector<FiniteTimeAction*> actions;

	auto checkDeleteFunc = CallFuncN::create([this](Ref* obj){
		Rect charaRect = this->mCharaSprite->getBoundingBox();
		SpawnObjectManager::getInstance().CheckHitObject(mStageNode, charaRect);
		UpdateLifePointButton();
	});

	for (int i = 1; i < mMovePointVector.size(); i++)
	{
		auto func = CallFuncN::create([i, this](Ref* obj){
			auto name = StringUtils::format("%d", i);
			this->removeChildByName(name.c_str());
		});

		actions.pushBack(MoveTo::create(0.02f, this->mMovePointVector.at(i)));
		actions.pushBack(func);
		actions.pushBack(checkDeleteFunc);
	}

	auto goalCheckFunc = CallFuncN::create([this](Ref* obj){
		auto goalpoint = dynamic_cast<Sprite*>(this->mStageNode->getChildByName("goalpoint"));
		Rect charaRect = this->mCharaSprite->getBoundingBox();
		if (charaRect.intersectsRect(goalpoint->getBoundingBox()) == true)
		{
			log("goal");
			this->mGoalPointCheck = true;
		}
		else
		{
			GlobalValue::getInstance().AddCharaLife(-1);
			UpdateLifePointButton();
		}
	});
	actions.pushBack(goalCheckFunc);

	auto clearVecFunc = CallFuncN::create([this](Ref* obj){
		this->mMovePointVector.clear();
		this->mGameState = GAME_STATE::MOVE_CHARACTER_END;
		log("clear");
	});
	actions.pushBack(clearVecFunc);

	auto sequenceVec = Sequence::create(actions);
	this->mCharaSprite->runAction(sequenceVec);

	mGameState = GAME_STATE::MOVE_CHARACTER_UPDATE;
}
void GameScene::MoveCharacterUpdate(float delta)
{
}
void GameScene::MoveCharacterEnd()
{
	if (GlobalValue::getInstance().GetCharaLife() <= 0)
	{
		mGameState = GAME_STATE::FAILED_INFORMATION_INIT;
	}
	else
	{
		// 本来はここでクリアかどうかの判定が入る
		GlobalValue::getInstance().SetAreaId(GlobalValue::getInstance().GetAreaId() + 1);
		if (GlobalValue::getInstance().GetAreaId() > GlobalValue::getInstance().GetStageValue())
		{
			mGameState = GAME_STATE::CLEAR_INFORMATION_INIT;
		}
		else
		{
			StageDestroy();
			mGameState = GAME_STATE::LOAD_STAGE_INIT;
		}
	}
}

void GameScene::LoadStageInit()
{
	mStartPointCheck = false;
	mGoalPointCheck = false;
	mTimeConter = 0.0f;
	mMaxTime = 5.0f;

	GlobalValue::getInstance().SetExpValue(0);

	auto stageString = StringUtils::format("res/GameScene/Stage%d/Stage%d_%d.csb", GlobalValue::getInstance().GetStageId(), GlobalValue::getInstance().GetStageId(), GlobalValue::getInstance().GetAreaId());

	mStageNode = CSLoader::createNode(stageString);

	addChild(mStageNode, (int)GAME_LAYER::STAGE_LAYER);

	mGameState = GAME_STATE::LOAD_STAGE_END;
}
void GameScene::LoadStageUpdate(float delta)
{

}
void GameScene::LoadStageEnd()
{
	mGameState = GAME_STATE::AREA_EFFECT_INIT;
}

void GameScene::FailedInformationInit()
{
	mFailedNode = CSLoader::createNode("res/GameScene/FailedInformation.csb");
	auto yesbutton = dynamic_cast<ui::Button*>(mFailedNode->getChildByName("yesButton"));
	struct callBackFunctor {
		void operator() (Ref* sender) const {
			auto basescene = Director::getInstance()->getRunningScene();
			GameScene* gamescene = (GameScene*)basescene->getChildren().at(1);
			gamescene->StageDestroy();
			gamescene->removeChild(gamescene->mFailedNode);
			GlobalValue::getInstance().SetAreaId(1);
			mGameState = GAME_STATE::LOAD_STAGE_INIT;
		}
	};
	ui::Widget::ccWidgetClickCallback callback = callBackFunctor();
	yesbutton->addClickEventListener(callback);

	auto nobutton = dynamic_cast<ui::Button*>(mFailedNode->getChildByName("noButton"));
	struct callBackFunctor2 {
		void operator() (Ref* sender) const {
			auto basescene = Director::getInstance()->getRunningScene();
			GameScene* gamescene = (GameScene*)basescene->getChildren().at(1);
			gamescene->StageDestroy();
			gamescene->removeChild(gamescene->mFailedNode);
			Director::getInstance()->replaceScene(StageSelectScene::createScene());
		}
	};
	ui::Widget::ccWidgetClickCallback callback2 = callBackFunctor2();
	nobutton->addClickEventListener(callback2);

	addChild(mFailedNode, (int)GAME_LAYER::INFORMATION_LAYER);
	mGameState = GAME_STATE::FAILED_INFORMATION_UPDATE;
}
void GameScene::FailedInformationUpdate(float delta)
{

}
void GameScene::FailedInformationEnd()
{

}

void GameScene::ClearInformationInit()
{
	mClearNode = CSLoader::createNode("res/GameScene/ClearInformation.csb");
	auto okbutton = dynamic_cast<ui::Button*>(mClearNode->getChildByName("okButton"));
	struct callBackFunctor {
		void operator() (Ref* sender) const {
			auto basescene = Director::getInstance()->getRunningScene();
			GameScene* gamescene = (GameScene*)basescene->getChildren().at(1);
			gamescene->StageDestroy();
			gamescene->removeChild(gamescene->mClearNode);
			Director::getInstance()->replaceScene(StageSelectScene::createScene());
		}
	};
	ui::Widget::ccWidgetClickCallback callback = callBackFunctor();
	okbutton->addClickEventListener(callback);

	addChild(mClearNode, (int)GAME_LAYER::INFORMATION_LAYER);
	mGameState = GAME_STATE::CLEAR_INFORMATION_UPDATE;
}
void GameScene::ClearInformationUpdate(float delta)
{

}
void GameScene::ClearInformationEnd()
{

}

void GameScene::StageDestroy()
{
	SpawnObjectManager::getInstance().DestroySpawnObject();
	removeChild(mStageNode);
}
