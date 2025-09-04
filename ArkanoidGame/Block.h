#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	/**
	 * @brief Block class for Arkanoid game
	 * 
	 * Inherits from GameObject and represents destructible blocks
	 * that the ball can hit. Each block has a color and can be destroyed.
	 */
	class Block : public GameObject
	{
	private:
		sf::RectangleShape shape;
		sf::Color color;
		int points = 10; // Points awarded when destroyed

	public:
		Block(float x, float y, float width, float height, const sf::Color& blockColor, int blockPoints = 10);
		~Block() = default;

		// Getters
		sf::Color getColor() const { return color; }
		int getPoints() const { return points; }

		// Override virtual methods
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) const override;

		// Block-specific methods
		void destroy();
		bool isDestroyed() const { return !isActive; }
	};
}
