#include "Platform.h"

namespace ArkanoidGame
{
	Platform::Platform(float x, float y, float w, float h, float s)
		: GameObject(x, y, w, h), speed(s), isMovingLeft(false), isMovingRight(false)
	{
		shape.setSize(sf::Vector2f(size.x, size.y));
		shape.setPosition(position);
		shape.setFillColor(sf::Color::Blue);
		shape.setOrigin(size.x / 2, size.y / 2);
	}

	sf::FloatRect Platform::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	void Platform::setMovingLeft(bool moving)
	{
		isMovingLeft = moving;
	}

	void Platform::setMovingRight(bool moving)
	{
		isMovingRight = moving;
	}

	void Platform::update(float timeDelta)
	{
		float deltaX = 0.0f;
		
		if (isMovingLeft)
		{
			deltaX = -speed * timeDelta;
		}
		else if (isMovingRight)
		{
			deltaX = speed * timeDelta;
		}

		// Update position
		position.x += deltaX;

		// Keep platform within screen bounds
		if (position.x - size.x / 2 < 0)
		{
			position.x = size.x / 2;
		}
		else if (position.x + size.x / 2 > SCREEN_WIDTH)
		{
			position.x = SCREEN_WIDTH - size.x / 2;
		}

		// Update shape position
		shape.setPosition(position);
	}

	void Platform::draw(sf::RenderWindow& window) const
	{
		window.draw(shape);
	}

	void Platform::setWidth(float newWidth)
	{
		size.x = newWidth;
		shape.setSize(sf::Vector2f(size.x, size.y));
		shape.setOrigin(size.x / 2, size.y / 2);
		
		// Ensure platform stays within bounds
		if (position.x - size.x / 2 < 0)
		{
			position.x = size.x / 2;
		}
		else if (position.x + size.x / 2 > SCREEN_WIDTH)
		{
			position.x = SCREEN_WIDTH - size.x / 2;
		}
		
		shape.setPosition(position);
	}

	void Platform::setVisualEffect(bool hasEffect)
	{
		if (hasEffect)
		{
			shape.setFillColor(sf::Color::Magenta); // Purple when effect is active
		}
		else
		{
			shape.setFillColor(sf::Color::Blue); // Normal blue color
		}
	}
}
