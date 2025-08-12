#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "GameSettings.h"
#include <assert.h>

namespace ArkanoidGame
{
	GameStateMainMenu::GameStateMainMenu()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		initializeUI();
	}

	void GameStateMainMenu::initializeUI()
	{
		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(50, 50, 100)); // Dark blue background

		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setStyle(sf::Text::Bold);
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setString("ARKANOID");

		startText.setFont(font);
		startText.setCharacterSize(32);
		startText.setFillColor(sf::Color::White);
		startText.setString("Press Enter to Start");

		exitText.setFont(font);
		exitText.setCharacterSize(24);
		exitText.setFillColor(sf::Color::White);
		exitText.setString("Press Escape to Exit");

		hintText.setFont(font);
		hintText.setCharacterSize(20);
		hintText.setFillColor(sf::Color::Cyan);
		hintText.setString("Use arrow keys to move platform\nSpace to launch ball");
	}

	void GameStateMainMenu::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				// Close the application
				Application::Instance().GetGame().Shutdown();
			}
		}
	}

	void GameStateMainMenu::update(float timeDelta)
	{
		// No update logic needed for main menu
	}

	void GameStateMainMenu::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		// Draw background
		window.draw(background);

		// Draw title
		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.5f }));
		titleText.setPosition(viewSize.x / 2.f, viewSize.y / 3.f);
		window.draw(titleText);

		// Draw start text
		startText.setOrigin(GetTextOrigin(startText, { 0.5f, 0.5f }));
		startText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(startText);

		// Draw exit text
		exitText.setOrigin(GetTextOrigin(exitText, { 0.5f, 0.5f }));
		exitText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);
		window.draw(exitText);

		// Draw hint text
		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 0.5f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y * 0.8f);
		window.draw(hintText);
	}
}
