#define GAME_CPP

#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"
#include "random.h"
#include "openGLStuff.h"
#include "game.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

using namespace Engine;

// Declarations
const uint32_t CGame::mScreenWidth = 1024;
const uint32_t CGame::mScreenHeight = 768;
const uint32_t CGame::mBitsPerPixel = 32;

const char8_t CGame::mGameTitle[] = "AAA";
CGame* CGame::sInstance = NULL;

BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->Init();
	return TRUE;						
}

CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}

void CGame::Init()
{
	AAA::InputManager::CreateInstance();
	GameObjectManager::CreateInstance();
	CollisionManager::CreateInstance();
	AAA::GameManager::CreateInstance();


	AAA::InputManager::GetInstance()->Initialize();
	GameObjectManager::GetInstance()->Initialize();
	CollisionManager::GetInstance()->Initialize();
	AAA::GameManager::GetInstance()->Initialize();
}

void CGame::UpdateFrame(DWORD milliseconds)			
{
	AAA::InputManager::GetInstance()->Update(milliseconds);
	GameObjectManager::GetInstance()->Update(milliseconds);
	CollisionManager::GetInstance()->Update(milliseconds);
	AAA::GameManager::GetInstance()->Update(milliseconds);
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	GameObjectManager::GetInstance()->Render();
}

void CGame::Shutdown()
{
	AAA::InputManager::GetInstance()->Shutdown();
	GameObjectManager::GetInstance()->Shutdown();
	CollisionManager::GetInstance()->Shutdown();
	AAA::GameManager::GetInstance()->Shutdown();
}

void CGame::DestroyGame(void)
{

}