#pragma once

#include "baseTypes.h"
#include <string>
#include <windows.h>

namespace Engine
{
	class Sprite
	{
		friend class GameObject;
	public:
		/**
		* Default destructor.
		*/
		~Sprite() = default;
		/**
		* Initialize the sprite with texture file name, width and height.
		*/
		void Initialize(uint32_t width, uint32_t height, const std::string& textureFilePath);
		/**
		* Enable a sprite, so it renders.
		*/
		void Enable();
		/**
		* Disable the sprite, so it doesn't render.
		*/
		void Disable();
		/**
		* Render the sprite.
		*/
		void Render();
		/**
		* Update method for each frame.
		*/
		void Update(DWORD milliseconds);
	protected:
		/**
		* Get the owner game object.
		*/
		GameObject* GetOwner();
		/**
		* Set the owner game object.
		*/
		void SetOwner(GameObject& object);
		/**
		* Default constructor.
		*/
		Sprite();
	private:
		/**
		* The width of this sprite.
		*/
		uint32_t mWidth;
		/**
		* The height of this sprite.
		*/
		uint32_t mHeight;
		/**
		* The texture ID associated with this sprite.
		*/
		uint32_t mSpriteTextureID;
		/**
		* Whether the sprite has been initialized.
		*/
		bool mIsInitialized;
		/**
		* The sprite will render only if it is enabled.
		*/
		bool mIsEnabled;
		/**
		* The game object with which this sprite is associated.
		*/
		GameObject* mOwnerObject;
	};
}