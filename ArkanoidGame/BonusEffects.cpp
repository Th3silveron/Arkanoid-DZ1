#include "BonusEffects.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	// PlatformSizeBonus implementation
	PlatformSizeBonus::PlatformSizeBonus(float bonusMultiplier, float effectDuration)
		: originalWidth(0), bonusWidth(0), duration(effectDuration)
	{
		bonusWidth = PLATFORM_WIDTH * bonusMultiplier;
	}

	void PlatformSizeBonus::applyEffect(Platform& platform, Ball& ball)
	{
		originalWidth = platform.getWidth();
		platform.setWidth(bonusWidth);
		platform.setVisualEffect(true);
	}

	void PlatformSizeBonus::removeEffect(Platform& platform, Ball& ball)
	{
		platform.setWidth(originalWidth);
		platform.setVisualEffect(false);
	}

	std::unique_ptr<IBonusEffect> PlatformSizeBonus::clone() const
	{
		return std::make_unique<PlatformSizeBonus>(bonusWidth / PLATFORM_WIDTH, duration);
	}

	// BallSpeedBonus implementation
	BallSpeedBonus::BallSpeedBonus(float speedMultiplier, float effectDuration)
		: originalSpeed(0), bonusMultiplier(speedMultiplier), duration(effectDuration)
	{
	}

	void BallSpeedBonus::applyEffect(Platform& platform, Ball& ball)
	{
		originalSpeed = ball.getSpeed();
		ball.setSpeed(originalSpeed * bonusMultiplier);
		ball.setVisualEffect(true);
	}

	void BallSpeedBonus::removeEffect(Platform& platform, Ball& ball)
	{
		ball.setSpeed(originalSpeed);
		ball.setVisualEffect(false);
		// Note: isBonusSpeedActive flag will be reset when speed is restored to original
	}

	std::unique_ptr<IBonusEffect> BallSpeedBonus::clone() const
	{
		return std::make_unique<BallSpeedBonus>(bonusMultiplier, duration);
	}

	// ExtraLifeBonus implementation
	ExtraLifeBonus::ExtraLifeBonus(float effectDuration)
		: duration(effectDuration)
	{
	}

	void ExtraLifeBonus::applyEffect(Platform& platform, Ball& ball)
	{
		// This will be handled by the game state
		// We'll use a callback or observer pattern
	}

	void ExtraLifeBonus::removeEffect(Platform& platform, Ball& ball)
	{
		// No cleanup needed for instant effect
	}

	std::unique_ptr<IBonusEffect> ExtraLifeBonus::clone() const
	{
		return std::make_unique<ExtraLifeBonus>(duration);
	}

	// BallSlowBonus implementation
	BallSlowBonus::BallSlowBonus(float speedMultiplier, float effectDuration)
		: originalSpeed(0), slowMultiplier(speedMultiplier), duration(effectDuration)
	{
	}

	void BallSlowBonus::applyEffect(Platform& platform, Ball& ball)
	{
		originalSpeed = ball.getSpeed();
		ball.setSpeed(originalSpeed * slowMultiplier);
		ball.setVisualEffect(true);
	}

	void BallSlowBonus::removeEffect(Platform& platform, Ball& ball)
	{
		ball.setSpeed(originalSpeed);
		ball.setVisualEffect(false);
		// Note: isBonusSpeedActive flag will be reset when speed is restored to original
	}

	std::unique_ptr<IBonusEffect> BallSlowBonus::clone() const
	{
		return std::make_unique<BallSlowBonus>(slowMultiplier, duration);
	}

	// PointsBonus implementation
	PointsBonus::PointsBonus(int points, float effectDuration)
		: bonusPoints(points), duration(effectDuration)
	{
	}

	void PointsBonus::applyEffect(Platform& platform, Ball& ball)
	{
		// This will be handled by the game state
		// We'll use a callback or observer pattern
	}

	void PointsBonus::removeEffect(Platform& platform, Ball& ball)
	{
		// No cleanup needed for instant effect
	}

	std::unique_ptr<IBonusEffect> PointsBonus::clone() const
	{
		return std::make_unique<PointsBonus>(bonusPoints, duration);
	}
}
