#ifndef __SPAWNOBJECT_MANAGER_H__
#define __SPAWNOBJECT_MANAGER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include <random>

enum class SPAWNOBJECT_TYPE : int
{
	EXP = 0,
	TRAP_SPIKE = 1,
	TRAP_RED_SPIKE = 2,
	TRAP_GREEN_SPIKE = 3,
	TRAP_BLUE_SPIKE = 4,
	TRAP_RED_SPIKE_BREAK = 5,
	TRAP_GREEN_SPIKE_BREAK = 6,
	TRAP_BLUE_SPIKE_BREAK = 7
};

class SpawnObject
{
public:
	SpawnObject();

	void SetSprite(cocos2d::Sprite* sprite){ mSprite = sprite; }
	cocos2d::Sprite* GetSprite(){ return mSprite; }

	void SetType(SPAWNOBJECT_TYPE type){ mType = type; }
	SPAWNOBJECT_TYPE GetType(){ return mType; }


private:
	SPAWNOBJECT_TYPE mType;
	cocos2d::Sprite* mSprite;
};

class SpawnObjectManager
{
public:
	static SpawnObjectManager &getInstance();

private:
	SpawnObjectManager(){};
	SpawnObjectManager(const SpawnObjectManager &other){}
	SpawnObjectManager &operator=(const SpawnObjectManager &other){}

private:
	std::vector<SpawnObject*> mSpawnObjectVector;

public:
//	void CreateSpawnObject(cocos2d::Node* scene, int posx, int posy);
	void CheckHitObject(cocos2d::Node* scene, Rect rect);

	void AddSpawnObject(SpawnObject* obj);

	void CreateSpawnObjectAction(int index);

	int GetSpawnObjectVectorSize(){ return mSpawnObjectVector.size(); }
	std::vector<SpawnObject*> GetSpawnObjectVector(){ return mSpawnObjectVector; }

	void DestroySpawnObject();

	void RemoveRedSpikeTrap(cocos2d::Node* scene);
	void RemoveGreenSpikeTrap(cocos2d::Node* scene);
	void RemoveBlueSpikeTrap(cocos2d::Node* scene);

};


#endif // __SPAWNOBJECT_MANAGER_H__
