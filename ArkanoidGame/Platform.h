#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

namespace ArkanoidGame
{
	/**
	 * @brief Player-controlled platform class for Arkanoid game
	 * 
	 * The platform is a rectangle that can move left and right
	 * at the bottom of the screen. It's controlled by arrow keys
	 * and is used to bounce the ball back into play.
	 */
	class Platform
	{
	private:
		sf::RectangleShape shape;    // Visual representation of the platform
		float speed;                 // Movement speed in pixels per second
		float positionX;             // Current X position
		float positionY;             // Current Y position (fixed at bottom)
		float width;                 // Platform width
		float height;                // Platform height
		bool isMovingLeft;           // Flag for left movement
		bool isMovingRight;          // Flag for right movement

	public:
		Platform(float x, float y, float w, float h, float s);
		~Platform() = default;

		// Getters
		sf::FloatRect getBounds() const;
		sf::Vector2f getPosition() const;
		float getWidth() const;
		float getHeight() const;

		// Movement control
		void setMovingLeft(bool moving);
		void setMovingRight(bool moving);
		void update(float timeDelta);

		// Rendering
		void draw(sf::RenderWindow& window) const;

		// Collision detection
		bool checkCollision(const sf::FloatRect& otherBounds) const;
	};
}
