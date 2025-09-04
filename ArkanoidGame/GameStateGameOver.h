#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Game over state for Arkanoid game
	 * 
	 * Displays game over message, final score, and records table.
	 * Player can press any key to return to main menu.
	 */
	class GameStateGameOver : public GameStateBase
	{
	private:
		sf::Font font;
		float timeSinceGameOver = 0.f;
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

	public:
		GameStateGameOver();
		~GameStateGameOver() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateRecordsTable();
	};
}
