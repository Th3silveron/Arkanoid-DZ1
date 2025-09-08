#include "GameStatePlaying.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GameStatePlaying::GameStatePlaying()
		: platform(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_SPEED),
		  ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80, BALL_RADIUS, BALL_SPEED)
	{
		initializeUI();
		initializeGameObjects();
	}

	void GameStatePlaying::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Load sounds
		if (!ballHitSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"))
		{
			// Fallback if sound loading fails
		}
		if (!gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"))
		{
			// Fallback if sound loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 100, 200));

		// Initialize score text
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setString("Score: 0");

		// Initialize lives text
		livesText.setFont(font);
		livesText.setCharacterSize(24);
		livesText.setFillColor(sf::Color::Red);
		livesText.setString("Lives: 3");

		// Initialize input hint text
		inputHintText.setFont(font);
		inputHintText.setCharacterSize(18);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("LEFT/RIGHT: move platform | UP/DOWN: aim ball | SPACE: launch ball");

		// Initialize sounds
		ballHitSound.setBuffer(ballHitSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlaying::initializeGameObjects()
	{
		// Platform and ball are already initialized in constructor
		initializeBlocks();
		isGameActive = true;
	}

	void GameStatePlaying::initializeBlocks()
	{
		blocks.clear();
		
		// Define block colors
		std::vector<sf::Color> blockColors = {
			sf::Color::Red,
			sf::Color::Green,
			sf::Color::Blue,
			sf::Color::Yellow,
			sf::Color::Magenta,
			sf::Color::Cyan,
			sf::Color(255, 165, 0), // Orange
			sf::Color(128, 0, 128), // Purple
			sf::Color(255, 192, 203), // Pink
			sf::Color(0, 128, 0) // Dark Green
		};
		
		// Block dimensions
		const float blockWidth = 80.0f;
		const float blockHeight = 30.0f;
		const float blockSpacing = 10.0f;
		const float startX = 50.0f;
		const float startY = 100.0f;
		
		// Create blocks in a grid pattern
		int blocksPerRow = 8;
		int numRows = 3;
		
		for (int row = 0; row < numRows; ++row)
		{
			for (int col = 0; col < blocksPerRow; ++col)
			{
				float x = startX + col * (blockWidth + blockSpacing);
				float y = startY + row * (blockHeight + blockSpacing);
				
				// Use different colors for each row
				sf::Color color = blockColors[row % blockColors.size()];
				int points = (numRows - row) * 10; // More points for higher rows
				
				// Create different types of blocks based on position
				if (row == 0) // Top row - DurableBricks
				{
					blocks.push_back(std::make_unique<DurableBrick>(x, y, blockWidth, blockHeight, color, points, 3));
				}
				else if (row == 1 && col % 3 == 0) // Middle row - some GlassBricks
				{
					blocks.push_back(std::make_unique<GlassBrick>(x, y, blockWidth, blockHeight, points));
				}
				else // Regular blocks
				{
					blocks.push_back(std::make_unique<Block>(x, y, blockWidth, blockHeight, color, points));
				}
			}
		}
	}

	void GameStatePlaying::handleInput()
	{
		// Platform movement
		platform.setMovingLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		platform.setMovingRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

		// Ball aiming and launch
		if (!ball.getIsLaunched())
		{
			// Aim with Up/Down arrows
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				ball.setAimDirection(-1.0f); // Aim left
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				ball.setAimDirection(1.0f); // Aim right
			}
			else
			{
				ball.setAimDirection(0.0f); // Aim straight
			}

			// Launch ball with Space
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				ball.launch();
			}
		}
	}

	void GameStatePlaying::checkCollisions()
	{
		// Check ball-platform collision
		if (ball.getIsLaunched())
		{
			ball.handlePlatformCollision(platform.getBounds());
		}

		// Check ball-block collisions
		checkBlockCollisions();

		// Check if ball fell below screen (lose life)
		if (ball.getPosition().y > SCREEN_HEIGHT)
		{
			lives--;
			if (lives > 0)
			{
				resetBall();
			}
			else
			{
				gameOver();
			}
		}

		// Check win condition
		if (checkWinCondition())
		{
			// Player won - switch to win state
			if (game)
			{
				game->SwitchStateTo(GameStateType::Win);
			}
		}
	}

	void GameStatePlaying::checkBlockCollisions()
	{
		if (!ball.getIsLaunched()) return;

		// Check collisions with all active blocks
		for (auto& block : blocks)
		{
			if (block->getIsActive())
			{
				// Get ball and block bounds
				sf::FloatRect ballBounds = ball.getBounds();
				sf::FloatRect blockBounds = block->getBounds();
				
				// Check if ball intersects with block
				if (ballBounds.intersects(blockBounds))
				{
					// Handle collision - check if block should bounce ball
					bool shouldBounce = block->OnHit();
					
					if (shouldBounce)
					{
						ball.handleBlockCollision(blockBounds);
					}
					
					// Add points if block was destroyed
					if (block->isDestroyed())
					{
						score += block->getPoints();
					}
					
					// Play hit sound
					ballHitSound.play();
					
					break; // Only handle one collision per frame to prevent multiple hits
				}
			}
		}
	}

	void GameStatePlaying::resetBall()
	{
		// Reset ball to platform position
		float platformX = platform.getPosition().x;
		float platformY = platform.getPosition().y - platform.getHeight() / 2 - ball.getRadius();
		ball.reset(platformX, platformY);
	}

	void GameStatePlaying::gameOver()
	{
		gameOverSound.play();
		isGameActive = false;
		// Game over logic will be handled by the Game class
	}

	bool GameStatePlaying::checkWinCondition()
	{
		// Check if all blocks are destroyed
		for (const auto& block : blocks)
		{
			if (block->getIsActive())
			{
				return false; // At least one block is still active
			}
		}
		return true; // All blocks are destroyed
	}

	void GameStatePlaying::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				// Return to main menu
				if (game)
				{
					game->SwitchStateTo(GameStateType::MainMenu);
				}
			}
		}
	}

	void GameStatePlaying::update(float timeDelta)
	{
		if (!isGameActive)
			return;

		handleInput();
		
		// Update game objects
		platform.update(timeDelta);
		
		// Make ball follow platform when not launched
		if (!ball.getIsLaunched())
		{
			ball.followPlatform(platform.getPosition(), platform.getWidth());
		}
		
		ball.update(timeDelta);
		
		// Check collisions multiple times if ball is moving fast to prevent tunneling
		checkCollisions();
		
		// Additional collision check for fast-moving ball
		if (ball.getIsLaunched())
		{
			checkBlockCollisions();
		}

		// Update UI
		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
	}

	void GameStatePlaying::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw blocks
		for (const auto& block : blocks)
		{
			block->draw(window);
		}

		// Draw game objects
		platform.draw(window);
		ball.draw(window);

		// Draw UI
		scoreText.setPosition(10, 10);
		window.draw(scoreText);

		livesText.setPosition(10, 40);
		window.draw(livesText);

		inputHintText.setPosition(10, SCREEN_HEIGHT - 30);
		window.draw(inputHintText);
	}
}
