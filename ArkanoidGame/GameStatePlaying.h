#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "Game.h"
#include <vector>

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Main game state for Arkanoid gameplay
	 * 
	 * This state handles the main game loop including:
	 * - Platform movement controlled by arrow keys
	 * - Ball physics and collision detection
	 * - Score tracking and lives management
	 * - Game over conditions
	 */
	class GameStatePlaying : public GameStateBase
	{
	private:
		// Resource management
		sf::Font font;
		sf::SoundBuffer ballHitSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game objects
		Platform platform;
		Ball ball;
		std::vector<Block> blocks;
		int score = 0;
		int lives = 3;

		// UI elements
		sf::Text scoreText;
		sf::Text livesText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Audio
		sf::Sound ballHitSound;
		sf::Sound gameOverSound;

		// Game state flags
		bool isGameActive = false;

	public:
		GameStatePlaying();
		~GameStatePlaying() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void initializeGameObjects();
		void initializeBlocks();
		void handleInput();
		void checkCollisions();
		void checkBlockCollisions();
		void resetBall();
		void gameOver();
		bool checkWinCondition();
	};
}
