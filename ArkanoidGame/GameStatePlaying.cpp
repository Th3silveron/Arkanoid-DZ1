#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "GameSettings.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	GameStatePlaying::GameStatePlaying()
		: platform(SCREEN_WIDTH / 2.f - PLATFORM_WIDTH / 2.f, SCREEN_HEIGHT - 50.f, PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_SPEED),
		  ball(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 80.f, BALL_RADIUS, BALL_SPEED)
	{
		// Load resources
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(ballHitSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav")); // Reusing existing sound
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		initializeUI();
		initializeGameObjects();
	}

	void GameStatePlaying::initializeUI()
	{
		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(50, 50, 100)); // Dark blue background

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setString("Score: 0");

		livesText.setFont(font);
		livesText.setCharacterSize(24);
		livesText.setFillColor(sf::Color::Red);
		livesText.setString("Lives: 3");

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(20);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Arrow keys to move platform\nSpace to launch ball\nESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		// Init sounds
		ballHitSound.setBuffer(ballHitSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlaying::initializeGameObjects()
	{
		// Platform and ball are initialized in constructor
		resetBall();
	}

	void GameStatePlaying::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
			else if (event.key.code == sf::Keyboard::Space && !isGameActive)
			{
				ball.launch();
				isGameActive = true;
			}
		}
	}

	void GameStatePlaying::update(float timeDelta)
	{
		handleInput();
		
		// Update game objects
		platform.update(timeDelta);
		ball.update(timeDelta);

		if (isGameActive)
		{
			checkCollisions();
		}
		else
		{
			// Ball follows platform when not launched
			sf::Vector2f platformPos = platform.getPosition();
			ball.setPosition(platformPos.x + platform.getWidth() / 2.f, platformPos.y - BALL_RADIUS);
		}

		// Update UI
		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
	}

	void GameStatePlaying::handleInput()
	{
		// Platform movement
		platform.setMovingLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		platform.setMovingRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	}

	void GameStatePlaying::checkCollisions()
	{
		// Ball collision with walls
		ball.handleWallCollision();

		// Ball collision with platform
		ball.handlePlatformCollision(platform.getBounds());

		// Check if ball fell below screen
		if (ball.getPosition().y > SCREEN_HEIGHT + BALL_RADIUS)
		{
			lives--;
			if (lives <= 0)
			{
				gameOver();
			}
			else
			{
				resetBall();
			}
		}
	}

	void GameStatePlaying::resetBall()
	{
		sf::Vector2f platformPos = platform.getPosition();
		ball.reset(platformPos.x + platform.getWidth() / 2.f, platformPos.y - BALL_RADIUS);
		isGameActive = false;
	}

	void GameStatePlaying::gameOver()
	{
		gameOverSound.play();
		
		Game& game = Application::Instance().GetGame();
		game.UpdateRecord(PLAYER_NAME, score);
		game.PushState(GameStateType::GameOver, false);
	}

	void GameStatePlaying::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game objects
		platform.draw(window);
		ball.draw(window);

		// Draw UI
		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		livesText.setOrigin(GetTextOrigin(livesText, { 0.f, 0.f }));
		livesText.setPosition(10.f, 40.f);
		window.draw(livesText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
