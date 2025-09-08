#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	/**
	 * @brief DurableBrick class for Arkanoid game
	 * 
	 * Inherits from Block and represents a block that requires multiple hits to destroy.
	 * Changes visual appearance with each hit and is destroyed after 2-3 hits.
	 */
	class DurableBrick : public Block
	{
	private:
		int maxHits;        // Maximum number of hits before destruction
		int currentHits;    // Current number of hits received
		sf::Color originalColor; // Original color of the block
		sf::Color damagedColor;  // Color when damaged

	public:
		DurableBrick(float x, float y, float width, float height, const sf::Color& blockColor, int blockPoints = 20, int hitsRequired = 3);
		~DurableBrick() = default;

		// Override virtual methods
		bool OnHit() override;
		void draw(sf::RenderWindow& window) const override;

		// Getters
		int getCurrentHits() const { return currentHits; }
		int getMaxHits() const { return maxHits; }
		bool isFullyDamaged() const { return currentHits >= maxHits; }

	private:
		void updateVisualAppearance();
	};
}
