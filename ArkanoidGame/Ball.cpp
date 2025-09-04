#include "Ball.h"
#include <random>

namespace ArkanoidGame
{
	Ball::Ball(float x, float y, float r, float s)
		: GameObject(x, y, r * 2, r * 2), radius(r), velocityX(0), velocityY(0), speed(s), isLaunched(false)
	{
		shape.setRadius(radius);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::White);
		shape.setOrigin(radius, radius);
	}

	sf::FloatRect Ball::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	sf::Vector2f Ball::getPosition() const
	{
		return position;
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
			
			// Random initial direction (upward with slight randomness)
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> angleDist(-0.3f, 0.3f);
			
			float angle = angleDist(gen);
			velocityX = speed * sin(angle);
			velocityY = -speed * cos(angle); // Negative for upward movement
		}
	}

	void Ball::update(float timeDelta)
	{
		if (isLaunched)
		{
			// Update position
			position.x += velocityX * timeDelta;
			position.y += velocityY * timeDelta;

			// Handle wall collisions
			handleWallCollision();

			// Update shape position
			shape.setPosition(position.x, position.y);
		}
	}

	void Ball::draw(sf::RenderWindow& window) const
	{
		window.draw(shape);
	}

	void Ball::handleWallCollision()
	{
		// Left and right walls
		if (position.x - radius <= 0)
		{
			position.x = radius;
			velocityX = -velocityX;
		}
		else if (position.x + radius >= SCREEN_WIDTH)
		{
			position.x = SCREEN_WIDTH - radius;
			velocityX = -velocityX;
		}

		// Top wall
		if (position.y - radius <= 0)
		{
			position.y = radius;
			velocityY = -velocityY;
		}
	}

	void Ball::handlePlatformCollision(const sf::FloatRect& platformBounds)
	{
		sf::FloatRect ballBounds = getBounds();
		
		if (ballBounds.intersects(platformBounds))
		{
			// Bounce the ball upward
			velocityY = -abs(velocityY);
			
			// Adjust X velocity based on where the ball hits the platform
			float platformCenterX = platformBounds.left + platformBounds.width / 2;
			float hitPosition = position.x - platformCenterX;
			float normalizedHit = hitPosition / (platformBounds.width / 2);
			
			// Add some horizontal velocity based on hit position
			velocityX += normalizedHit * speed * 0.5f;
			
			// Ensure ball doesn't get stuck inside platform
			position.y = platformBounds.top - radius;
		}
	}

	void Ball::handleBlockCollision(const sf::FloatRect& blockBounds)
	{
		sf::FloatRect ballBounds = getBounds();
		
		if (ballBounds.intersects(blockBounds))
		{
			// Calculate collision side
			float ballCenterX = position.x;
			float ballCenterY = position.y;
			float blockCenterX = blockBounds.left + blockBounds.width / 2;
			float blockCenterY = blockBounds.top + blockBounds.height / 2;
			
			float deltaX = ballCenterX - blockCenterX;
			float deltaY = ballCenterY - blockCenterY;
			
			// Determine which side was hit
			if (abs(deltaX) / blockBounds.width > abs(deltaY) / blockBounds.height)
			{
				// Hit left or right side
				velocityX = -velocityX;
			}
			else
			{
				// Hit top or bottom side
				velocityY = -velocityY;
			}
			
			// Move ball out of block to prevent getting stuck
			if (abs(deltaX) / blockBounds.width > abs(deltaY) / blockBounds.height)
			{
				if (deltaX > 0)
					position.x = blockBounds.left + blockBounds.width + radius;
				else
					position.x = blockBounds.left - radius;
			}
			else
			{
				if (deltaY > 0)
					position.y = blockBounds.top + blockBounds.height + radius;
				else
					position.y = blockBounds.top - radius;
			}
		}
	}

	void Ball::reset(float x, float y)
	{
		position.x = x;
		position.y = y;
		velocityX = 0;
		velocityY = 0;
		isLaunched = false;
		shape.setPosition(x, y);
	}

	void Ball::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
		shape.setPosition(x, y);
	}

	void Ball::setVelocity(float vx, float vy)
	{
		velocityX = vx;
		velocityY = vy;
	}
}
