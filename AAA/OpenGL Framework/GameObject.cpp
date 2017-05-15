#include "GameObject.h"


namespace Engine
{
	GameObject::GameObject() : mCollider(nullptr), mSprite(nullptr), mRotation(0)
	{
		SetPosition(0, 0);
		SetVelocity(0, 0);
		GameObjectManager::GetInstance()->Register(*this);
	}

	GameObject::~GameObject()
	{
		delete mSprite;
		delete mCollider;
		GameObjectManager::GetInstance()->Unregister(*this);
	}

	void GameObject::SetPosition(float_t x, float_t y)
	{
		mPosition.x = x;
		mPosition.y = y;
	}

	const Coord2D& GameObject::GetPosition() const
	{
		return mPosition;
	}

	void GameObject::SetVelocity(float_t x, float_t y)
	{
		mVelocity.x = x;
		mVelocity.y = y;
	}

	const Coord2D& GameObject::GetVelocity() const
	{
		return mVelocity;
	}

	void GameObject::SetRotation(float_t rotation)
	{
		mRotation = rotation;
	}

	const float_t& GameObject::GetRotation() const
	{
		return mRotation;
	}

	void GameObject::SetCollider(Collider& collider)
	{
		delete mCollider;
		mCollider = &collider;
		mCollider->SetOwner(*this);
	}
	
	Collider* GameObject::GetCollider()
	{
		return mCollider;
	}

	void GameObject::SetSprite(Sprite& sprite)
	{
		delete mSprite;
		mSprite = &sprite;
		mSprite->SetOwner(*this);
	}

	Sprite* GameObject::GetSprite()
	{
		return mSprite;
	}
	
	void GameObject::AttachSprite()
	{
		delete mSprite;
		mSprite = new Sprite();
		mSprite->SetOwner(*this);
	}

	void GameObject::AttachCollider(std::uint32_t width, std::uint32_t height, float_t offsetX, float_t offsetY)
	{
		delete mCollider;
		mCollider = new Collider(width, height, offsetX, offsetY);
		mCollider->SetOwner(*this);
	}

	void GameObject::Update(DWORD milliseconds)
	{
		UpdatePosition(milliseconds);
		if (mSprite)
		{
			mSprite->Update(milliseconds);
		}
	}

	void GameObject::InCollision(Collider& otherCollider)
	{
		otherCollider;
	}

	void GameObject::UpdatePosition(DWORD milliseconds)
	{
		if (mVelocity.x != 0 || mVelocity.y != 0)
		{
			float_t changeInX = mVelocity.x * milliseconds / 1000.0f;
			float_t changeInY = mVelocity.y * milliseconds / 1000.0f;

			mPosition.x += changeInX;
			mPosition.y += changeInY;
		}
	}
}
