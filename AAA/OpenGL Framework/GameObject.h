#pragma once

#include "baseTypes.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObjectManager.h"

namespace Engine
{
	class GameObject
	{
	public:
		/**
		* Default constructor.
		*/
		GameObject();
		/**
		* Delete the collider and sprite associated with this game object.
		*/
		virtual ~GameObject();
		/**
		* Set the position of this game object.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		*/
		void SetPosition(float_t x, float_t y);
		/**
		* Get the position of this game object.
		*/
		const Coord2D& GetPosition() const;
		/**
		* Set the velocity of this game object.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		*/
		void SetVelocity(float_t x, float_t y);
		/**
		* Get the velocity of this game object.
		*/
		const Coord2D& GetVelocity() const;
		/**
		* Set the rotation of this object in degrees.
		*/
		void SetRotation(float_t rotation);
		/**
		* Get the rotation of this game object in degrees.
		*/
		const float_t& GetRotation() const;
		/**
		* Set the collider of this object.
		*/
		void SetCollider(Collider& collider);
		/**
		* Get the collider of this object.
		*/
		Collider* GetCollider();
		/**
		* Set the sprite of this object.
		*/
		void SetSprite(Sprite& sprite);
		/**
		* Get the sprite of this object.
		*/
		Sprite* GetSprite();
		/**
		* Attach a new sprite to this game object. (Removes the preexisting one)
		*/
		void AttachSprite();
		/**
		* Attach a new collider to this game object. (Removes the preexisting one)
		*/
		void AttachCollider(std::uint32_t width, std::uint32_t height, float_t offsetX, float_t offsetY);
		/**
		* Update method for each frame.
		*/
		virtual void Update(DWORD milliseconds);
		/**
		* The method which is called for this game object when it collides with another game object.
		*/
		virtual void InCollision(Collider& otherCollider);
	protected:
		/**
		* Update the position of this game object based on its current position.
		*/
		void UpdatePosition(DWORD milliseconds);
		/* Properties */
		/**
		* The position of this game object.
		*/
		Coord2D mPosition;
		/**
		* The velocity of this game object.
		*/
		Coord2D mVelocity;
		/**
		* The rotation of the game object.
		*/
		float_t mRotation;
		/* Components */
		/**
		* The collider associated with this game object.
		*/
		Collider* mCollider;
		/**
		* The sprite associated with this game object.
		*/
		Sprite* mSprite;
	};
}