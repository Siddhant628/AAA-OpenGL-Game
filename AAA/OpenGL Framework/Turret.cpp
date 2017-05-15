#include "Turret.h"
#include "InputManager.h"
#include "GameManager.h"

namespace AAA
{
	const float_t Turret::sTurretAPositionX = 127.0f;
	const float_t Turret::sTurretAPositionY = 50.0f;
	const float_t Turret::sTurretBPositionX = 893.0f;
	const float_t Turret::sTurretBPositionY = 50.0f;

	const uint32_t Turret::sTurretWidth = 41;
	const uint32_t Turret::sTurretHeight = 78;

	const float_t Turret::sRotationTurretA = 5.0f;
	const float_t Turret::sRotationTurretB = 45.0f;

	const std::string Turret::sTurretSpritePath = "Sprites/Turret.png";

	const float_t Turret::sTurretRotationSpeed = 30.0f;
	const float_t Turret::sLeftRotationEnd = 5.0f;
	const float_t Turret::sRightRotationEnd = 45.0f;

	Turret::Turret(PlayerEnum turretPlayer)
	{
		InitializeMembers(turretPlayer);
		AttachSprite();
		GetSprite()->Initialize(sTurretWidth, sTurretHeight, sTurretSpritePath);
		InputManager::GetInstance()->AddPlayer(*this);
	}

	void Turret::Update(DWORD milliseconds)
	{
		GameObject::Update(milliseconds);
	}

	void Turret::InitializeMembers(PlayerEnum turretPlayer)
	{
		switch (turretPlayer)
		{
		case PlayerEnum::PlayerA:
			mPosition.x = sTurretAPositionX;
			mPosition.y = sTurretAPositionY;
			mRotation = sRotationTurretA;
			break;
		case PlayerEnum::PlayerB:
			mPosition.x = sTurretBPositionX;
			mPosition.y = sTurretBPositionY;
			mRotation = sRotationTurretB;
			break;
		}
	}
}