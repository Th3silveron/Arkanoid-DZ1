#include "EffectManager.h"
#include <algorithm>

namespace ArkanoidGame
{
	EffectManager::EffectManager()
		: platform(nullptr), ball(nullptr)
	{
	}

	EffectManager::~EffectManager()
	{
		// Clean up all active effects
		clearAllEffects();
	}

	void EffectManager::applyEffect(std::unique_ptr<IBonusEffect> effect, Platform& platform, Ball& ball)
	{
		if (!effect) return;

		// Set references for cleanup
		setReferences(platform, ball);

		// Apply the effect immediately
		effect->applyEffect(platform, ball);

		// Add to active effects list
		float duration = effect->getDuration();
		if (duration > 0.0f) // Only track effects with duration
		{
			activeEffects.emplace_back(std::move(effect), duration);
		}
	}

	void EffectManager::updateEffects(float timeDelta)
	{
		if (activeEffects.empty()) return;

		// Update remaining time for all effects
		for (auto& activeEffect : activeEffects)
		{
			if (activeEffect.isActive)
			{
				activeEffect.remainingTime -= timeDelta;
			}
		}

		// Remove expired effects
		removeExpiredEffects();
	}

	void EffectManager::clearAllEffects()
	{
		// Remove all effects and restore original state
		for (auto& activeEffect : activeEffects)
		{
			if (activeEffect.isActive && activeEffect.effect && platform && ball)
			{
				activeEffect.effect->removeEffect(*platform, *ball);
			}
		}
		activeEffects.clear();
	}

	std::vector<std::string> EffectManager::getActiveEffectNames() const
	{
		std::vector<std::string> names;
		for (const auto& activeEffect : activeEffects)
		{
			if (activeEffect.isActive && activeEffect.effect)
			{
				names.push_back(activeEffect.effect->getEffectName());
			}
		}
		return names;
	}

	void EffectManager::removeExpiredEffects()
	{
		// Remove expired effects
		activeEffects.erase(
			std::remove_if(activeEffects.begin(), activeEffects.end(),
				[this](ActiveEffect& activeEffect) {
					if (!activeEffect.isActive || !activeEffect.effect)
						return true;

					// Check if effect has expired
					if (activeEffect.remainingTime <= 0.0f)
					{
						// Remove the effect
						if (platform && ball)
						{
							activeEffect.effect->removeEffect(*platform, *ball);
						}
						activeEffect.isActive = false;
						return true;
					}
					return false;
				}),
			activeEffects.end()
		);
	}

	void EffectManager::setReferences(Platform& platformRef, Ball& ballRef)
	{
		platform = &platformRef;
		ball = &ballRef;
	}
}
