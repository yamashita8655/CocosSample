#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum class GAME_STATE : int
{
	LOAD_STAGE_INIT,
	LOAD_STAGE_UPDATE,
	LOAD_STAGE_END,

	AREA_EFFECT_INIT,
	AREA_EFFECT_UPDATE,
	AREA_EFFECT_END,

	SPAWN_OBJECT_INIT,
	SPAWN_OBJECT_UPDATE,
	SPAWN_OBJECT_END,

	SPAWN_START_GOAL_INIT,
	SPAWN_START_GOAL_UPDATE,
	SPAWN_START_GOAL_END,

	SPAWN_CLOUD_INIT,
	SPAWN_CLOUD_UPDATE,
	SPAWN_CLOUD_END,

	WAIT,
	DRAW_MOVE_LINE,

	FAILED_INFORMATION_INIT,
	FAILED_INFORMATION_UPDATE,
	FAILED_INFORMATION_END,

	CLEAR_INFORMATION_INIT,
	CLEAR_INFORMATION_UPDATE,
	CLEAR_INFORMATION_END,

	DELETE_CLOUD_INIT,
	DELETE_CLOUD_UPDATE,
	DELETE_CLOUD_END,

	MOVE_CHARACTER_INIT,
	MOVE_CHARACTER_UPDATE,
	MOVE_CHARACTER_END,
};

enum class GAME_STATE2 : int
{
	STARTUP,
	LOAD_STAGE,
	DISPLAY_AREA_TEXT,
	SPAWN_OBJECT,
};

enum class GAME_LAYER : int
{
	STAGE_LAYER = 10,
	CLOUD_LAYER = 17,
	LINE_LAYER = 18,
	MOVE_CHARA_LAYER = 19,
	STAGE_FRONT_LAYER = 20,
	INFORMATION_LAYER = 30,
};

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

public:
	cocos2d::Node* mRootNode;
	cocos2d::Node* mStageNode;
	cocos2d::Node* mFailedNode;
	cocos2d::Node* mClearNode;

	cocos2d::Vec2 mPrevPoint;
	std::vector<cocos2d::Vec2> mMovePointVector;

	cocos2d::Sprite* mCharaSprite;
	cocos2d::ui::Text* mCountDownTimeText;

	cocos2d::Sprite* mStartSprite;
	cocos2d::Sprite* mGoalSprite;

	std::vector<cocos2d::Sprite*> mCloudVector;

	
	static GAME_STATE mGameState;

	float mMaxDistance;
	float mNowDistance;

	bool mStartPointCheck;
	bool mGoalPointCheck;

	void update(float delta);

	float mMaxTime;
	float mTimeConter;

	std::vector<cocos2d::ui::Button*> mCharacterLifeButton;
	void UpdateLifePointButton();

//	void (GameScene::*fpFunc)();

	static void Endfunction();

	void CreateStartGoalAction();

	void LoadStageInit();
	void LoadStageUpdate(float delta);
	void LoadStageEnd();

	void AreaEffectInit();
	void AreaEffectUpdate(float delta);
	void AreaEffectEnd();

	void SpawnObjectInit();
	void SpawnObjectUpdate(float delta);
	void SpawnObjectEnd();

	void SpawnStartGoalInit();
	void SpawnStartGoalUpdate(float delta);
	void SpawnStartGoalEnd();

	void SpawnCloudInit();
	void SpawnCloudUpdate(float delta);
	void SpawnCloudEnd();

	void DeleteCloudInit();
	void DeleteCloudUpdate(float delta);
	void DeleteCloudEnd();

	void MoveCharacterInit();
	void MoveCharacterUpdate(float delta);
	void MoveCharacterEnd();

	void FailedInformationInit();
	void FailedInformationUpdate(float delta);
	void FailedInformationEnd();

	void ClearInformationInit();
	void ClearInformationUpdate(float delta);
	void ClearInformationEnd();

	void StageDestroy();
};


#endif // __GAME_SCENE_H__
