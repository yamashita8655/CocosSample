#include "SpawnObjectManager.h"
#include "Utility.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <random>

SpawnObject::SpawnObject() :
mType(SPAWNOBJECT_TYPE::EXP),
mSprite(nullptr)
{

}

SpawnObjectManager &SpawnObjectManager::getInstance() {
	static SpawnObjectManager instance;
	return instance;
}

/*void SpawnObjectManager::CreateSpawnObject(cocos2d::Node* scene, int posx, int posy)
{
	SpawnObject* obj = new SpawnObject();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto spriteName = StringUtils::format("GameScene/exp.png");
	auto sprite = Sprite::create(spriteName.c_str());
	obj->SetSprite(sprite);
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x + posx, visibleSize.height / 2 + origin.y + posy));
	scene->addChild(sprite, 2);

	mSpawnObjectVector.push_back(obj);
}*/

void SpawnObjectManager::setEndSpawnObjectCallback(cocos2d::CallFunc* call)
{
	mEndSpawnObjectCallback = call;
}


void SpawnObjectManager::CheckHitObject(cocos2d::Node* scene, Rect rect)
{
	auto it = mSpawnObjectVector.begin();

	while (it != mSpawnObjectVector.end())
	{
		if (rect.intersectsRect((*it)->GetSprite()->getBoundingBox()) == true)
		{
			if ((*it)->GetType() == SPAWNOBJECT_TYPE::EXP)
			{
				GlobalValue::getInstance().AddExpValue(1);
				if (GlobalValue::getInstance().GetExpValue() % 5 == 0)
				{
					GlobalValue::getInstance().AddCharaLife(1);
				}
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_SPIKE)
			{
				GlobalValue::getInstance().AddCharaLife(-1);
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_RED_SPIKE)
			{
				GlobalValue::getInstance().AddCharaLife(-1);
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE)
			{
				GlobalValue::getInstance().AddCharaLife(-1);
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE)
			{
				GlobalValue::getInstance().AddCharaLife(-1);
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_RED_SPIKE_BREAK)
			{
				scene->removeChild((*it)->GetSprite());
				auto delObj = (*it);
				mSpawnObjectVector.erase(it);
				delete delObj;
				RemoveRedSpikeTrap(scene);
				it = mSpawnObjectVector.begin();
				continue;
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE_BREAK)
			{
				scene->removeChild((*it)->GetSprite());
				auto delObj = (*it);
				mSpawnObjectVector.erase(it);
				delete delObj;
				RemoveGreenSpikeTrap(scene);
				it = mSpawnObjectVector.begin();
				continue;
			}
			else if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE_BREAK)
			{
				scene->removeChild((*it)->GetSprite());
				auto delObj = (*it);
				mSpawnObjectVector.erase(it);
				delete delObj;
				RemoveBlueSpikeTrap(scene);
				it = mSpawnObjectVector.begin();
				continue;
			}

			scene->removeChild((*it)->GetSprite());
			auto eraseIt = (*it);
			it = mSpawnObjectVector.erase(it);
			delete eraseIt;
		}
		else
		{
			it++;
		}
	}
}

bool CheckDeleteRedSpikeFunction(SpawnObject* obj)
{
	if (obj->GetType() == SPAWNOBJECT_TYPE::TRAP_RED_SPIKE)
	{
		return true;
	}
	return false;
}
bool CheckDeleteGreenSpikeFunction(SpawnObject* obj)
{
	if (obj->GetType() == SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE)
	{
		return true;
	}
	return false;
}
bool CheckDeleteBlueSpikeFunction(SpawnObject* obj)
{
	if (obj->GetType() == SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE)
	{
		return true;
	}
	return false;
}

void SpawnObjectManager::RemoveRedSpikeTrap(cocos2d::Node* scene)
{
	auto it = mSpawnObjectVector.begin();
	while (it != mSpawnObjectVector.end())
	{
		if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_RED_SPIKE)
		{
			scene->removeChild((*it)->GetSprite());
			auto eraseIt = (*it);
			it = mSpawnObjectVector.erase(it);
			delete eraseIt;
		}
		else
		{
			it++;
		}
	}
}
void SpawnObjectManager::RemoveGreenSpikeTrap(cocos2d::Node* scene)
{
	auto it = mSpawnObjectVector.begin();
	while (it != mSpawnObjectVector.end())
	{
		if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_GREEN_SPIKE)
		{
			scene->removeChild((*it)->GetSprite());
			auto eraseIt = (*it);
			it = mSpawnObjectVector.erase(it);
			delete eraseIt;
		}
		else
		{
			it++;
		}
	}
}
void SpawnObjectManager::RemoveBlueSpikeTrap(cocos2d::Node* scene)
{
	auto it = mSpawnObjectVector.begin();
	while (it != mSpawnObjectVector.end())
	{
		if ((*it)->GetType() == SPAWNOBJECT_TYPE::TRAP_BLUE_SPIKE)
		{
			scene->removeChild((*it)->GetSprite());
			auto eraseIt = (*it);
			it = mSpawnObjectVector.erase(it);
			delete eraseIt;
		}
		else
		{
			it++;
		}
	}
}

void SpawnObjectManager::AddSpawnObject(SpawnObject* obj)
{
	mSpawnObjectVector.push_back(obj);
}

void SpawnObjectManager::CreateSpawnObjectAction(int index)
{
	auto sprite = mSpawnObjectVector.at(index)->GetSprite();
	sprite->setScale(3.0f, 3.0f);

	Vector<FiniteTimeAction*> actions;
	auto visibleOnFunc = CallFuncN::create([sprite, this](Ref* obj){
		sprite->setVisible(true);
	});

	auto visibleOffFunc = CallFuncN::create([sprite, this](Ref* obj){
		sprite->setVisible(false);
	});

	auto nextSpriteFunc = CallFuncN::create([index, this](Ref* obj){
		if ((index+1) < this->GetSpawnObjectVectorSize())
		{
			this->CreateSpawnObjectAction(index + 1);
		}
		else
		{
			// VisibleをTrueにするのは仮
			auto vec =  this->GetSpawnObjectVector();
			for (int i = 0; i < vec.size(); i++)
			{
				vec.at(i)->GetSprite()->setVisible(true);
			}

			if (mEndSpawnObjectCallback != nullptr)
			{
				mEndSpawnObjectCallback->execute();
				mEndSpawnObjectCallback->release();
				mEndSpawnObjectCallback = nullptr;
			}
			//GameScene::Endfunction();
		}
	});

	actions.pushBack(visibleOnFunc);
	actions.pushBack(ScaleTo::create(0.5f, 1.0f));
	actions.pushBack(visibleOffFunc);
	actions.pushBack(nextSpriteFunc);

	auto sequenceVec = Sequence::create(actions);
	sprite->runAction(sequenceVec);
}

void SpawnObjectManager::DestroySpawnObject()
{
	for (int i = 0; i < mSpawnObjectVector.size(); i++)
	{
		delete mSpawnObjectVector.at(i);
	}

	mSpawnObjectVector.clear();
}
