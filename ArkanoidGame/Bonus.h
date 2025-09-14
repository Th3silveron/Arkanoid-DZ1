#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

namespace ArkanoidGame
{
	// Forward declarations
	class Platform;
	class Ball;

	/**
	 * @brief Strategy interface for bonus effects
	 * 
	 * Defines the contract for different bonus effects using Strategy pattern
	 */
	class IBonusEffect
	{
	public:
		virtual ~IBonusEffect() = default;
		virtual void applyEffect(Platform& platform, Ball& ball) = 0;
		virtual void removeEffect(Platform& platform, Ball& ball) = 0;
		virtual std::string getEffectName() const = 0;
		virtual float getDuration() const = 0;
		virtual std::unique_ptr<IBonusEffect> clone() const = 0;
	};

	/**
	 * @brief Base Bonus class for Arkanoid game
	 * 
	 * Represents a bonus item that falls down and can be collected by the platform.
	 * Uses Strategy pattern for different effects and Observer pattern for notifications.
	 */
	class Bonus : public GameObject
	{
	protected:
		sf::CircleShape shape;
		std::unique_ptr<IBonusEffect> effect;
		float fallSpeed;
		bool isCollected;
		float timeToLive;

	public:
		Bonus(float x, float y, std::unique_ptr<IBonusEffect> bonusEffect, float speed = 100.0f);
		virtual ~Bonus() = default;

		// Getters
		bool getIsCollected() const { return isCollected; }
		bool isExpired() const { return timeToLive <= 0; }
		IBonusEffect* getEffect() const { return effect.get(); }

		// Override virtual methods
		sf::FloatRect getBounds() const override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) const override;

		// Bonus-specific methods
		void collect();
		void setPosition(float x, float y);

		// Observer pattern - callback for collection
		std::function<void(Bonus*)> onCollected;
	};
}
