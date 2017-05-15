#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include "InputManager.h"
InputManagerC* InputManagerC::sInstance = NULL;

InputManagerC *InputManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new InputManagerC();
	return sInstance;
}