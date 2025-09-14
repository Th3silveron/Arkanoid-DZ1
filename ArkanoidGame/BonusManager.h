#pragma once
#include "Bonus.h"
#include "BonusFactory.h"
#include "EffectManager.h"
#include "Platform.h"
#include "Ball.h"
#include <vector>
#include <memory>
#include <functional>

namespace ArkanoidGame
{
	/**
	 * @brief Manager class for handling bonuses
	 * 
	 * Uses Manager pattern to handle all bonus-related operations:
	 * - Creating bonuses when blocks are destroyed
	 * - Managing active bonuses and their effects
	 * - Handling bonus collection and expiration
	 */
	class BonusManager
	{
	private:
		std::vector<std::unique_ptr<Bonus>> activeBonuses;
		BonusFactory factory;
		EffectManager effectManager;
		
		// Track all applied effects (including instant ones)
		std::vector<std::string> recentEffects;
		float effectDisplayTime = 2.0f; // Show effects for 2 seconds
		
		// Callbacks for game state changes
		std::function<void(int)> onScoreChange;
		std::function<void(int)> onLivesChange;
		std::function<void(const std::string&)> onEffectApplied;

	public:
		BonusManager();
		~BonusManager() = default;

		// Bonus lifecycle management
		void createBonusFromBlock(float x, float y);
		void updateBonuses(float timeDelta, Platform& platform, Ball& ball);
		void drawBonuses(sf::RenderWindow& window);
		void clearAllBonuses();

		// Collision detection
		void checkPlatformCollisions(Platform& platform, Ball& ball);

		// Callback setters
		void setScoreCallback(std::function<void(int)> callback) { onScoreChange = callback; }
		void setLivesCallback(std::function<void(int)> callback) { onLivesChange = callback; }
		void setEffectCallback(std::function<void(const std::string&)> callback) { onEffectApplied = callback; }

		// Getters
		size_t getActiveBonusCount() const { return activeBonuses.size(); }
		bool hasActiveBonuses() const { return !activeBonuses.empty(); }
		std::vector<std::string> getActiveEffectNames() const;

	private:
		void removeExpiredBonuses();
		void handleBonusCollection(Bonus* bonus, Platform& platform, Ball& ball);
	};
}
