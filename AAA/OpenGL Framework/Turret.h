#pragma once

#include "GameObject.h"
#include <string>

namespace AAA
{
	enum class PlayerEnum;
	class Turret final : public Engine::GameObject
	{
	public:
		/**
		* Initializes the members of the turret based on the player it belongs to.
		*/
		Turret(PlayerEnum turretPlayer);
		/**
		* Default destructor.
		*/
		~Turret() = default;
		/**
		* Update for each frame.
		*/
		virtual void Update(DWORD milliseconds) override;
	private:
		/**
		* Initializes the members of object.
		*/
		void InitializeMembers(PlayerEnum turretPlayer);

		// The positions of turrets on the display.
		static const float_t sTurretAPositionX;
		static const float_t sTurretAPositionY;
		static const float_t sTurretBPositionX;
		static const float_t sTurretBPositionY;
		// The dimension in pixels where the turret should be rendered.
		static const uint32_t sTurretWidth;
		static const uint32_t sTurretHeight;
		// Default rotations of turrets.
		static const float sRotationTurretA;
		static const float sRotationTurretB;
		// The file path of the turret sprite.
		static const std::string sTurretSpritePath;
	public:
		// Turret rotation data.
		static const float_t sTurretRotationSpeed;
		static const float_t sLeftRotationEnd;
		static const float_t sRightRotationEnd;
	};
}