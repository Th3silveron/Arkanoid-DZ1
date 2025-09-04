#include "GameObject.h"

namespace ArkanoidGame
{
	GameObject::GameObject(float x, float y, float width, float height)
		: position(x, y), size(width, height)
	{
	}

	sf::FloatRect GameObject::getBounds() const
	{
		return sf::FloatRect(position.x, position.y, size.x, size.y);
	}

	void GameObject::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void GameObject::setPosition(const sf::Vector2f& pos)
	{
		position = pos;
	}

	void GameObject::setSize(float width, float height)
	{
		size.x = width;
		size.y = height;
	}

	bool GameObject::checkCollision(const sf::FloatRect& otherBounds) const
	{
		return getBounds().intersects(otherBounds);
	}
}
