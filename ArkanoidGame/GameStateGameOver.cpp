#include "GameStateGameOver.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GameStateGameOver::GameStateGameOver()
	{
		initializeUI();
	}

	void GameStateGameOver::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0, 200));

		// Initialize game over text
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(48);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
		gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100);

		// Initialize hint text
		hintText.setFont(font);
		hintText.setString("Press any key to return to main menu");
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
		hintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);

		// Initialize records table texts
		recordsTableTexts.resize(5);
		for (int i = 0; i < 5; ++i)
		{
			recordsTableTexts[i].setFont(font);
			recordsTableTexts[i].setCharacterSize(20);
			recordsTableTexts[i].setFillColor(sf::Color::Yellow);
		}

		updateRecordsTable();
	}

	void GameStateGameOver::updateRecordsTable()
	{
		// This would normally fetch records from the Game class
		// For now, we'll use placeholder data
		std::vector<std::pair<std::string, int>> records = {
			{"Player1", 1000},
			{"Player2", 800},
			{"Player3", 600},
			{"Player4", 400},
			{"Player5", 200}
		};

		for (size_t i = 0; i < records.size() && i < recordsTableTexts.size(); ++i)
		{
			std::string recordText = std::to_string(i + 1) + ". " + records[i].first + " - " + std::to_string(records[i].second);
			recordsTableTexts[i].setString(recordText);
			recordsTableTexts[i].setOrigin(recordsTableTexts[i].getLocalBounds().width / 2, recordsTableTexts[i].getLocalBounds().height / 2);
			recordsTableTexts[i].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20 + i * 30);
		}
	}

	void GameStateGameOver::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			// Any key pressed returns to main menu
			if (game)
			{
				game->SwitchStateTo(GameStateType::MainMenu);
			}
		}
	}

	void GameStateGameOver::update(float timeDelta)
	{
		timeSinceGameOver += timeDelta;
	}

	void GameStateGameOver::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game over text
		window.draw(gameOverText);

		// Draw hint text
		window.draw(hintText);

		// Draw records table
		for (const auto& recordText : recordsTableTexts)
		{
			window.draw(recordText);
		}
	}
}
