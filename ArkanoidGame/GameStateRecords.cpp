#include "GameStateRecords.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GameStateRecords::GameStateRecords()
	{
		initializeUI();
	}

	void GameStateRecords::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 50, 100));

		// Initialize title text
		titleText.setFont(font);
		titleText.setString("HIGH SCORES");
		titleText.setCharacterSize(36);
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
		titleText.setPosition(SCREEN_WIDTH / 2, 100);

		// Initialize hint text
		hintText.setFont(font);
		hintText.setString("Press ESC to return to main menu");
		hintText.setCharacterSize(18);
		hintText.setFillColor(sf::Color::White);
		hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
		hintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);

		// Initialize records table texts
		recordsTableTexts.resize(10);
		for (int i = 0; i < 10; ++i)
		{
			recordsTableTexts[i].setFont(font);
			recordsTableTexts[i].setCharacterSize(20);
			recordsTableTexts[i].setFillColor(sf::Color::White);
		}

		updateRecordsTable();
	}

	void GameStateRecords::updateRecordsTable()
	{
		// This would normally fetch records from the Game class
		// For now, we'll use placeholder data
		std::vector<std::pair<std::string, int>> records = {
			{"Player1", 1500},
			{"Player2", 1200},
			{"Player3", 1000},
			{"Player4", 800},
			{"Player5", 600},
			{"Player6", 500},
			{"Player7", 400},
			{"Player8", 300},
			{"Player9", 200},
			{"Player10", 100}
		};

		for (size_t i = 0; i < records.size() && i < recordsTableTexts.size(); ++i)
		{
			std::string recordText = std::to_string(i + 1) + ". " + records[i].first + " - " + std::to_string(records[i].second);
			recordsTableTexts[i].setString(recordText);
			recordsTableTexts[i].setOrigin(recordsTableTexts[i].getLocalBounds().width / 2, recordsTableTexts[i].getLocalBounds().height / 2);
			recordsTableTexts[i].setPosition(SCREEN_WIDTH / 2, 200 + i * 30);
		}
	}

	void GameStateRecords::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				// Return to main menu
				if (game)
				{
					game->PopState();
				}
			}
		}
	}

	void GameStateRecords::update(float timeDelta)
	{
		// No update logic needed for this state
	}

	void GameStateRecords::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw title
		window.draw(titleText);

		// Draw records table
		for (const auto& recordText : recordsTableTexts)
		{
			window.draw(recordText);
		}

		// Draw hint
		window.draw(hintText);
	}
}
