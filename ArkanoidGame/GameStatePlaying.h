#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "Game.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlaying : public GameStateBase
	{
	private:
		// Resources
		sf::Font font;
		sf::SoundBuffer ballHitSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game objects
		Platform platform;
		Ball ball;
		int score = 0;
		int lives = 3;

		// UI data
		sf::Text scoreText;
		sf::Text livesText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound ballHitSound;
		sf::Sound gameOverSound;

		// Game state
		bool isGameActive = false;

	public:
		GameStatePlaying();
		~GameStatePlaying() = default;

		// GameStateBase interface
		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void initializeGameObjects();
		void handleInput();
		void checkCollisions();
		void resetBall();
		void gameOver();
	};
}
