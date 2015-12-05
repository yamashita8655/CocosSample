#include "Utility.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <random>

RandomCreator &RandomCreator::getInstance() {
	static RandomCreator instance;
	return instance;
}

void RandomCreator::init()
{
	std::random_device rd;
	mRandom.seed(rd());
}

int RandomCreator::GetRandomMinToMax(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mRandom);
}

GlobalValue &GlobalValue::getInstance() {
	static GlobalValue instance;
	return instance;
}

void GlobalValue::AddCharaLife(int add)
{
	mCharaLife += add;
	if (mCharaLife > (int)GAME_CONST::MAX_LIFE)
	{
		mCharaLife = (int)GAME_CONST::MAX_LIFE;
	}

	if (mCharaLife < 0)
	{
		mCharaLife = 0;
	}
}

void GlobalValue::AddExpValue(int add)
{
	mExpValue += add;
	if (mExpValue < 0)
	{
		mExpValue = 0;
	}
}
	
void GlobalValue::setStartPointCheck(bool value)
{
	mStartPointCheck = value;
}
bool GlobalValue::getStartPointCheck()
{
	return mStartPointCheck;
}
void GlobalValue::setGoalPointCheck(bool value)
{
	mGoalPointCheck = value;
}
bool GlobalValue::getGoalPointCheck()
{
	return mGoalPointCheck;
}
void GlobalValue::setMaxTime(float value)
{
	mMaxTime = value;
}
float GlobalValue::getMaxTime()
{
	return mMaxTime;
}
void GlobalValue::setTimeCounter(float value)
{
	mTimeCounter = value;
}
float GlobalValue::getTimeCounter()
{
	return mTimeCounter;
}
void GlobalValue::setStageNode(cocos2d::Node* node)
{
	mStageNode = node;
}
cocos2d::Node* GlobalValue::getStageNode()
{
	return mStageNode;
}
void GlobalValue::setMaxDistance(float value)
{
	mMaxDistance = value;
}
float GlobalValue::getMaxDistance()
{
	return mMaxDistance;
}
void GlobalValue::setNowDistance(float value)
{
	mNowDistance = value;
}
float GlobalValue::getNowDistance()
{
	return mNowDistance;
}
void GlobalValue::setRootNode(cocos2d::Node* node)
{
	mRootNode = node;
}
cocos2d::Node* GlobalValue::getRootNode()
{
	return mRootNode;
}

// ============================================================
//!		@brief		インスタンス取得関数
//!		@note		
//!		@return		シーンマネージャインスタンス
//!		@retval		instance
// ============================================================
Utility &Utility::getInstance() {
	static Utility instance;
	return instance;
}

// ============================================================
//!		@brief		文字列分割
//!		@note		
//!		@param[in]	str		文字列
//!		@param[in]	delim	分割文字
//!		@return		分割後配列
// ============================================================
ValueVector Utility::split(const std::string &str, const std::string &delim)
{
	ValueVector res;
	size_t current = 0;
	size_t found = 0;

	while ((found = str.find(delim.c_str(), current, delim.size())) != std::string::npos)
	{
		res.push_back(Value(std::string(str, current, found - current)));
		current = found + delim.size();
	}
	res.push_back(Value(std::string(str, current, str.size() - current)));

	/*	std::string lastStr = std::string(str, current, str.size() - current);
	if (lastStr.size() != 0)
	{
	res.push_back(Value(lastStr));
	}*/
	return res;
}
