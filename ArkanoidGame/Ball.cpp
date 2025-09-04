#include "Ball.h"
#include <random>

namespace ArkanoidGame
{
	Ball::Ball(float x, float y, float r, float s)
		: GameObject(x, y, r * 2, r * 2), radius(r), velocityX(0), velocityY(0), speed(s), isLaunched(false), aimDirection(0.0f), lastCollisionTime(0.0f)
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
			
			// Use aim direction for launch
			float angle = aimDirection * 0.5f; // Limit angle to ±0.5 radians (about ±30 degrees)
			velocityX = speed * sin(angle);
			velocityY = -speed * cos(angle); // Negative for upward movement
		}
	}

	void Ball::update(float timeDelta)
	{
		if (isLaunched)
		{
			// Store previous position for collision detection
			float prevX = position.x;
			float prevY = position.y;
			
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
			// Calculate overlap on each axis
			float overlapLeft = (ballBounds.left + ballBounds.width) - blockBounds.left;
			float overlapRight = (blockBounds.left + blockBounds.width) - ballBounds.left;
			float overlapTop = (ballBounds.top + ballBounds.height) - blockBounds.top;
			float overlapBottom = (blockBounds.top + blockBounds.height) - ballBounds.top;
			
			// Find the minimum overlap to determine collision side
			float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
			
			// Determine collision side and bounce accordingly
			if (minOverlap == overlapLeft)
			{
				// Hit left side of block
				velocityX = -abs(velocityX); // Ensure negative velocity
				position.x = blockBounds.left - radius - 2.0f; // Move ball out with extra margin
			}
			else if (minOverlap == overlapRight)
			{
				// Hit right side of block
				velocityX = abs(velocityX); // Ensure positive velocity
				position.x = blockBounds.left + blockBounds.width + radius + 2.0f; // Move ball out with extra margin
			}
			else if (minOverlap == overlapTop)
			{
				// Hit top side of block
				velocityY = -abs(velocityY); // Ensure negative velocity (upward)
				position.y = blockBounds.top - radius - 2.0f; // Move ball out with extra margin
			}
			else if (minOverlap == overlapBottom)
			{
				// Hit bottom side of block
				velocityY = abs(velocityY); // Ensure positive velocity (downward)
				position.y = blockBounds.top + blockBounds.height + radius + 2.0f; // Move ball out with extra margin
			}
			
			// Update shape position
			shape.setPosition(position.x, position.y);
		}
	}

	void Ball::reset(float x, float y)
	{
		position.x = x;
		position.y = y;
		velocityX = 0;
		velocityY = 0;
		isLaunched = false;
		aimDirection = 0.0f; // Reset aim direction
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

	void Ball::followPlatform(const sf::Vector2f& platformPosition, float platformWidth)
	{
		if (!isLaunched)
		{
			// Position ball on platform center
			position.x = platformPosition.x;
			position.y = platformPosition.y - radius; // Ball sits on top of platform
			shape.setPosition(position.x, position.y);
		}
	}

	void Ball::setAimDirection(float direction)
	{
		// Clamp direction between -1.0 and 1.0
		aimDirection = std::max(-1.0f, std::min(1.0f, direction));
	}
}
