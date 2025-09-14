#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	/**
	 * @brief Base class for all game objects
	 * 
	 * Provides common interface for game objects including
	 * position, bounds, rendering, and update functionality.
	 */
	class GameObject
	{
	protected:
		sf::Vector2f position;
		sf::Vector2f size;
		bool isActive = true;

	public:
		GameObject(float x, float y, float width, float height);
		virtual ~GameObject() = default;

		// Getters
		sf::Vector2f getPosition() const { return position; }
		sf::Vector2f getSize() const { return size; }
		virtual sf::FloatRect getBounds() const;
		bool getIsActive() const { return isActive; }

		// Setters
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& pos);
		void setSize(float width, float height);
		void setActive(bool active) { isActive = active; }

		// Virtual methods to be overridden by derived classes
		virtual void update(float timeDelta) {}
		virtual void draw(sf::RenderWindow& window) const = 0;
		virtual bool checkCollision(const sf::FloatRect& otherBounds) const;
	};
}
