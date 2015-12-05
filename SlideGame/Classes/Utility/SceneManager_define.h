// ============================================================
//!		@file		SceneManager_define.h
//!		@brief		シーンマネージャで使う値
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __SCENE_MANAGER_DEFINE_H__
#define __SCENE_MANAGER_DEFINE_H__

enum class SCENE_NAME : int
{
	NONE,
	STAGE_SELECT,
	CHARACTER_SELECT,
	GAME,
};

enum class ZORDER : int
{
	NONE,
	MOVIE,
	SYSTEM,
	MAX,
};

#define LAYER_NAME_NONE				"none"
#define LAYER_NAME_GAME				"game"
#define LAYER_NAME_STAGE_SELECT		"stageselect"
#define LAYER_NAME_CHARACTER_SELECT "characterselect"

#define LAYER_NAME_LAYER1 "Layer1"
#define LAYER_NAME_LAYER2 "Layer2"
#define LAYER_NAME_LAYER3 "Layer3"
#define LAYER_NAME_SYSTEM "System"

#define LAYER_NAME_TEST_QUEST "quest"
#define LAYER_NAME_CARDTABLE "cardtable"

#define LAYER_NAME_TESTMENU	"testmenu"

#endif // __SCENE_MANAGER_DEFINE_H__
