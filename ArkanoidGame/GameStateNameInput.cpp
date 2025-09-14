#include "GameStateNameInput.h"
#include "GameSettings.h"
#include <algorithm>

namespace ArkanoidGame
{
	GameStateNameInput::GameStateNameInput()
	{
		initializeUI();
		initializeRecordsTable();
		
		// Initialize menu options array
		menuOptions[0] = &saveText;
		menuOptions[1] = &skipText;
		
		// Initialize menu selection
		updateMenuSelection();
	}

	void GameStateNameInput::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 100, 200)); // Blue background

		// Initialize title text
		titleText.setFont(font);
		titleText.setString("Enter Your Name");
		titleText.setCharacterSize(UI_FONT_SIZE_LARGE);
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
		titleText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200);

		// Initialize score text
		scoreText.setFont(font);
		scoreText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
		scoreText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150);

		// Initialize name prompt text
		namePromptText.setFont(font);
		namePromptText.setString("Your name:");
		namePromptText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		namePromptText.setFillColor(sf::Color::White);
		namePromptText.setOrigin(namePromptText.getLocalBounds().width / 2, namePromptText.getLocalBounds().height / 2);
		namePromptText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 80);

		// Initialize input box
		inputBox.setSize(sf::Vector2f(300, 40));
		inputBox.setPosition(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50);
		inputBox.setFillColor(sf::Color::Black);
		inputBox.setOutlineColor(sf::Color::White);
		inputBox.setOutlineThickness(2);

		// Initialize name input text
		nameInputText.setFont(font);
		nameInputText.setString("Player");
		nameInputText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		nameInputText.setFillColor(sf::Color::Yellow);
		nameInputText.setOrigin(nameInputText.getLocalBounds().width / 2, nameInputText.getLocalBounds().height / 2);
		nameInputText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30);

		// Initialize records hint text
		recordsHintText.setFont(font);
		recordsHintText.setCharacterSize(UI_FONT_SIZE_SMALL);
		recordsHintText.setFillColor(sf::Color::Cyan);
		recordsHintText.setOrigin(recordsHintText.getLocalBounds().width / 2, recordsHintText.getLocalBounds().height / 2);
		recordsHintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20);

		// Initialize save text
		saveText.setFont(font);
		saveText.setString("Save Score");
		saveText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		saveText.setFillColor(sf::Color::White);
		saveText.setOrigin(saveText.getLocalBounds().width / 2, saveText.getLocalBounds().height / 2);
		saveText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80);

		// Initialize skip text
		skipText.setFont(font);
		skipText.setString("Skip to Main Menu");
		skipText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		skipText.setFillColor(sf::Color::White);
		skipText.setOrigin(skipText.getLocalBounds().width / 2, skipText.getLocalBounds().height / 2);
		skipText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 120);

		// Initialize player name
		playerName = "Player";
	}

	void GameStateNameInput::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (showRecordsTable)
			{
				// In records table mode, only ESC is handled
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Return to main menu
					if (game)
					{
						game->SwitchStateTo(GameStateType::MainMenu);
					}
				}
			}
			else if (isTyping)
			{
				// Handle text input mode
				if (event.key.code == sf::Keyboard::Enter)
				{
					// Finish typing and return to menu
					isTyping = false;
					updateInputDisplay();
				}
				else
				{
					handleTextInput(event);
				}
			}
			else
			{
				// Menu navigation mode (default)
				if (event.key.code == sf::Keyboard::Up)
				{
					selectedOption = (selectedOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT;
					updateMenuSelection();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
					updateMenuSelection();
				}
				else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
				{
					selectOption();
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					// ESC defaults to Skip
					selectedOption = 1;
					selectOption();
				}
				else if (event.key.code == sf::Keyboard::Tab)
				{
					// Start typing mode
					isTyping = true;
					updateInputDisplay();
				}
			}
		}
		else if (event.type == sf::Event::TextEntered && isTyping && !showRecordsTable)
		{
			handleTextInput(event);
		}
	}

	void GameStateNameInput::handleTextInput(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				if (!playerName.empty())
				{
					playerName.pop_back();
					updateInputDisplay();
				}
			}
		}
		else if (event.type == sf::Event::TextEntered)
		{
			char character = static_cast<char>(event.text.unicode);
			if (character >= 32 && character <= 126 && playerName.length() < 20) // Printable ASCII, max 20 chars
			{
				playerName += character;
				updateInputDisplay();
			}
		}
	}

	void GameStateNameInput::updateInputDisplay()
	{
		nameInputText.setString(playerName + (isTyping ? "_" : ""));
		nameInputText.setOrigin(nameInputText.getLocalBounds().width / 2, nameInputText.getLocalBounds().height / 2);
	}

	void GameStateNameInput::update(float timeDelta)
	{
		// Update score display
		if (game)
		{
			int score = game->GetCurrentScore();
			bool won = game->GetGameResult();
			bool isHighScore = game->IsScoreHighEnough();
			
			scoreText.setString("Final Score: " + std::to_string(score) + 
							   (won ? " (VICTORY!)" : " (DEFEAT)"));
			scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
			
			if (isHighScore)
			{
				recordsHintText.setString("Congratulations! This score qualifies for the records table!");
				recordsHintText.setFillColor(sf::Color::Yellow);
			}
			else
			{
				recordsHintText.setString("This score is not high enough for the records table.");
				recordsHintText.setFillColor(sf::Color(128, 128, 128)); // Gray color
			}
			recordsHintText.setOrigin(recordsHintText.getLocalBounds().width / 2, recordsHintText.getLocalBounds().height / 2);
		}
	}

	void GameStateNameInput::updateMenuSelection()
	{
		// Reset all text colors to white
		saveText.setFillColor(sf::Color::White);
		skipText.setFillColor(sf::Color::White);
		
		// Highlight selected option
		menuOptions[selectedOption]->setFillColor(sf::Color::Yellow);
	}

	void GameStateNameInput::selectOption()
	{
		if (!game) return;
		
		switch (selectedOption)
		{
		case 0: // Save Score
			{
				// Add to records if high enough
				if (game->IsScoreHighEnough())
				{
					game->AddRecord(playerName, game->GetCurrentScore());
				}
				// Show records table in this state instead of switching
				showRecordsTable = true;
				updateRecordsTable();
			}
			break;
		case 1: // Skip to Main Menu
			game->SwitchStateTo(GameStateType::MainMenu);
			break;
		}
	}

	void GameStateNameInput::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw title and score (always visible)
		window.draw(titleText);
		window.draw(scoreText);

		if (showRecordsTable)
		{
			// Draw records table
			window.draw(recordsTitleText);
			for (const auto& recordText : recordsTableTexts)
			{
				if (!recordText.getString().isEmpty())
				{
					window.draw(recordText);
				}
			}
			
			// Draw control hint for records view
			sf::Text hintText;
			hintText.setFont(font);
			hintText.setString("Press ESC to return to main menu");
			hintText.setCharacterSize(UI_FONT_SIZE_TINY);
			hintText.setFillColor(sf::Color::Cyan);
			hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
			hintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);
			window.draw(hintText);
		}
		else
		{
			// Draw input elements
			window.draw(namePromptText);
			window.draw(inputBox);
			window.draw(nameInputText);
			window.draw(recordsHintText);
			window.draw(saveText);
			window.draw(skipText);
			
			// Draw control hints
			sf::Text hintText;
			hintText.setFont(font);
			if (isTyping)
			{
				hintText.setString("Type your name, ENTER to finish typing");
			}
			else
			{
				hintText.setString("Use UP/DOWN arrows to navigate, ENTER to select, TAB to edit name, ESC to skip");
			}
			hintText.setCharacterSize(UI_FONT_SIZE_TINY);
			hintText.setFillColor(sf::Color::Cyan);
			hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
			hintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);
			window.draw(hintText);
		}
	}

	void GameStateNameInput::initializeRecordsTable()
	{
		// Initialize records title
		recordsTitleText.setFont(font);
		recordsTitleText.setString("HIGH SCORES");
		recordsTitleText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		recordsTitleText.setFillColor(sf::Color::Yellow);
		recordsTitleText.setOrigin(recordsTitleText.getLocalBounds().width / 2, recordsTitleText.getLocalBounds().height / 2);
		recordsTitleText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50);

		// Initialize records table texts
		recordsTableTexts.resize(10);
		for (int i = 0; i < 10; ++i)
		{
			recordsTableTexts[i].setFont(font);
			recordsTableTexts[i].setCharacterSize(UI_FONT_SIZE_SMALL);
			recordsTableTexts[i].setFillColor(sf::Color::White);
		}
	}

	void GameStateNameInput::updateRecordsTable()
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
			recordsTableTexts[i].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20.0f + static_cast<float>(i) * 25.0f);
		}
		
		// Clear remaining slots if there are fewer than 10 records
		for (size_t i = displayCount; i < recordsTableTexts.size(); ++i)
		{
			recordsTableTexts[i].setString("");
		}
	}
}
