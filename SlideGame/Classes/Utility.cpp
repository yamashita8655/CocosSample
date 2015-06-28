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