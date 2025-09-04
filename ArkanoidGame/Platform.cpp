#include "Platform.h"

namespace ArkanoidGame
{
	Platform::Platform(float x, float y, float w, float h, float s)
		: speed(s), positionX(x), positionY(y), width(w), height(h), isMovingLeft(false), isMovingRight(false)
	{
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(positionX, positionY);
		shape.setFillColor(sf::Color::Blue);
		shape.setOrigin(width / 2, height / 2);
	}

	sf::FloatRect Platform::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	sf::Vector2f Platform::getPosition() const
	{
		return sf::Vector2f(positionX, positionY);
	}

	float Platform::getWidth() const
	{
		return width;
	}

	float Platform::getHeight() const
	{
		return height;
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
		positionX += deltaX;

		// Keep platform within screen bounds
		if (positionX - width / 2 < 0)
		{
			positionX = width / 2;
		}
		else if (positionX + width / 2 > SCREEN_WIDTH)
		{
			positionX = SCREEN_WIDTH - width / 2;
		}

		// Update shape position
		shape.setPosition(positionX, positionY);
	}

	void Platform::draw(sf::RenderWindow& window) const
	{
		window.draw(shape);
	}

	bool Platform::checkCollision(const sf::FloatRect& otherBounds) const
	{
		return shape.getGlobalBounds().intersects(otherBounds);
	}
}
