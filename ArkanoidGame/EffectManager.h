#pragma once
#include "BonusEffects.h"
#include "Platform.h"
#include "Ball.h"
#include <vector>
#include <memory>

namespace ArkanoidGame
{
	/**
	 * @brief Manages active bonus effects and their timers
	 * 
	 * Tracks active effects, applies them, and removes them when they expire.
	 * Uses RAII pattern to ensure effects are properly cleaned up.
	 */
	class EffectManager
	{
	private:
		struct ActiveEffect
		{
			std::unique_ptr<IBonusEffect> effect;
			float remainingTime;
			bool isActive;

			ActiveEffect(std::unique_ptr<IBonusEffect> eff, float dur)
				: effect(std::move(eff)), remainingTime(dur), isActive(true)
			{
			}
		};

		std::vector<ActiveEffect> activeEffects;
		Platform* platform;
		Ball* ball;

	public:
		EffectManager();
		~EffectManager();

		// Effect management
		void applyEffect(std::unique_ptr<IBonusEffect> effect, Platform& platform, Ball& ball);
		void updateEffects(float timeDelta);
		void clearAllEffects();

		// Getters
		bool hasActiveEffects() const { return !activeEffects.empty(); }
		size_t getActiveEffectCount() const { return activeEffects.size(); }
		
		// Get active effect names for UI
		std::vector<std::string> getActiveEffectNames() const;

	private:
		void removeExpiredEffects();
		void setReferences(Platform& platform, Ball& ball);
	};
}
