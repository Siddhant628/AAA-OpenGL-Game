#pragma once
#include "GameObject.h"

class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void Init();
	void Shutdown();
	static const uint32_t mScreenWidth;
	static const uint32_t mScreenHeight;
	static const uint32_t mBitsPerPixel;
private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	CGame(){};
};