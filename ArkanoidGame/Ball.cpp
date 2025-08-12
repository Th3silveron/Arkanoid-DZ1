#include "Ball.h"
#include <cmath>

namespace ArkanoidGame
{
	Ball::Ball(float x, float y, float r, float s)
		: radius(r), positionX(x), positionY(y), velocityX(0.0f), velocityY(0.0f), speed(s), isLaunched(false)
	{
		shape.setRadius(radius);
		shape.setPosition(positionX, positionY);
		shape.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(2.0f);
		shape.setOrigin(radius, radius);
	}

	sf::FloatRect Ball::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	sf::Vector2f Ball::getPosition() const
	{
		return sf::Vector2f(positionX, positionY);
	}

	float Ball::getRadius() const
	{
		return radius;
	}

	bool Ball::getIsLaunched() const
	{
		return isLaunched;
	}

	void Ball::launch()
	{
		if (!isLaunched)
		{
			isLaunched = true;
			// Launch ball upward with some horizontal variation
			velocityX = (rand() % 200 - 100) / 100.0f; // Random direction between -1 and 1
			velocityY = -speed;
			
			// Normalize and scale to speed
			float length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
			velocityX = (velocityX / length) * speed;
			velocityY = (velocityY / length) * speed;
		}
	}

	void Ball::update(float timeDelta)
	{
		if (isLaunched)
		{
			positionX += velocityX * timeDelta;
			positionY += velocityY * timeDelta;
			shape.setPosition(positionX, positionY);
		}
	}

	void Ball::draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void Ball::handleWallCollision()
	{
		// Left and right walls
		if (positionX - radius <= 0)
		{
			positionX = radius;
			velocityX = std::abs(velocityX); // Bounce right
		}
		else if (positionX + radius >= SCREEN_WIDTH)
		{
			positionX = SCREEN_WIDTH - radius;
			velocityX = -std::abs(velocityX); // Bounce left
		}

		// Top wall
		if (positionY - radius <= 0)
		{
			positionY = radius;
			velocityY = std::abs(velocityY); // Bounce down
		}

		shape.setPosition(positionX, positionY);
	}

	void Ball::handlePlatformCollision(const sf::FloatRect& platformBounds)
	{
		sf::FloatRect ballBounds = getBounds();
		
		if (ballBounds.intersects(platformBounds))
		{
			// Calculate collision point and bounce direction
			float ballCenterX = positionX;
			float ballCenterY = positionY;
			float platformCenterX = platformBounds.left + platformBounds.width / 2.0f;
			float platformCenterY = platformBounds.top + platformBounds.height / 2.0f;

			// Determine which side of the platform was hit
			float relativeX = ballCenterX - platformCenterX;
			float relativeY = ballCenterY - platformCenterY;

			// Bounce off platform
			if (std::abs(relativeX) > std::abs(relativeY))
			{
				// Hit from left or right
				velocityX = -velocityX;
			}
			else
			{
				// Hit from top or bottom
				velocityY = -velocityY;
			}

			// Ensure ball moves upward after hitting platform
			if (velocityY > 0)
			{
				velocityY = -std::abs(velocityY);
			}

			// Add some randomness to prevent infinite loops
			velocityX += (rand() % 100 - 50) / 1000.0f;
			velocityY += (rand() % 100 - 50) / 1000.0f;

			// Normalize and scale back to speed
			float length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
			velocityX = (velocityX / length) * speed;
			velocityY = (velocityY / length) * speed;
		}
	}

	void Ball::reset(float x, float y)
	{
		positionX = x;
		positionY = y;
		velocityX = 0.0f;
		velocityY = 0.0f;
		isLaunched = false;
		shape.setPosition(positionX, positionY);
	}

	void Ball::setPosition(float x, float y)
	{
		positionX = x;
		positionY = y;
		shape.setPosition(positionX, positionY);
	}

	void Ball::setVelocity(float vx, float vy)
	{
		velocityX = vx;
		velocityY = vy;
	}
}
