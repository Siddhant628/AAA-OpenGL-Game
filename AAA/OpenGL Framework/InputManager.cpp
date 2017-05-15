#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include "InputManager.h"
#include "openGLFramework.h"
#include "Turret.h"
#include "Bullet.h"
#include "GameManager.h"

#define DISABLE_ROTATE_ON_FIRE 0

namespace AAA
{
	InputManager* InputManager::sInstance = nullptr;

	InputManager::InputManager() : mTurretPlayer1(nullptr), mTurretPlayer2(nullptr)
	{

	}

	InputManager *InputManager::CreateInstance()
	{
		if (!sInstance)
		{
			sInstance = new InputManager();
		}
		return sInstance;
	}

	InputManager* InputManager::GetInstance()
	{
		return sInstance;
	}

	void InputManager::Initialize()
	{

	}

	void InputManager::Update(DWORD milliseconds)
	{
		HandleInputAppication();
		if (GameManager::GetInstance()->IsGameRunning())
		{
			HandlePlayerAInput(g_keys, milliseconds);
			HandlePlayerBInput(g_keys, milliseconds);
		}
	}

	void InputManager::Shutdown()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	void InputManager::AddPlayer(Turret& turret)
	{
		if (!mTurretPlayer1)
		{
			mTurretPlayer1 = &turret;
		}
		else if (!mTurretPlayer2)
		{
			mTurretPlayer2 = &turret;
		}
	}

	void InputManager::HandleInputAppication()
	{
		// Close the application.
		if (g_keys->keyDown[VK_ESCAPE])
		{
			TerminateApplication(g_window);
		}
		// Toggle full screen.
		if (g_keys->keyDown[VK_F1])
		{
			ToggleFullscreen(g_window);
		}
		if (g_keys->keyDown['R'])
		{
			if (GameManager::GetInstance() != nullptr)
			{
				GameManager::GetInstance()->RestartGame();
			}
		}
	}

	void InputManager::HandlePlayerAInput(Keys* keys, DWORD milliseconds)
	{
		float_t turretRotation = mTurretPlayer1->GetRotation();
		// Fire bullet
		if (keys->keyDown['W'])
		{
			Bullet::Fire(turretRotation, Bullet::BulletOwner::PlayerA);
		}
		// Rotate turret left
#if DISABLE_ROTATE_ON_FIRE
		else
		{
#endif
			if (keys->keyDown['A'])
			{
				if (turretRotation < Turret::sRightRotationEnd)
				{
					mTurretPlayer1->SetRotation(turretRotation + Turret::sTurretRotationSpeed * milliseconds / 1000);
				}
			}
			// Rotate turret right
			if (keys->keyDown['D'])
			{
				if (turretRotation > Turret::sLeftRotationEnd)
				{
					mTurretPlayer1->SetRotation(turretRotation - Turret::sTurretRotationSpeed * milliseconds / 1000);
				}
			}
#if DISABLE_ROTATE_ON_FIRE
			}
#endif
		}

	void InputManager::HandlePlayerBInput(Keys* keys, DWORD milliseconds)
	{
		float_t turretRotation = mTurretPlayer2->GetRotation();
		// Fire bullet
		if (keys->keyDown[VK_NUMPAD8])
		{
			Bullet::Fire(turretRotation, Bullet::BulletOwner::PlayerB);
		}
#if DISABLE_ROTATE_ON_FIRE
		else
		{
#endif
			// Rotate turret left
			if (keys->keyDown[VK_NUMPAD4])
			{
				if (turretRotation < Turret::sRightRotationEnd)
				{
					mTurretPlayer2->SetRotation(turretRotation + Turret::sTurretRotationSpeed * milliseconds / 1000);
				}
			}
			// Rotate turret right
			if (keys->keyDown[VK_NUMPAD6])
			{
				if (turretRotation > Turret::sLeftRotationEnd)
				{
					mTurretPlayer2->SetRotation(turretRotation - Turret::sTurretRotationSpeed * milliseconds / 1000);
				}
			}
#if DISABLE_ROTATE_ON_FIRE
			}
#endif
		}
}