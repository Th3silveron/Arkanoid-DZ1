#pragma once
#include "Bonus.h"
#include "BonusEffects.h"
#include <random>
#include <memory>

namespace ArkanoidGame
{
	/**
	 * @brief Factory class for creating bonuses
	 * 
	 * Uses Factory pattern to create different types of bonuses
	 * with random effects and positions
	 */
	class BonusFactory
	{
	private:
		std::mt19937 rng;
		std::uniform_real_distribution<float> dropChance;
		std::uniform_real_distribution<float> positionX;
		std::uniform_int_distribution<int> bonusType;

	public:
		BonusFactory();
		
		/**
		 * @brief Creates a bonus at the specified position
		 * @param x X position
		 * @param y Y position
		 * @return Unique pointer to bonus or nullptr if no bonus should be created
		 */
		std::unique_ptr<Bonus> createBonus(float x, float y);
		
		/**
		 * @brief Determines if a bonus should drop (10% chance)
		 * @return True if bonus should drop
		 */
		bool shouldDropBonus();
		
		/**
		 * @brief Creates a random bonus effect
		 * @return Unique pointer to bonus effect
		 */
		std::unique_ptr<IBonusEffect> createRandomEffect();
	};
}
