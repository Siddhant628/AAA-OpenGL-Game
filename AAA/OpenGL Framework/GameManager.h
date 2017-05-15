#pragma once

#include <windows.h>
#include <string>
#include <vector>

namespace Engine
{
	class GameObject;
}

namespace AAA
{
	class Plane;
	enum class PlayerEnum
	{
		PlayerA,
		PlayerB
	};

	class GameManager
	{
	public:
		/**
		* Default destructor.
		*/
		~GameManager() = default;

		/* Methods associated with the singleton. */
		/**
		* Create a singleton instance.
		*/
		static GameManager* CreateInstance();
		/**
		* Get the instance of singleton.
		*/
		static GameManager* GetInstance();
		/**
		* Initialize the level.
		*/
		void Initialize();
		/**
		* Update call for each frame.
		*/
		void Update(DWORD milliseconds);
		/**
		* Deallocate memory associated with this level.
		*/
		void Shutdown();

		/* Other methods. */
		/**
		* Register a plane to this game manager.
		*/
		void RegisterPlane(Plane& plane);

		bool IsGameRunning();
		/**
		* Request the game manager to restart the game.
		*/
		void RestartGame();
	private:
		/**
		* Private constructor for singleton.
		*/
		GameManager();

		/* Methods associated with loading of game objects. */
		/**
		* Load the background game object.
		*/
		void LoadBackground();
		/**
		* Load the plane game objects.
		*/
		void LoadPlanes();
		/**
		* Load the bullet game objects.
		*/
		void LoadBullets();
		/**
		* Load the turret game objects.
		*/
		void LoadTurrets();
		/**
		* Load the game objects associated with sprites displaying lives.
		*/
		void LoadLivesSprites();
		/**
		* Loads the sprite associated with the end game screen.
		*/
		void LoadEndGameScreen();


		/* Other methods. */
		/**
		* The level's planes are checked for respawn (re-spawnned if required), and health is decremented if planes cross into enemy territory.
		*/
		void PlanesUpdate(DWORD currentTime);
		/**
		* Decrements the health of the player and checks for lose condition.
		*/
		void DecrementHealth(PlayerEnum playerEnum);
		/**
		* Perform actions associated with level end.
		*/
		void EndGame();

		void ResetLives();

		void ResetPlanes();

		/**
		* Pointer to the singleton.
		*/
		static GameManager* sInstance;
		/**
		* Game objects which represent lives of player A.
		*/
		std::vector<Engine::GameObject*> mLivesPlayerA;
		/**
		* Game objects which represent lives of player B.
		*/
		std::vector<Engine::GameObject*> mLivesPlayerB;
		/**
		* Game objects which represent planes of player A.
		*/
		std::vector<Plane*> mPlanesPlayerA;
		/**
		* Game objects which represent planes of player B.
		*/
		std::vector<Plane*> mPlanesPlayerB;
		/**
		* Iterator associated with the current health object of player A.
		*/
		std::vector<Engine::GameObject*>::iterator mCurrentHealthA;
		/**
		* Iterator associated with the current health object of player B.
		*/
		std::vector<Engine::GameObject*>::iterator mCurrentHealthB;
		/**
		* A pointer to the game object loaded at the end of the game.
		*/
		Engine::GameObject* mEndGameScreen;
		/**
		* Is the game still running.
		*/
		bool mGameIsRunning;
		/**
		* The amount of time passed since the start of the game.
		*/
		DWORD mCurrentTime;

		// Background sprite related variables.
		static const std::string sBackgroundSpritePath;
		// Turret base related variables.
		static const std::string sTurretBaseSpritePath;
		static const float_t sPositionTurretBaseAX;
		static const float_t sPositionTurretBaseAY;
		static const float_t sPositionTurretBaseBX;
		static const float_t sPositionTurretBaseBY;
		static const uint32_t sTurretBaseWidth;
		static const uint32_t sTurretBaseHeight;
		// End game screen related variables.
		static const float_t sEndGamePositionX;
		static const float_t sEndGamePositionY;
		static const uint32_t sEndGameWidth;
		static const uint32_t sEndGameHeight;
		static const std::string sEndGameSprite;
		// Lives related variables.
		static const uint32_t sLivesCount;
		static const uint32_t sLivesWidth;
		static const uint32_t sLivesHeight;
		static const float_t sLivesPositionOffsetY;
		static const float_t sLivesPositionOffsetX;
		static const std::string sLivesSpritePlayerA;
		static const std::string sLivesSpritePlayerB;
	};
}