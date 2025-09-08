#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	/**
	 * @brief GlassBrick class for Arkanoid game
	 * 
	 * Inherits from Block and represents a glass block that:
	 * - Is destroyed with one hit
	 * - Does not cause ball to bounce (ball passes through)
	 * - Has transparent appearance
	 */
	class GlassBrick : public Block
	{
	private:
		sf::Color glassColor; // Semi-transparent glass color

	public:
		GlassBrick(float x, float y, float width, float height, int blockPoints = 5);
		~GlassBrick() = default;

		// Override virtual methods
		bool OnHit() override;
		void draw(sf::RenderWindow& window) const override;

	private:
		void setupGlassAppearance();
	};
}
