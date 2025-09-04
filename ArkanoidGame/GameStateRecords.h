#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Records display state for Arkanoid game
	 * 
	 * Shows the high scores table with player names and scores.
	 * Player can press ESC to return to main menu.
	 */
	class GameStateRecords : public GameStateBase
	{
	private:
		sf::Font font;
		sf::Text titleText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
		sf::RectangleShape background;

	public:
		GameStateRecords();
		~GameStateRecords() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateRecordsTable();
	};
}
