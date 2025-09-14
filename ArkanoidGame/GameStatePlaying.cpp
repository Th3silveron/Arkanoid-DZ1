#include "GameStatePlaying.h"
#include "GameSettings.h"
#include <random>
#include <algorithm>
#include <cmath>

namespace ArkanoidGame
{
	GameStatePlaying::GameStatePlaying()
		: platform(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_SPEED),
		  ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80, BALL_RADIUS, BALL_SPEED)
	{
		initializeUI();
		initializeGameObjects();
		setupBonusCallbacks();
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
		scoreText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setString("Score: 0");

		// Initialize lives text
		livesText.setFont(font);
		livesText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		livesText.setFillColor(sf::Color::Red);
		livesText.setString("Lives: 3");

		// Initialize input hint text
		inputHintText.setFont(font);
		inputHintText.setCharacterSize(UI_FONT_SIZE_SMALL);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("LEFT/RIGHT: move platform | UP/DOWN: aim ball | SPACE: launch ball");

		// Initialize active effects text
		activeEffectsText.setFont(font);
		activeEffectsText.setCharacterSize(UI_FONT_SIZE_TINY);
		activeEffectsText.setFillColor(sf::Color::Cyan);
		activeEffectsText.setString("Active Effects: None");

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

	void GameStatePlaying::setupBonusCallbacks()
	{
		// Set up callbacks for bonus effects
		bonusManager.setScoreCallback([this](int points) {
			score += points;
		});
		
		bonusManager.setLivesCallback([this](int extraLives) {
			lives += extraLives;
		});
		
		bonusManager.setEffectCallback([this](const std::string& effectName) {
			// Could add visual feedback here
			// For now, we'll just update the score text
		});
	}

	void GameStatePlaying::initializeBlocks()
	{
		blocks.clear();
		
		// Define block colors (excluding red - reserved for DurableBricks)
		std::vector<sf::Color> blockColors = {
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
		
		// Random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		
		// Grid setup - keep the grid structure but randomize within each cell
		const float startX = 50.0f;
		const float startY = 100.0f;
		const float cellWidth = BLOCK_WIDTH + BLOCK_SPACING;
		const float cellHeight = BLOCK_HEIGHT + BLOCK_SPACING;
		
		// Smaller random offset for more even grid
		const float maxOffsetX = BLOCK_SPACING * 0.15f; // 15% of spacing for more even look
		const float maxOffsetY = BLOCK_SPACING * 0.15f;
		
		// Create all blocks with perfect grid positions first
		std::vector<std::unique_ptr<Block>> allBlocks;
		const int totalBlocks = BLOCK_ROWS * BLOCKS_PER_ROW;
		
		// Create all blocks with perfect grid positions
		for (int i = 0; i < totalBlocks; ++i)
		{
			int row = i / BLOCKS_PER_ROW;
			int col = i % BLOCKS_PER_ROW;
			
			// Perfect grid position
			float x = startX + col * cellWidth;
			float y = startY + row * cellHeight;
			
			// Add small random offset
			std::uniform_real_distribution<float> offsetXDist(-maxOffsetX, maxOffsetX);
			std::uniform_real_distribution<float> offsetYDist(-maxOffsetY, maxOffsetY);
			
			x += offsetXDist(gen);
			y += offsetYDist(gen);
			
			// Ensure blocks stay within screen bounds
			x = std::max(0.0f, std::min(x, SCREEN_WIDTH - BLOCK_WIDTH));
			y = std::max(0.0f, std::min(y, SCREEN_HEIGHT - 200.0f - BLOCK_HEIGHT));
			
			// Random color for each block
			std::uniform_int_distribution<int> colorDist(0, static_cast<int>(blockColors.size()) - 1);
			sf::Color color = blockColors[colorDist(gen)];
			
			// Random points (10-30)
			std::uniform_int_distribution<int> pointsDist(10, 30);
			int points = pointsDist(gen);
			
			// Create regular block (we'll randomize types later)
			allBlocks.push_back(std::make_unique<Block>(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, color, points));
		}
		
		// Now randomize block types - convert some to special types
		std::uniform_int_distribution<int> typeDist(0, 9);
		for (auto& block : allBlocks)
		{
			int blockType = typeDist(gen);
			
			if (blockType < 2) // 20% chance for DurableBricks
			{
				// Get current block properties
				sf::Vector2f pos = block->getPosition();
				int points = block->getPoints();
				
				// DurableBricks are always red
				sf::Color durableColor = sf::Color::Red;
				
				// Replace with DurableBrick
				block = std::make_unique<DurableBrick>(pos.x, pos.y, BLOCK_WIDTH, BLOCK_HEIGHT, durableColor, points, 3);
			}
			else if (blockType < 4) // 20% chance for GlassBricks
			{
				// Get current block properties
				sf::Vector2f pos = block->getPosition();
				int points = block->getPoints();
				
				// Replace with GlassBrick (keeps its default glass color)
				block = std::make_unique<GlassBrick>(pos.x, pos.y, BLOCK_WIDTH, BLOCK_HEIGHT, points);
			}
			// 60% remain as regular blocks with their random colors
		}
		
		// Move all blocks to the main blocks vector
		for (auto& block : allBlocks)
		{
			blocks.push_back(std::move(block));
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
			// Player won - save game data and switch to name input state
			if (game)
			{
				game->SetCurrentScore(score);
				game->SetGameResult(true); // Player won
				game->SwitchStateTo(GameStateType::NameInput);
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
						
						// Create bonus at block position (10% chance)
						bonusManager.createBonusFromBlock(blockBounds.left + blockBounds.width / 2, blockBounds.top + blockBounds.height / 2);
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
		
		// Save game data and switch to name input state
		if (game)
		{
			game->SetCurrentScore(score);
			game->SetGameResult(false); // Player lost
			game->SwitchStateTo(GameStateType::NameInput);
		}
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
		
		// Update bonuses
		bonusManager.updateBonuses(timeDelta, platform, ball);
		
		// Check collisions
		checkCollisions();

		// Update UI
		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
		
		// Update active effects display
		auto activeEffects = bonusManager.getActiveEffectNames();
		if (activeEffects.empty())
		{
			activeEffectsText.setString("Active Effects: None");
		}
		else
		{
			std::string effectsString = "Active Effects: ";
			for (size_t i = 0; i < activeEffects.size(); ++i)
			{
				if (i > 0) effectsString += ", ";
				effectsString += activeEffects[i];
			}
			activeEffectsText.setString(effectsString);
		}
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
		
		// Draw bonuses
		bonusManager.drawBonuses(window);

		// Draw UI
		scoreText.setPosition(10, 10);
		window.draw(scoreText);

		livesText.setPosition(10, 40);
		window.draw(livesText);

		activeEffectsText.setPosition(10, 70);
		window.draw(activeEffectsText);

		inputHintText.setPosition(10, SCREEN_HEIGHT - 30);
		window.draw(inputHintText);
	}
}
