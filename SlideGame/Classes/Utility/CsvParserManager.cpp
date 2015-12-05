// ============================================================
//!		@file		CsvParserManager.cpp
//!		@brief		バトルシーン
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#include "CsvParserManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// ============================================================
//!		@brief		インスタンス取得関数
//!		@note		
//!		@return		エフェクトマネージャインスタンス
//!		@retval		instance
// ============================================================
CsvParserManager &CsvParserManager::getInstance() {
	static CsvParserManager instance;
	return instance;
}

// ============================================================
//!		@brief		初期化
//!		@note		
//!		@return		
// ============================================================
void CsvParserManager::init()
{
	if(mCsvParser == nullptr)
	{
		mCsvParser = new CsvParser();
	}
}

// ============================================================
//!		@brief		文字列をパースして、取得できるデータに分解する
//!		@note		
//!		@return		
// ============================================================
int CsvParserManager::parseString(std::string str)
{
	return mCsvParser->parseString(str);
}

// ============================================================
//!		@brief		行数を指定して、分解したデータを取得する
//!		@note		
//!		@return		
// ============================================================
cocos2d::ValueVector CsvParserManager::getLineVector(int row)
{
	cocos2d::ValueVector vvec = mCsvParser->getLineVector(row);
	return vvec;
}

