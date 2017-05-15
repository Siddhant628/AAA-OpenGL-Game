#include "GameManager.h"
#include "GameObject.h"
#include "Plane.h"
#include "Turret.h"
#include "Bullet.h"
#include "game.h"

#include <cassert>
#include <time.h>

using namespace Engine;

namespace AAA
{
	const std::string GameManager::sBackgroundSpritePath = "Sprites/Background.png";

	const std::string GameManager::sTurretBaseSpritePath = "Sprites/TurretBase.png";
	const float_t GameManager::sPositionTurretBaseAX = 100.0f;
	const float_t GameManager::sPositionTurretBaseAY = 35.0f;
	const float_t GameManager::sPositionTurretBaseBX = 867.0f;
	const float_t GameManager::sPositionTurretBaseBY = 35.0f;
	const uint32_t GameManager::sTurretBaseWidth = 57;
	const uint32_t GameManager::sTurretBaseHeight = 53;

	const float_t GameManager::sEndGamePositionX = 0.0f;
	const float_t GameManager::sEndGamePositionY = 268.0f;
	const uint32_t GameManager::sEndGameWidth = 1024;
	const uint32_t GameManager::sEndGameHeight = 500;
	const std::string GameManager::sEndGameSprite = "Sprites/GameEnd.png";

	const uint32_t GameManager::sLivesCount = 5;
	const uint32_t GameManager::sLivesWidth = 20;
	const uint32_t GameManager::sLivesHeight = 20;
	const float_t GameManager::sLivesPositionOffsetX = 30.0f;
	const float_t GameManager::sLivesPositionOffsetY = 5.0f;
	const std::string GameManager::sLivesSpritePlayerA = "Sprites/LivesA.png";
	const std::string GameManager::sLivesSpritePlayerB = "Sprites/LivesB.png";

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::CreateInstance()
	{
		if (!sInstance)
		{
			sInstance = new GameManager;
		}
		return sInstance;
	}

	GameManager* GameManager::GetInstance()
	{
		return sInstance;
	}

	void GameManager::Initialize()
	{
		srand(time(nullptr));
		LoadBackground();
		LoadPlanes();
		LoadBullets();
		LoadTurrets();
		LoadLivesSprites();
		LoadEndGameScreen();
	}

	void GameManager::Update(DWORD milliseconds)
	{
		mCurrentTime += milliseconds;
		if (mGameIsRunning)
		{
			PlanesUpdate(mCurrentTime);
		}
	}

	void GameManager::Shutdown()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::RegisterPlane(Plane& plane)
	{
		if (plane.GetPlaneID() == Plane::PlaneID::PlaneA_1 || plane.GetPlaneID() == Plane::PlaneID::PlaneA_2)
		{
			mPlanesPlayerA.push_back(&plane);
		}
		else if (plane.GetPlaneID() == Plane::PlaneID::PlaneB_1 || plane.GetPlaneID() == Plane::PlaneID::PlaneB_2)
		{
			mPlanesPlayerB.push_back(&plane);
		}
	}

	bool GameManager::IsGameRunning()
	{
		return mGameIsRunning;
	}

	void GameManager::RestartGame()
	{
		assert(GameManager::GetInstance() != nullptr);
		if (!GameManager::GetInstance()->IsGameRunning())
		{
			ResetLives();
			ResetPlanes();
			// Enable the game
			mCurrentTime = 0;
			mEndGameScreen->GetSprite()->Disable();
			mGameIsRunning = true;
		}
	}

	GameManager::GameManager() : mGameIsRunning(true), mEndGameScreen(nullptr), mCurrentTime(0)
	{

	}

	void GameManager::DecrementHealth(PlayerEnum playerEnum)
	{
		if (mGameIsRunning)
		{
			switch (playerEnum)
			{
			case PlayerEnum::PlayerA:
				(*mCurrentHealthA)->GetSprite()->Disable();
				if (mCurrentHealthA == mLivesPlayerA.begin())
				{
					EndGame();
					return;
				}
				mCurrentHealthA--;
				break;
			case PlayerEnum::PlayerB:
				(*mCurrentHealthB)->GetSprite()->Disable();
				mCurrentHealthB++;
				if (mCurrentHealthB == mLivesPlayerB.end())
				{
					EndGame();
				}
				break;
			}
		}
	}

	void GameManager::EndGame()
	{
		// TODO Lose condition
		mEndGameScreen->GetSprite()->Enable();
		mGameIsRunning = false;
	}

	void GameManager::ResetLives()
	{
		// Enable all the health sprites
		auto end = mLivesPlayerA.end();
		for (auto it = mLivesPlayerA.begin(); it != end; ++it)
		{
			(*it)->GetSprite()->Enable();
		}
		end = mLivesPlayerB.end();
		for (auto it = mLivesPlayerB.begin(); it != end; ++it)
		{
			(*it)->GetSprite()->Enable();
		}
		// Reset the current health pointers
		mCurrentHealthA = --mLivesPlayerA.end();
		mCurrentHealthB = mLivesPlayerB.begin();
	}

	void GameManager::ResetPlanes()
	{
		auto end = mPlanesPlayerA.end();
		for (auto it = mPlanesPlayerA.begin(); it != end; ++it)
		{
			(*it)->ResetPlane();
		}
		end = mPlanesPlayerB.end();
		for (auto it = mPlanesPlayerB.begin(); it != end; ++it)
		{
			(*it)->ResetPlane();
		}
	}

	void GameManager::LoadBackground()
	{
		GameObject* backgroundObject = new GameObject;
		backgroundObject->AttachSprite();
		backgroundObject->GetSprite()->Initialize(CGame::mScreenWidth, CGame::mScreenHeight, sBackgroundSpritePath);
	}

	void GameManager::LoadPlanes()
	{
		new Plane(Plane::PlaneID::PlaneA_1);
		new Plane(Plane::PlaneID::PlaneA_2);
		new Plane(Plane::PlaneID::PlaneB_1);
		new Plane(Plane::PlaneID::PlaneB_2);
	}

	void GameManager::LoadBullets()
	{
		new Bullet(Bullet::BulletOwner::PlayerA);
		new Bullet(Bullet::BulletOwner::PlayerA);
		new Bullet(Bullet::BulletOwner::PlayerA);
		new Bullet(Bullet::BulletOwner::PlayerB);
		new Bullet(Bullet::BulletOwner::PlayerB);
		new Bullet(Bullet::BulletOwner::PlayerB);
	}

	void GameManager::LoadTurrets()
	{
		new Turret(PlayerEnum::PlayerA);
		new Turret(PlayerEnum::PlayerB);
		GameObject* turretBaseA = new GameObject;
		turretBaseA->AttachSprite();
		turretBaseA->SetPosition(sPositionTurretBaseAX, sPositionTurretBaseAY);
		turretBaseA->GetSprite()->Initialize(sTurretBaseWidth, sTurretBaseHeight, sTurretBaseSpritePath);
		GameObject* turretBaseB = new GameObject;
		turretBaseB->AttachSprite();
		turretBaseB->SetPosition(sPositionTurretBaseBX, sPositionTurretBaseBY);
		turretBaseB->GetSprite()->Initialize(sTurretBaseWidth, sTurretBaseHeight, sTurretBaseSpritePath);
	}

	void GameManager::LoadLivesSprites()
	{
		for (uint32_t i = 0; i < sLivesCount; ++i)
		{
			mLivesPlayerA.push_back(new GameObject);
			auto it = mLivesPlayerA.end();
			--it;
			(*it)->AttachSprite();
			(*it)->GetSprite()->Initialize(sLivesWidth, sLivesHeight, sLivesSpritePlayerA);
			(*it)->SetPosition(10 + sLivesPositionOffsetX * i, sLivesPositionOffsetY);

			mLivesPlayerB.push_back(new GameObject);
			it = mLivesPlayerB.end();
			--it;
			(*it)->AttachSprite();
			(*it)->GetSprite()->Initialize(sLivesWidth, sLivesHeight, sLivesSpritePlayerB);
			(*it)->SetPosition(994 - sLivesPositionOffsetX * i, sLivesPositionOffsetY);
		}
		mCurrentHealthA = --mLivesPlayerA.end();
		mCurrentHealthB = mLivesPlayerB.begin();
	}

	void GameManager::LoadEndGameScreen()
	{
		mEndGameScreen = new GameObject;
		mEndGameScreen->SetPosition(sEndGamePositionX, sEndGamePositionY);
		mEndGameScreen->AttachSprite();
		mEndGameScreen->GetSprite()->Disable();
		mEndGameScreen->GetSprite()->Initialize(sEndGameWidth, sEndGameHeight, sEndGameSprite);
	}

	void GameManager::PlanesUpdate(DWORD currentTime)
	{
		// Check if all planes are ready for respawning.
		auto it = mPlanesPlayerA.begin();
		auto end = mPlanesPlayerA.end();

		for (; it != end; ++it)
		{
			if (!(*it)->RequiresRespawn())
			{
				return;
			}
		}
		it = mPlanesPlayerB.begin();
		end = mPlanesPlayerB.end();
		for (; it != end; ++it)
		{
			if (!(*it)->RequiresRespawn())
			{
				return;
			}
		}
		// Check which planes did enter the enemy territory, update health accordingly, then respawn them.
		it = mPlanesPlayerB.begin();
		for (; it != end; ++it)
		{
			if ((*it)->GetPosition().x < Plane::sSpawnPositionA1X)
			{
				DecrementHealth(PlayerEnum::PlayerA);
			}
			(*it)->Respawn(currentTime);
		}

		it = mPlanesPlayerA.begin();
		end = mPlanesPlayerA.end();
		for (; it != end; ++it)
		{
			if ((*it)->GetPosition().x > Plane::sSpawnPositionB1X)
			{
				DecrementHealth(PlayerEnum::PlayerB);
			}
			(*it)->Respawn(currentTime);
		}
	}
}