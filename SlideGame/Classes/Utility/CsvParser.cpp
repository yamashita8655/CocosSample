// ============================================================
//!		@file		CsvParser.cpp
//!		@brief		Csvパーサー
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#include "CsvParser.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Utility.h"

USING_NS_CC;

// ============================================================
//!		@brief		文字列をパースして、取得できるデータに分解する
//!		@note		
//!		@return		
// ============================================================
int CsvParser::parseString(std::string str)
{
	mParseData = Utility::getInstance().split(str, "\r\n");
	return mParseData.size();
}

// ============================================================
//!		@brief		行数を指定して、分解したデータを取得する
//!		@note		
//!		@return		
// ============================================================
cocos2d::ValueVector CsvParser::getLineVector(int row)
{
	cocos2d::ValueVector vvec = Utility::getInstance().split(mParseData.at(row).asString(), ",");
	return vvec;
}
