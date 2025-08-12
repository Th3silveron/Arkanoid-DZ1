#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateMainMenu : public GameStateBase
	{
	private:
		// Resources
		sf::Font font;

		// UI data
		sf::RectangleShape background;
		sf::Text titleText;
		sf::Text startText;
		sf::Text exitText;
		sf::Text hintText;

	public:
		GameStateMainMenu();
		~GameStateMainMenu() = default;

		// GameStateBase interface
		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
	};
}
