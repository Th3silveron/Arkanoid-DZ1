#include "GameStateRecords.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "GameSettings.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	GameStateRecords::GameStateRecords()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		initializeUI();
		updateRecordsTable();
	}

	void GameStateRecords::initializeUI()
	{
		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(50, 50, 100)); // Dark blue background

		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setStyle(sf::Text::Bold);
		titleText.setFillColor(sf::Color::Red);
		titleText.setString("RECORDS");

		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Press ESC to return to main menu");

		recordsTableTexts.reserve(MAX_RECORDS_TABLE_SIZE);
	}

	void GameStateRecords::updateRecordsTable()
	{
		const Game& game = Application::Instance().GetGame();
		std::multimap<int, std::string> sortedRecordsTable;
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			recordsTableTexts.emplace_back();
			sf::Text& text = recordsTableTexts.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
		}
	}

	void GameStateRecords::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}
		}
	}

	void GameStateRecords::update(float timeDelta)
	{
		// No update logic needed
	}

	void GameStateRecords::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		// Draw background
		window.draw(background);

		// Draw title
		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.5f }));
		titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(titleText);

		// Draw records table
		std::vector<sf::Text*> textsList;
		textsList.reserve(recordsTableTexts.size());
		for (auto& text : recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2.f, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		// Draw hint
		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 0.5f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(hintText);
	}
}
