#include "BonusFactory.h"
#include "GameSettings.h"
#include <chrono>

namespace ArkanoidGame
{
	BonusFactory::BonusFactory()
		: rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())),
		  dropChance(0.0f, 1.0f),
		  positionX(50.0f, SCREEN_WIDTH - 50.0f),
		  bonusType(0, 4) // 5 different bonus types
	{
	}

	std::unique_ptr<Bonus> BonusFactory::createBonus(float x, float y)
	{
		if (!shouldDropBonus())
		{
			return nullptr;
		}

		auto effect = createRandomEffect();
		if (!effect)
		{
			return nullptr;
		}

		// Create bonus with slight random offset
		float offsetX = positionX(rng) - x;
		float finalX = x + offsetX * 0.1f; // Small random offset
		
		return std::make_unique<Bonus>(finalX, y, std::move(effect));
	}

	bool BonusFactory::shouldDropBonus()
	{
		return dropChance(rng) < BONUS_DROP_CHANCE;
	}

	std::unique_ptr<IBonusEffect> BonusFactory::createRandomEffect()
	{
		int type = bonusType(rng);
		
		switch (type)
		{
		case 0:
			return std::make_unique<PlatformSizeBonus>(1.5f, 8.0f);
		case 1:
			return std::make_unique<BallSpeedBonus>(1.3f, 6.0f);
		case 2:
			return std::make_unique<ExtraLifeBonus>();
		case 3:
			return std::make_unique<BallSlowBonus>(0.7f, 7.0f);
		case 4:
			return std::make_unique<PointsBonus>(100);
		default:
			return std::make_unique<PlatformSizeBonus>(1.5f, 8.0f);
		}
	}
}
