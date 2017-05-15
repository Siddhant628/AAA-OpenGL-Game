#pragma once

#include <windows.h>
#include <vector>

namespace Engine
{
	class GameObject;
	class GameObjectManager
	{
	public:
		/**
		* Default destructor.
		*/
		~GameObjectManager() = default;
		/**
		* Create the singleton instance of this class.
		*/
		static GameObjectManager* CreateInstance();
		/**
		* Get the singleton instance.
		*/
		static GameObjectManager* GetInstance();
		/**
		* Initialize this singleton.
		*/
		void Initialize();
		/**
		* Update method for each frame.
		*/
		void Update(DWORD milliseconds);
		/**
		* Register the game object from the game object manager.
		*/
		void Register(GameObject& gameObject);
		/**
		* Unregister the game object from the game object manager.
		*/
		void Unregister(GameObject& gameObject);
		/**
		* Iterate over all the game objects and render their sprites.
		*/
		void Render();
		/**
		* Clear the memory allocated to the singleton.
		*/
		void Shutdown();
	private:
		/**
		* Default constructor.
		*/
		GameObjectManager() = default;

		/**
		* Delete the game objects which were queued for deletion in previous frame.
		*/
		void ClearDeleteQueue();
		/**
		* The singleton instance of the class.
		*/
		static GameObjectManager* sInstance;
		/**
		* The list of game objects present / registered in the game.
		*/
		std::vector<GameObject*> mGameObjects;
		/**
		* The list of game objects queued for deletion in previous frame.
		*/
		std::vector<GameObject*> mDeleteQueue;
	};
}