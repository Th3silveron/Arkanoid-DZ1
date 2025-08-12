#include "GameStateExitDialog.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "GameSettings.h"
#include <assert.h>

namespace ArkanoidGame
{
	GameStateExitDialog::GameStateExitDialog()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		initializeUI();
	}

	void GameStateExitDialog::initializeUI()
	{
		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setFillColor(sf::Color::Red);
		titleText.setString("Exit Game?");

		yesText.setFont(font);
		yesText.setCharacterSize(32);
		yesText.setFillColor(sf::Color::White);
		yesText.setString("Yes (Y)");

		noText.setFont(font);
		noText.setCharacterSize(32);
		noText.setFillColor(sf::Color::White);
		noText.setString("No (N)");
	}

	void GameStateExitDialog::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Y)
			{
				Application::Instance().GetGame().Shutdown();
			}
			else if (event.key.code == sf::Keyboard::N || event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}
		}
	}

	void GameStateExitDialog::update(float timeDelta)
	{
		// No update logic needed
	}

	void GameStateExitDialog::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		// Draw background
		window.draw(background);

		// Draw title
		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.5f }));
		titleText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 50.f);
		window.draw(titleText);

		// Draw options
		yesText.setOrigin(GetTextOrigin(yesText, { 0.5f, 0.5f }));
		yesText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 20.f);
		window.draw(yesText);

		noText.setOrigin(GetTextOrigin(noText, { 0.5f, 0.5f }));
		noText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 60.f);
		window.draw(noText);
	}
}
