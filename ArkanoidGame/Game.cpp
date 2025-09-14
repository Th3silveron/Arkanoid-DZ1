#include "Game.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStateWin.h"
#include "GameStateExitDialog.h"
#include "GameStateRecords.h"
#include "GameStateNameInput.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>

namespace ArkanoidGame
{
	Game::Game()
	{
		// Load records from file, or use default if file doesn't exist
		LoadRecordsFromFile();

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		// Save records before shutting down
		SaveRecordsToFile();
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().data->handleWindowEvent(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Clear all game states
			stateStack.clear();
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Remove only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			auto newState = CreateGameState(pendingGameStateType);
			if (newState)
			{
				newState->setGame(this);
				stateStack.push_back({ pendingGameStateType, std::move(newState), pendingGameStateIsExclusivelyVisible });
			}
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().data->update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->data->draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		stateStack.clear();
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		return (options & option) == option;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value)
		{
			options = static_cast<GameOptions>(static_cast<int>(options) | static_cast<int>(option));
		}
		else
		{
			options = static_cast<GameOptions>(static_cast<int>(options) & ~static_cast<int>(option));
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return (it != recordsTable.end()) ? it->second : 0;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = score;
	}

	bool Game::IsScoreHighEnough() const
	{
		// Check if current score is high enough to be in top 5
		if (recordsTable.size() < 5)
		{
			return true; // Always allow if less than 5 records
		}
		
		// Find the lowest score in current records
		int lowestScore = INT_MAX;
		for (const auto& record : recordsTable)
		{
			lowestScore = std::min(lowestScore, record.second);
		}
		
		// Player needs to beat the lowest score to qualify
		return currentScore > lowestScore;
	}

	void Game::AddRecord(const std::string& playerName, int score)
	{
		// Add the record
		recordsTable[playerName] = score;
		
		// If we have more than 10 records, remove the lowest ones
		if (recordsTable.size() > 10)
		{
			// Convert to vector and sort by score
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
			
			// Keep only top 10
			recordsTable.clear();
			for (size_t i = 0; i < 10 && i < records.size(); ++i)
			{
				recordsTable[records[i].first] = records[i].second;
			}
		}
		
		// Save records immediately after adding new record
		SaveRecordsToFile();
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		stateChangeType = GameStateChangeType::Push;
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
	}

	void Game::PopState()
	{
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		stateChangeType = GameStateChangeType::Switch;
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
	}

	std::unique_ptr<GameStateBase> CreateGameState(GameStateType stateType)
	{
		switch (stateType)
		{
		case GameStateType::MainMenu:
			return std::make_unique<GameStateMainMenu>();
		case GameStateType::Playing:
			return std::make_unique<GameStatePlaying>();
		case GameStateType::GameOver:
			return std::make_unique<GameStateGameOver>();
		case GameStateType::Win:
			return std::make_unique<GameStateWin>();
		case GameStateType::ExitDialog:
			return std::make_unique<GameStateExitDialog>();
		case GameStateType::Records:
			return std::make_unique<GameStateRecords>();
		case GameStateType::NameInput:
			return std::make_unique<GameStateNameInput>();
		default:
			return nullptr;
		}
	}

	void Game::SaveRecordsToFile()
	{
		std::ofstream file(RECORDS_FILE);
		if (!file.is_open())
		{
			return; // Failed to open file, silently continue
		}

		// Write each record in format: "PlayerName Score"
		for (const auto& record : recordsTable)
		{
			file << record.first << " " << record.second << std::endl;
		}
	}

	void Game::LoadRecordsFromFile()
	{
		std::ifstream file(RECORDS_FILE);
		if (!file.is_open())
		{
			// File doesn't exist, use default records
			recordsTable =
			{
				{"Champion", 195},
				{"ProGamer", 180},
				{"BlockBreaker", 165},
				{"ArcadeMaster", 150},
				{"SpeedRunner", 135},
			};
			return;
		}

		recordsTable.clear();
		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string playerName;
			int score;
			
			if (iss >> playerName >> score)
			{
				recordsTable[playerName] = score;
			}
		}

		// If no records were loaded, use defaults
		if (recordsTable.empty())
		{
			recordsTable =
			{
				{"Champion", 195},
				{"ProGamer", 180},
				{"BlockBreaker", 165},
				{"ArcadeMaster", 150},
				{"SpeedRunner", 135},
			};
		}
	}
}
