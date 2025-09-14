#include "GameStateRecords.h"
#include "GameSettings.h"
#include <algorithm>

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
		if (!game) return;

		// Get records from Game class
		const auto& recordsTable = game->GetRecordsTable();
		
		// Convert to vector and sort by score (descending)
		std::vector<std::pair<std::string, int>> records;
		for (const auto& record : recordsTable)
		{
			records.push_back({record.first, record.second});
		}
		
		// Sort by score in descending order
		std::sort(records.begin(), records.end(), 
			[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
				return a.second > b.second;
			});

		// Display up to 10 records
		size_t displayCount = std::min(records.size(), recordsTableTexts.size());
		
		for (size_t i = 0; i < displayCount; ++i)
		{
			std::string recordText = std::to_string(i + 1) + ". " + records[i].first + " - " + std::to_string(records[i].second);
			recordsTableTexts[i].setString(recordText);
			recordsTableTexts[i].setOrigin(recordsTableTexts[i].getLocalBounds().width / 2, recordsTableTexts[i].getLocalBounds().height / 2);
			recordsTableTexts[i].setPosition(SCREEN_WIDTH / 2, 200.0f + static_cast<float>(i) * 30.0f);
		}
		
		// Clear remaining slots if there are fewer than 10 records
		for (size_t i = displayCount; i < recordsTableTexts.size(); ++i)
		{
			recordsTableTexts[i].setString("");
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
					game->SwitchStateTo(GameStateType::MainMenu);
				}
			}
		}
	}

	void GameStateRecords::update(float timeDelta)
	{
		// Update records table in case new records were added
		updateRecordsTable();
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
