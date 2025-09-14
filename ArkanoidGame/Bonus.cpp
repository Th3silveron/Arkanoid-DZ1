#include "Bonus.h"
#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Bonus::Bonus(float x, float y, std::unique_ptr<IBonusEffect> bonusEffect, float speed)
		: GameObject(x, y, BONUS_SIZE, BONUS_SIZE), effect(std::move(bonusEffect)), fallSpeed(speed), isCollected(false), timeToLive(10.0f)
	{
		// Create circular shape for bonus
		shape.setRadius(BONUS_RADIUS);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Yellow);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(2.0f);
		shape.setOrigin(BONUS_RADIUS, BONUS_RADIUS); // Center the origin
	}

	sf::FloatRect Bonus::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	void Bonus::update(float timeDelta)
	{
		if (!isActive || isCollected) return;

		// Fall down
		position.y += fallSpeed * timeDelta;
		shape.setPosition(position);

		// Decrease time to live
		timeToLive -= timeDelta;

		// Check if bonus fell off screen
		if (position.y > SCREEN_HEIGHT + 20.0f)
		{
			isActive = false;
		}
	}

	void Bonus::draw(sf::RenderWindow& window) const
	{
		if (isActive && !isCollected)
		{
			window.draw(shape);
		}
	}

	void Bonus::collect()
	{
		if (!isCollected)
		{
			isCollected = true;
			isActive = false;
			
			// Notify observer
			if (onCollected)
			{
				onCollected(this);
			}
		}
	}

	void Bonus::setPosition(float x, float y)
	{
		GameObject::setPosition(x, y);
		shape.setPosition(x, y);
	}
}
