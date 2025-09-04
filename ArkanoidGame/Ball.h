#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	/**
	 * @brief Ball class for Arkanoid game with physics and collision detection
	 * 
	 * The ball moves around the screen and bounces off walls and the platform.
	 * It can be launched by the player and has realistic physics for bouncing.
	 */
	class Ball : public GameObject
	{
	private:
		sf::CircleShape shape;       // Visual representation of the ball
		float radius;                // Ball radius
		float velocityX;             // Horizontal velocity
		float velocityY;             // Vertical velocity
		float speed;                 // Ball speed (magnitude of velocity)
		bool isLaunched;             // Whether ball is in motion
		float aimDirection;          // Aim direction (-1.0 to 1.0)
		float lastCollisionTime;     // Time of last collision to prevent multiple hits

	public:
		Ball(float x, float y, float r, float s);
		~Ball() = default;

		// Getters
		sf::FloatRect getBounds() const;
		sf::Vector2f getPosition() const;
		float getRadius() const;
		bool getIsLaunched() const;

		// Game mechanics
		void launch();
		void update(float timeDelta);
		void draw(sf::RenderWindow& window) const;
		void followPlatform(const sf::Vector2f& platformPosition, float platformWidth);
		void setAimDirection(float direction); // -1.0 to 1.0, where -1 is left, 1 is right

		// Collision handling
		void handleWallCollision();
		void handlePlatformCollision(const sf::FloatRect& platformBounds);
		void handleBlockCollision(const sf::FloatRect& blockBounds);

		// State control
		void reset(float x, float y);
		void setPosition(float x, float y);
		void setVelocity(float vx, float vy);
	};
}
