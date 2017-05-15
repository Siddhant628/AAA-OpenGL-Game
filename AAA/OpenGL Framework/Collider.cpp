#include "Collider.h"
#include "CollisionManager.h"
#include "baseTypes.h"
#include "GameObject.h"

namespace Engine
{
	Collider::~Collider()
	{
		CollisionManager::GetInstance()->Unregister(*this);
	}

	void Collider::SetDimensions(uint32_t width, uint32_t height)
	{
		mWidth = width;
		mHeight = height;
	}

	void Collider::SetOffset(float_t offsetX, float_t offsetY)
	{
		mOffsetX = offsetX;
		mOffsetY = offsetY;
	}

	void Collider::SetOwner(GameObject& object)
	{
		mOwnerObject = &object;
	}

	GameObject* Collider::GetOwner()
	{
		return mOwnerObject;
	}

	void Collider::SetColliderTag(Collider::ColliderTag tag)
	{
		mColliderTag = tag;
	}

	Collider::ColliderTag Collider::GetColliderTag()
	{
		return mColliderTag;
	}

	Collider::Collider(std::uint32_t width, std::uint32_t height, float_t offsetX, float_t offsetY) : mWidth(width), mHeight(height), mOffsetX(offsetX), mOffsetY(offsetY), mColliderTag(ColliderTag::Default)
	{
		CollisionManager::GetInstance()->Register(*this);
	}

	bool Collider::OnCollision(Collider& other)
	{
		if (this != &other)
		{
			Coord2D thisPositon = GetOwner()->GetPosition();
			Coord2D otherPosition = other.GetOwner()->GetPosition();

			float_t thisLeft = thisPositon.x + mOffsetX;
			float_t thisRight = thisLeft + mWidth;
			float_t thisBottom = thisPositon.y + mOffsetY;
			float_t thisTop = thisBottom + mHeight;

			float_t otherLeft = otherPosition.x + other.mOffsetX;
			float_t otherRight = otherLeft + other.mWidth;
			float_t otherBottom = otherPosition.y + other.mOffsetY;
			float_t otherTop = otherBottom + other.mHeight;

			if (thisLeft < otherRight && thisRight > otherLeft && thisTop > otherBottom && thisBottom < otherTop)
			{
				return true;
			}
		}
		return false;
	}
}
