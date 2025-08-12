#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateGameOver : public GameStateBase
	{
	private:
		// Resources
		sf::Font font;

		float timeSinceGameOver = 0.f;

		// UI data
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

	public:
		GameStateGameOver();
		~GameStateGameOver() = default;

		// GameStateBase interface
		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateRecordsTable();
	};
}
