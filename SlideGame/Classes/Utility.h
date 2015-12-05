#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <random>

enum class GAME_CONST : int
{
	MAX_LIFE = 5,
};

class RandomCreator
{
public:
	static RandomCreator &getInstance();

private:
	RandomCreator(){};
	RandomCreator(const RandomCreator &other){}
	RandomCreator &operator=(const RandomCreator &other){}

private:
	std::mt19937		mRandom;
	void init();

public:
	int GetRandomMinToMax(int min, int max);
};

class GlobalValue
{
public:
	static GlobalValue &getInstance();

private:
	GlobalValue(){};
	GlobalValue(const GlobalValue &other){}
	GlobalValue &operator=(const GlobalValue &other){}

private:
	int mCharaId;
	float mMoveDistance;
	int mCharaLife;
	int mExpValue;
	int mStageId;
	int mAreaId;
	int mStageValue;

	bool mStartPointCheck;
	bool mGoalPointCheck;
	float mMaxTime;
	float mTimeCounter;
	
	cocos2d::Node* mStageNode;
	cocos2d::Node* mRootNode;
	
	float mMaxDistance;
	float mNowDistance;

public:
	void SetCharaId(int id){ mCharaId = id; }
	int GetCharaId(){ return mCharaId; }

	void SetMoveDistance(float distance){ mMoveDistance = distance; }
	float GetMoveDistance(){ return mMoveDistance; }

	void SetCharaLife(int life){ mCharaLife = life; }
	void AddCharaLife(int add);
	int GetCharaLife(){ return mCharaLife; }

	void SetExpValue(int exp){ mExpValue = exp; }
	void AddExpValue(int add);
	int GetExpValue(){ return mExpValue; }

	void SetStageId(int id){ mStageId = id; }
	int GetStageId(){ return mStageId; }

	void SetAreaId(int id){ mAreaId = id; }
	int GetAreaId(){ return mAreaId; }

	void SetStageValue(int value){ mStageValue = value; }
	int GetStageValue(){ return mStageValue; }

	void setStartPointCheck(bool value);
	bool getStartPointCheck();
	
	void setGoalPointCheck(bool value);
	bool getGoalPointCheck();
	
	void setMaxTime(float value);
	float getMaxTime();
	
	void setTimeCounter(float value);
	float getTimeCounter();

	void setStageNode(cocos2d::Node* node);
	cocos2d::Node* getStageNode();
	
	void setMaxDistance(float value);
	float getMaxDistance();
	
	void setNowDistance(float value);
	float getNowDistance();
	
	void setRootNode(cocos2d::Node* node);
	cocos2d::Node* getRootNode();

};

class Utility
{
public:
	static Utility &getInstance();

private:
	Utility(){};
	Utility(const Utility &other){}
	Utility &operator=(const Utility &other){}

private:

public:
	ValueVector split(const std::string &str, const std::string &delim);
};


#endif // __UTILITY_H__
