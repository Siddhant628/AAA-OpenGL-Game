#include "GameObjectManager.h"
#include "GameObject.h"

namespace Engine
{
	GameObjectManager* GameObjectManager::sInstance = nullptr;
	
	GameObjectManager* GameObjectManager::CreateInstance()
	{
		if (!sInstance)
		{
			sInstance = new GameObjectManager();
		}
		return sInstance;
	}

	GameObjectManager* GameObjectManager::GetInstance()
	{
		return sInstance;
	}

	void GameObjectManager::Initialize()
	{

	}

	void GameObjectManager::Update(DWORD milliseconds)
	{
		ClearDeleteQueue();

		std::vector<GameObject*>::iterator it = mGameObjects.begin();
		std::vector<GameObject*>::iterator end = mGameObjects.end();

		for (; it != end; ++it)
		{
			(*it)->Update(milliseconds);
		}
	}

	void GameObjectManager::Register(GameObject& gameObject)
	{
		mGameObjects.push_back(&gameObject);
	}

	void GameObjectManager::Unregister(GameObject& gameObject)
	{
		mDeleteQueue.push_back(&gameObject);
	}

	void GameObjectManager::Render()
	{
		std::vector<GameObject*>::iterator it = mGameObjects.begin();
		std::vector<GameObject*>::iterator end = mGameObjects.end();

		for (; it != end; ++it)
		{
			Sprite* sprite = (*it)->GetSprite();
			if (sprite)
			{
				sprite->Render();
			}
		}
	}

	void GameObjectManager::Shutdown()
	{
		std::vector<GameObject*>::iterator it = mGameObjects.begin();
		std::vector<GameObject*>::iterator end = mGameObjects.end();

		for (; it != end; ++it)
		{
			delete *it;
		}
		delete sInstance;
		sInstance = nullptr;
	}

	void GameObjectManager::ClearDeleteQueue()
	{
		std::vector<GameObject*>::iterator end = mDeleteQueue.end();
		for (auto it = mDeleteQueue.begin(); it != end; ++it)
		{
			auto itDelete = std::find(mGameObjects.begin(), mGameObjects.end(), *it);
			mGameObjects.erase(itDelete);
		}
		mDeleteQueue.clear();
	}
}