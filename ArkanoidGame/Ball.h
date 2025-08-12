#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

namespace ArkanoidGame
{
	class Ball
	{
	private:
		sf::CircleShape shape;
		float radius;
		float positionX;
		float positionY;
		float velocityX;
		float velocityY;
		float speed;
		bool isLaunched;

	public:
		Ball(float x, float y, float r, float s);
		~Ball() = default;

		// Getters
		sf::FloatRect getBounds() const;
		sf::Vector2f getPosition() const;
		float getRadius() const;
		bool getIsLaunched() const;

		// Movement and physics
		void launch();
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);

		// Collision handling
		void handleWallCollision();
		void handlePlatformCollision(const sf::FloatRect& platformBounds);
		void reset(float x, float y);

		// Ball state
		void setPosition(float x, float y);
		void setVelocity(float vx, float vy);
	};
}
