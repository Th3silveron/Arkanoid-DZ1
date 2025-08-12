#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateRecords : public GameStateBase
	{
	private:
		// Resources
		sf::Font font;

		// UI data
		sf::RectangleShape background;
		sf::Text titleText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

	public:
		GameStateRecords();
		~GameStateRecords() = default;

		// GameStateBase interface
		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateRecordsTable();
	};
}
