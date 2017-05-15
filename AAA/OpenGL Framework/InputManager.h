#pragma once

#include <windows.h>
#include "openGLFramework.h"

namespace AAA
{
	class Turret;

	class InputManager
	{
		friend class Turret;
	public:
		/**
		* Default destructor.
		*/
		~InputManager() = default;
		/**
		* Create the singleton instance of this class.
		*/
		static InputManager *CreateInstance();
		/**
		* Get the singleton instance.
		*/
		static InputManager *GetInstance();
		/**
		* Initialize this singleton.
		*/
		void Initialize();
		/**
		* Update method for each frame.
		*/
		void Update(DWORD milliseconds);
		/**
		* Clear the memory allocated to the singleton.
		*/
		void Shutdown();
	private:
		/**
		* Default constructor.
		*/
		InputManager();
		/**
		* Register player game object (turret) to the Input Manager.
		*/
		void AddPlayer(Turret& turret);
		/**
		* Handle the input associated with this application.
		*/
		void HandleInputAppication();
		/**
		* Handle the input associated with the player A.
		*/
		void HandlePlayerAInput(Keys* keys, DWORD milliseconds);
		/**
		* Handle the input associated with the player B.
		*/
		void HandlePlayerBInput(Keys* keys, DWORD milliseconds);
		/**
		* The singleton instance of the class.
		*/
		static InputManager *sInstance;
		/**
		* Pointer to the player 1 game object.
		*/
		Turret* mTurretPlayer1;
		/**
		* Pointer to the player 2 game object.
		*/
		Turret* mTurretPlayer2;
	};
}