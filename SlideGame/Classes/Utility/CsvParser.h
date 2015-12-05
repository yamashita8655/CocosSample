// ============================================================
//!		@file		CsvParser.h
//!		@brief		Csvパーサー
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __CSVPARSER_H__
#define __CSVPARSER_H__
#include "cocos2d.h"

// ============================================================
//!		@brief		Csvパーサー
//!		@note		,区切りのテキストデータを配列にして返してくれる
//!		@attention	
//!		@warning	
// ============================================================
class CsvParser 
{
public:
	CsvParser(){};
	virtual ~CsvParser(){}

	int parseString(std::string str);
	cocos2d::ValueVector getLineVector(int row);

private:
	cocos2d::ValueVector mParseData;
};

#endif // __CSVPARSER_H__
