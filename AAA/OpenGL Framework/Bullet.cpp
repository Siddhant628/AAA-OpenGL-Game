#include "Bullet.h"
#include "game.h"
#include "Collider.h"
#include "Plane.h"

#include <math.h>

using namespace Engine;

namespace AAA
{
	const float_t Bullet::sSpawnPositionPlayerAX = 124.0f;
	const float_t Bullet::sSpawnPositionPlayerAY = 47.0f;
	const float_t Bullet::sSpawnPositionPlayerBX = 890.0f;
	const float_t Bullet::sSpawnPositionPlayerBY = 47.0f;

	const float_t Bullet::sColliderOffsetX = 0;
	const float_t Bullet::sColliderOffsetY = 0;
	const uint32_t Bullet::sColliderWidth = 6;
	const uint32_t Bullet::sColliderHeight = 6;

	const uint32_t Bullet::sBulletWidth = 6;
	const uint32_t Bullet::sBulletHeight = 6;
	const uint32_t Bullet::sMaxBulletCount = 3;
	const float_t Bullet::sBulletSpeed = 520.0f;
	const float_t Bullet::sFiringAngleOffset = 65.0f;
	const DWORD Bullet::sBulletReloadTime = 1000;
	const double Bullet::sPI = 3.14159265;

	const std::string Bullet::sBulletSpritePath = "Sprites/Bullet.png";

	std::vector<Bullet*> Bullet::sPlayerABullets;
	std::vector<Bullet*> Bullet::sPlayerBBullets;
	bool Bullet::sRequiresReloadA = false;
	bool Bullet::sRequiresReloadB = false;
	DWORD Bullet::sTimeSpentReloadingA = 0;
	DWORD Bullet::sTimeSpentReloadingB = 0;
	

	Bullet::Bullet(BulletOwner owner) : mCanBeFired(true)
	{
		AttachCollider(sColliderWidth, sColliderHeight, sColliderOffsetX, sColliderOffsetY);
		InitializeMembers(owner);
		AttachSprite();
		GetSprite()->Initialize(sBulletWidth, sBulletHeight, sBulletSpritePath);
	}

	void Bullet::Update(DWORD milliseconds)
	{
		GameObject::Update(milliseconds);
		CheckForCanBeFired();
		Reload(milliseconds);
	}

	void Bullet::Fire(float_t angle, BulletOwner owner)
	{
		if (owner == BulletOwner::PlayerA)
		{
			auto it = sPlayerABullets.begin();
			auto end = sPlayerABullets.end();
			if (!sRequiresReloadA)
			{
				for (; it != end; ++it)
				{
					if ((*it)->mCanBeFired)
					{
						FireBullet(angle, **it);
						sRequiresReloadA = true;
						break;
					}
				}
			}
		}
		else if(owner == BulletOwner::PlayerB)
		{
			auto it = sPlayerBBullets.begin();
			auto end = sPlayerBBullets.end();
			if (!sRequiresReloadB)
			{
				for (; it != end; ++it)
				{
					if ((*it)->mCanBeFired)
					{
						FireBullet(angle, **it);
						sRequiresReloadB = true;
						break;
					}
				}
			}
		}
	}

	void Bullet::InCollision(Collider& otherCollider)
	{
		if (mOwnerPlayer == BulletOwner::PlayerB && otherCollider.GetColliderTag() == Collider::ColliderTag::Player_A_Plane)
		{
			ResetBullet();
		}
		else if (mOwnerPlayer == BulletOwner::PlayerA && otherCollider.GetColliderTag() == Collider::ColliderTag::Player_B_Plane)
		{
			ResetBullet();
		}
	}

	void Bullet::FireBullet(float_t angle, Bullet & bullet)
	{
		bullet.mCanBeFired = false;
		angle += sFiringAngleOffset;
		bullet.SetVelocity(sBulletSpeed * static_cast<float_t>(cos(angle * sPI / 180)), sBulletSpeed * static_cast<float_t>(sin(angle * sPI / 180)));
	}

	void Bullet::Reload(DWORD milliseconds)
	{
		if (sRequiresReloadA)
		{
			uint32_t count = sPlayerABullets.size();
			sTimeSpentReloadingA += milliseconds;
			if (sTimeSpentReloadingA / (DWORD)(count) >= sBulletReloadTime)
			{
				sTimeSpentReloadingA = 0;
				sRequiresReloadA = false;
			}
		}
		if (sRequiresReloadB)
		{
			uint32_t count = sPlayerBBullets.size();
			sTimeSpentReloadingB += milliseconds;
			if (sTimeSpentReloadingB / (DWORD)(count) >= sBulletReloadTime)
			{
				sTimeSpentReloadingB = 0;
				sRequiresReloadB = false;
			}
		}
	}

	void Bullet::ResetBullet()
	{
		mCanBeFired = true;
		SetVelocity(0, 0);
		SetPosition(mSpawnPositionX, mSpawnPositionY);
	}

	void Bullet::InitializeMembers(BulletOwner owner)
	{
		switch (owner)
		{
		case Bullet::BulletOwner::PlayerA:
			mOwnerPlayer = BulletOwner::PlayerA;
			mSpawnPositionX = sSpawnPositionPlayerAX;
			mPosition.x = mSpawnPositionX;
			mSpawnPositionY = sSpawnPositionPlayerAY;
			mPosition.y = mSpawnPositionY;
			sPlayerABullets.push_back(this);
			GetCollider()->SetColliderTag(Collider::ColliderTag::Player_A_Bullet);
			break;
		case Bullet::BulletOwner::PlayerB:
			mOwnerPlayer = BulletOwner::PlayerB;
			mSpawnPositionX = sSpawnPositionPlayerBX;
			mPosition.x = mSpawnPositionX;
			mSpawnPositionY = sSpawnPositionPlayerBY;
			mPosition.y = mSpawnPositionY;
			sPlayerBBullets.push_back(this);
			GetCollider()->SetColliderTag(Collider::ColliderTag::Player_B_Bullet);
			break;
		default:
			break;
		}
	}

	void Bullet::CheckForCanBeFired()
	{
		if (!mCanBeFired)
		{
			if (mPosition.y > CGame::mScreenHeight)
			{
				ResetBullet();
			}
		}
	}
}