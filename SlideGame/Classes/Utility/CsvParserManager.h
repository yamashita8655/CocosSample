// ============================================================
//!		@file		CsvParserManager.h
//!		@brief		CSVパーサーを使いまわすマネージャ
//!		@note	
//!		@attention	
//!		@warning	
// ============================================================
#ifndef __CSVPARSER_MANAGER_H__
#define __CSVPARSER_MANAGER_H__

#include "cocos2d.h"
#include "CsvParser.h"

// ============================================================
//!		@brief		CSVパーサーマネージャ
//!		@note		
//!		@attention	
//!		@warning	
// ============================================================
class CsvParserManager 
{
public:
	static CsvParserManager &getInstance();

private:
	CsvParserManager(){};
	CsvParserManager(const CsvParserManager &other){}
	CsvParserManager &operator=(const CsvParserManager &other){}

private:
	CsvParser* mCsvParser;

public:
	void init();
	int parseString(std::string str);
	cocos2d::ValueVector getLineVector(int row);
};

#endif // __CSVPARSER_MANAGER_H__
