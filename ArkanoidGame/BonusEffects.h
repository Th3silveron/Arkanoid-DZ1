#pragma once
#include "Bonus.h"
#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	/**
	 * @brief Bonus effect that increases platform size
	 */
	class PlatformSizeBonus : public IBonusEffect
	{
	private:
		float originalWidth;
		float bonusWidth;
		float duration;

	public:
		PlatformSizeBonus(float bonusMultiplier = 1.5f, float effectDuration = 8.0f);
		void applyEffect(Platform& platform, Ball& ball) override;
		void removeEffect(Platform& platform, Ball& ball) override;
		std::string getEffectName() const override { return "Platform Size+"; }
		float getDuration() const override { return duration; }
		std::unique_ptr<IBonusEffect> clone() const override;
	};

	/**
	 * @brief Bonus effect that increases ball speed
	 */
	class BallSpeedBonus : public IBonusEffect
	{
	private:
		float originalSpeed;
		float bonusMultiplier;
		float duration;

	public:
		BallSpeedBonus(float speedMultiplier = 1.3f, float effectDuration = 6.0f);
		void applyEffect(Platform& platform, Ball& ball) override;
		void removeEffect(Platform& platform, Ball& ball) override;
		std::string getEffectName() const override { return "Ball Speed+"; }
		float getDuration() const override { return duration; }
		std::unique_ptr<IBonusEffect> clone() const override;
	};

	/**
	 * @brief Bonus effect that gives extra life
	 */
	class ExtraLifeBonus : public IBonusEffect
	{
	private:
		float duration;

	public:
		ExtraLifeBonus(float effectDuration = 0.0f); // Instant effect
		void applyEffect(Platform& platform, Ball& ball) override;
		void removeEffect(Platform& platform, Ball& ball) override;
		std::string getEffectName() const override { return "+1 Life"; }
		float getDuration() const override { return duration; }
		std::unique_ptr<IBonusEffect> clone() const override;
	};

	/**
	 * @brief Bonus effect that slows down ball speed
	 */
	class BallSlowBonus : public IBonusEffect
	{
	private:
		float originalSpeed;
		float slowMultiplier;
		float duration;

	public:
		BallSlowBonus(float speedMultiplier = 0.7f, float effectDuration = 7.0f);
		void applyEffect(Platform& platform, Ball& ball) override;
		void removeEffect(Platform& platform, Ball& ball) override;
		std::string getEffectName() const override { return "Ball Slow"; }
		float getDuration() const override { return duration; }
		std::unique_ptr<IBonusEffect> clone() const override;
	};

	/**
	 * @brief Bonus effect that gives extra points
	 */
	class PointsBonus : public IBonusEffect
	{
	private:
		int bonusPoints;
		float duration;

	public:
		PointsBonus(int points = 100, float effectDuration = 0.0f); // Instant effect
		void applyEffect(Platform& platform, Ball& ball) override;
		void removeEffect(Platform& platform, Ball& ball) override;
		std::string getEffectName() const override { return "Bonus Points"; }
		float getDuration() const override { return duration; }
		std::unique_ptr<IBonusEffect> clone() const override;
	};
}
