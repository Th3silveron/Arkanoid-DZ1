#include "BonusManager.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	BonusManager::BonusManager()
	{
	}

	void BonusManager::createBonusFromBlock(float x, float y)
	{
		auto bonus = factory.createBonus(x, y);
		if (bonus)
		{
			// Set up collection callback
			bonus->onCollected = [this](Bonus* collectedBonus) {
				// This will be handled in handleBonusCollection
			};
			
			activeBonuses.push_back(std::move(bonus));
		}
	}

	void BonusManager::updateBonuses(float timeDelta, Platform& platform, Ball& ball)
	{
		// Update all active bonuses
		for (auto& bonus : activeBonuses)
		{
			if (bonus && bonus->getIsActive())
			{
				bonus->update(timeDelta);
			}
		}

		// Update active effects
		effectManager.updateEffects(timeDelta);

		// Update recent effects display time
		if (!recentEffects.empty())
		{
			effectDisplayTime -= timeDelta;
			if (effectDisplayTime <= 0.0f)
			{
				recentEffects.clear();
				effectDisplayTime = 2.0f; // Reset for next effect
			}
		}

		// Check for platform collisions
		checkPlatformCollisions(platform, ball);

		// Remove expired bonuses
		removeExpiredBonuses();
	}

	void BonusManager::drawBonuses(sf::RenderWindow& window)
	{
		for (const auto& bonus : activeBonuses)
		{
			if (bonus && bonus->getIsActive())
			{
				bonus->draw(window);
			}
		}
	}

	void BonusManager::clearAllBonuses()
	{
		activeBonuses.clear();
	}

	void BonusManager::checkPlatformCollisions(Platform& platform, Ball& ball)
	{
		sf::FloatRect platformBounds = platform.getBounds();
		
		for (auto& bonus : activeBonuses)
		{
			if (bonus && bonus->getIsActive() && !bonus->getIsCollected())
			{
				sf::FloatRect bonusBounds = bonus->getBounds();
				
				if (platformBounds.intersects(bonusBounds))
				{
					handleBonusCollection(bonus.get(), platform, ball);
					bonus->collect();
				}
			}
		}
	}

	void BonusManager::removeExpiredBonuses()
	{
		activeBonuses.erase(
			std::remove_if(activeBonuses.begin(), activeBonuses.end(),
				[](const std::unique_ptr<Bonus>& bonus) {
					return !bonus || !bonus->getIsActive() || bonus->isExpired();
				}),
			activeBonuses.end()
		);
	}

	void BonusManager::handleBonusCollection(Bonus* bonus, Platform& platform, Ball& ball)
	{
		if (!bonus || !bonus->getEffect()) return;

		IBonusEffect* effect = bonus->getEffect();
		
		// Handle instant effects (no duration)
		if (effect->getDuration() == 0.0f)
		{
			// Apply instant effect
			effect->applyEffect(platform, ball);
			
			// Add to recent effects for display
			recentEffects.clear(); // Clear previous effects
			recentEffects.push_back(effect->getEffectName());
			effectDisplayTime = 2.0f; // Reset display timer
			
			// Handle specific instant effects
			if (effect->getEffectName() == "+1 Life" && onLivesChange)
			{
				onLivesChange(1); // Add one life
			}
			else if (effect->getEffectName() == "Bonus Points" && onScoreChange)
			{
				onScoreChange(100); // Add 100 points
			}
		}
		else
		{
			// Handle timed effects through EffectManager
			auto effectCopy = effect->clone();
			if (effectCopy)
			{
				effectManager.applyEffect(std::move(effectCopy), platform, ball);
			}
		}
		
		// Notify about effect application
		if (onEffectApplied)
		{
			onEffectApplied(effect->getEffectName());
		}
	}

	std::vector<std::string> BonusManager::getActiveEffectNames() const
	{
		std::vector<std::string> allEffects;
		
		// Get active timed effects
		auto activeEffects = effectManager.getActiveEffectNames();
		allEffects.insert(allEffects.end(), activeEffects.begin(), activeEffects.end());
		
		// Add recent instant effects
		allEffects.insert(allEffects.end(), recentEffects.begin(), recentEffects.end());
		
		return allEffects;
	}
}
