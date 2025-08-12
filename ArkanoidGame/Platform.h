#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

namespace ArkanoidGame
{
	class Platform
	{
	private:
		sf::RectangleShape shape;
		float speed;
		float positionX;
		float positionY;
		float width;
		float height;
		bool isMovingLeft;
		bool isMovingRight;

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
		void draw(sf::RenderWindow& window);

		// Collision detection
		bool checkCollision(const sf::FloatRect& otherBounds) const;
	};
}
