#include "Sprite.h"
#include "SOIL.h"
#include "glut.h"
#include "GameObject.h"

namespace Engine
{
	Sprite::Sprite() : mWidth(0), mHeight(0), mIsInitialized(false), mOwnerObject(nullptr), mIsEnabled(true)
	{

	}

	void Sprite::Enable()
	{
		mIsEnabled = true;
	}

	void Sprite::Disable()
	{
		mIsEnabled = false;
	}

	void Sprite::Initialize(uint32_t width, uint32_t height, const std::string& textureFilePath)
	{
		const char8_t* filePath = textureFilePath.c_str();
		mWidth = width;
		mHeight = height;
		mSpriteTextureID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		mIsInitialized = true;
	}

	void Sprite::Render()
	{
		if (mIsInitialized && mIsEnabled)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, mSpriteTextureID);

			glPushMatrix();
			
			const Coord2D& position = GetOwner()->GetPosition();
			glTranslatef(position.x, position.y, 0.0f);
			glRotatef(GetOwner()->GetRotation(), 0.0f, 0.0f, 1.0f);
			glTranslatef(-position.x, -position.y, 0.0f);


			// Initiate drawing
			glBegin(GL_QUADS);
			glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
			// Top Left
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(position.x, position.y + mHeight, 1);
			// Bottom Left
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(position.x, position.y, 1);
			// Bottom Right
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(position.x + mWidth, position.y, 1);
			// Top Right
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(position.x + mWidth, position.y + mHeight, 1);
			//End Drawing
			glEnd();

			glPopMatrix();
		}
	}

	void Sprite::Update(DWORD milliseconds)
	{
		milliseconds;
	}

	GameObject* Sprite::GetOwner()
	{
		return mOwnerObject;
	}
	
	void Sprite::SetOwner(GameObject& object)
	{
		mOwnerObject = &object;
	}
}