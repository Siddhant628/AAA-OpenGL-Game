#include "Plane.h"
#include "GameManager.h"
#include "random.h"

#include <cassert>

using namespace Engine;

namespace AAA
{
	const float_t Plane::sSpawnPositionA1X = -100.0f;
	const float_t Plane::sSpawnPositionA1Y = 700.0f;
	const float_t Plane::sSpawnPositionA2X = -100.0f;
	const float_t Plane::sSpawnPositionA2Y = 500.0f;
	const float_t Plane::sSpawnPositionB1X = 1024.0f;
	const float_t Plane::sSpawnPositionB1Y = 700.0f;
	const float_t Plane::sSpawnPositionB2X = 1024.0f;
	const float_t Plane::sSpawnPositionB2Y = 500.0f;
	const float_t Plane::sMinSpawnPositionVarianceY = 5.0f;
	const float_t Plane::sMaxSpawnPositionVarianceY = 50.0f;

	const float_t Plane::sColliderOffsetX = 0;
	const float_t Plane::sColliderOffsetY = 20;
	const uint32_t Plane::sColliderWidth = 100;
	const uint32_t Plane::sColliderHeight = 31;

	const std::string Plane::sSpritePathPlaneA = "Sprites/PlaneA.png";
	const std::string Plane::sSpritePathPlaneB = "Sprites/PlaneB.png";

	const uint32_t Plane::sWidthPlaneA = 100;
	const uint32_t Plane::sHeightPlaneA = 55;
	const uint32_t Plane::sWidthPlaneB = 100;
	const uint32_t Plane::sHeightPlaneB = 48;

	const float_t Plane::sMinimumSpeed = 200.0f;
	const float_t Plane::sMaximumSpeed = 300.0f;
	const float_t Plane::sMinimumSpeedVariance = 25.0f;
	const float_t Plane::sMaximumSpeedVariance = 65.0f;
	const DWORD Plane::sTimeForMaximumSpeed = 60000;

	Plane::Plane(PlaneID id)
	{
		AttachCollider(sColliderWidth, sColliderHeight, sColliderOffsetX, sColliderOffsetY);
		InitializeMembers(id);
		AttachSprite();
		GetSprite()->Initialize(mPlaneWidth, mPlaneHeight, mSpritePath);
		RegisterToLevelManager();
		SetPosition(mSpawnPositionX, mSpawnPositionY);
	}

	void Plane::Respawn(DWORD currentTime)
	{
		SetVelocity(GetSpeed(currentTime), 0);
		SetPosition(mSpawnPositionX, mSpawnPositionY + getRangedRandom(sMinSpawnPositionVarianceY, sMaxSpawnPositionVarianceY) - sMaxSpawnPositionVarianceY / 2);
	}

	void Plane::Update(DWORD milliseconds)
	{
		GameObject::Update(milliseconds);
	}

	void Plane::InCollision(Collider& otherCollider)
	{
		if (otherCollider.GetColliderTag() == Collider::ColliderTag::Player_B_Bullet && mCollider->GetColliderTag() == Collider::ColliderTag::Player_A_Plane)
		{
			ShotDown();
		}
		else if (otherCollider.GetColliderTag() == Collider::ColliderTag::Player_A_Bullet && mCollider->GetColliderTag() == Collider::ColliderTag::Player_B_Plane)
		{
			ShotDown();
		}
	}

	Plane::PlaneID Plane::GetPlaneID()
	{
		return mPlaneID;
	}

	void Plane::InitializeMembers(PlaneID planeID)
	{
		mPlaneID = planeID;

		switch (mPlaneID)
		{
		case PlaneID::PlaneA_1:
			mSpawnPositionX = sSpawnPositionA1X;
			mSpawnPositionY = sSpawnPositionA1Y;
			mPlaneWidth = sWidthPlaneA;
			mPlaneHeight = sHeightPlaneA;
			mSpritePath = sSpritePathPlaneA;
			GetCollider()->SetColliderTag(Collider::ColliderTag::Player_A_Plane);
			break;
		case PlaneID::PlaneA_2:
			mSpawnPositionX = sSpawnPositionA2X;
			mSpawnPositionY = sSpawnPositionA2Y;
			mPlaneWidth = sWidthPlaneA;
			mPlaneHeight = sHeightPlaneA;
			mSpritePath = sSpritePathPlaneA;
			GetCollider()->SetColliderTag(Collider::ColliderTag::Player_A_Plane);
			break;
		case PlaneID::PlaneB_1:
			mSpawnPositionX = sSpawnPositionB1X;
			mSpawnPositionY = sSpawnPositionB1Y;
			mPlaneWidth = sWidthPlaneB;
			mPlaneHeight = sHeightPlaneB;
			mSpritePath = sSpritePathPlaneB;
			GetCollider()->SetColliderTag(Collider::ColliderTag::Player_B_Plane);
			break;
		case PlaneID::PlaneB_2:
			mSpawnPositionX = sSpawnPositionB2X;
			mSpawnPositionY = sSpawnPositionB2Y;
			mPlaneWidth = sWidthPlaneB;
			mPlaneHeight = sHeightPlaneB;
			mSpritePath = sSpritePathPlaneB;
			GetCollider()->SetColliderTag(Collider::ColliderTag::Player_B_Plane);
			break;
		}
	}

	void Plane::RegisterToLevelManager()
	{
		GameManager* levelManager = GameManager::GetInstance();
		assert(levelManager != nullptr);
		levelManager->RegisterPlane(*this);
	}

	void Plane::ResetPlane()
	{
		SetPosition(mSpawnPositionX, mSpawnPositionY);
		SetVelocity(0, 0);
	}

	void Plane::ShotDown()
	{
		SetVelocity(0, 0);
		SetPosition(mSpawnPositionX, mSpawnPositionY);
	}

	float_t Plane::GetSpeed(DWORD currentTime)
	{
		// Estimate base speed based on the current time
		float_t timeRatio = currentTime / sTimeForMaximumSpeed;
		if (timeRatio > 1.0f)
		{
			timeRatio = 1.0f;
		}
		float_t speed = sMinimumSpeed + timeRatio * (sMaximumSpeed - sMinimumSpeed);
		// Add deflection to the base speed
		speed = speed + getRangedRandom(sMinimumSpeedVariance, sMaximumSpeedVariance) - sMaximumSpeedVariance / 2;
		// Return the speed based on the plane team
		if (mPlaneID == PlaneID::PlaneA_1 || mPlaneID == PlaneID::PlaneA_2)
		{
			return speed;
		}
		else
		{
			return -speed;
		}
	}

	bool Plane::RequiresRespawn()
	{
		bool isReadyForRespawn = false;
		if (mPosition.x <= sSpawnPositionA1X || mPosition.x >= sSpawnPositionB1X)
		{
			isReadyForRespawn = true;
		}
		return isReadyForRespawn;
	}
}