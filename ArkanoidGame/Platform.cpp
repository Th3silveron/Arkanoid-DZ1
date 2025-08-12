#include "Platform.h"

namespace ArkanoidGame
{
	Platform::Platform(float x, float y, float w, float h, float s)
		: speed(s), positionX(x), positionY(y), width(w), height(h), isMovingLeft(false), isMovingRight(false)
	{
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(positionX, positionY);
		shape.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(2.0f);
	}

	sf::FloatRect Platform::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	sf::Vector2f Platform::getPosition() const
	{
		return shape.getPosition();
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
		float movement = 0.0f;
		
		if (isMovingLeft)
		{
			movement -= speed * timeDelta;
		}
		if (isMovingRight)
		{
			movement += speed * timeDelta;
		}

		// Update position
		positionX += movement;
		
		// Keep platform within screen bounds
		if (positionX < 0)
		{
			positionX = 0;
		}
		else if (positionX + width > SCREEN_WIDTH)
		{
			positionX = SCREEN_WIDTH - width;
		}

		shape.setPosition(positionX, positionY);
	}

	void Platform::draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	bool Platform::checkCollision(const sf::FloatRect& otherBounds) const
	{
		return shape.getGlobalBounds().intersects(otherBounds);
	}
}
