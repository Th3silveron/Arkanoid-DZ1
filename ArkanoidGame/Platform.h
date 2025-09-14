#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	/**
	 * @brief Player-controlled platform class for Arkanoid game
	 * 
	 * The platform is a rectangle that can move left and right
	 * at the bottom of the screen. It's controlled by arrow keys
	 * and is used to bounce the ball back into play.
	 */
	class Platform : public GameObject
	{
	private:
		sf::RectangleShape shape;    // Visual representation of the platform
		float speed;                 // Movement speed in pixels per second
		bool isMovingLeft;           // Flag for left movement
		bool isMovingRight;          // Flag for right movement

	public:
		Platform(float x, float y, float w, float h, float s);
		~Platform() = default;

		// Getters
		sf::FloatRect getBounds() const override;
		float getWidth() const { return size.x; }
		float getHeight() const { return size.y; }

		// Movement control
		void setMovingLeft(bool moving);
		void setMovingRight(bool moving);
		void update(float timeDelta) override;

		// Rendering
		void draw(sf::RenderWindow& window) const override;
		
		// Bonus support
		void setWidth(float newWidth);
		void setVisualEffect(bool hasEffect);
	};
}
